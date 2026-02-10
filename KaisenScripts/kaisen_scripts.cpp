#include <Windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

#pragma comment(lib, "d3d11.lib")

// Forward declarations
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// DirectX11 data
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

// Configurações globais
struct Config {
    std::atomic<bool> triggerBotEnabled{false};
    std::atomic<bool> autoClickEnabled{false};
    std::atomic<bool> macroEnabled{false};
    
    int triggerKey = VK_XBUTTON1; // Mouse 4 por padrão
    int autoClickKey = VK_XBUTTON2; // Mouse 5 por padrão
    int macroKey = VK_F1;
    
    int clicksPerTrigger = 5;
    int autoClickCPS = 10;
    
    COLORREF targetColor = RGB(255, 0, 0); // Vermelho
    int colorTolerance = 30;
    
    std::vector<std::pair<int, int>> macroActions; // VK_CODE, delay
} config;

// Funções auxiliares DirectX
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();

// Funções do bot
COLORREF GetColorAtCursor();
bool IsColorMatch(COLORREF color1, COLORREF color2, int tolerance);
void PerformClicks(int count);
void TriggerBotThread();
void AutoClickThread();
void MacroThread();

// Window procedure
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
        case WM_SIZE:
            if (g_pd3dDevice != nullptr && wParam != SIZE_MINIMIZED) {
                CleanupRenderTarget();
                g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
                CreateRenderTarget();
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU)
                return 0;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Função para obter cor no cursor
COLORREF GetColorAtCursor() {
    POINT cursor;
    GetCursorPos(&cursor);
    
    HDC hdc = GetDC(NULL);
    COLORREF color = GetPixel(hdc, cursor.x, cursor.y);
    ReleaseDC(NULL, hdc);
    
    return color;
}

// Verifica se as cores correspondem dentro da tolerância
bool IsColorMatch(COLORREF color1, COLORREF color2, int tolerance) {
    int r1 = GetRValue(color1);
    int g1 = GetGValue(color1);
    int b1 = GetBValue(color1);
    
    int r2 = GetRValue(color2);
    int g2 = GetGValue(color2);
    int b2 = GetBValue(color2);
    
    return (abs(r1 - r2) <= tolerance &&
            abs(g1 - g2) <= tolerance &&
            abs(b1 - b2) <= tolerance);
}

// Realiza múltiplos clicks
void PerformClicks(int count) {
    for (int i = 0; i < count; i++) {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

// Thread do Trigger Bot
void TriggerBotThread() {
    while (true) {
        if (config.triggerBotEnabled) {
            if (GetAsyncKeyState(config.triggerKey) & 0x8000) {
                COLORREF currentColor = GetColorAtCursor();
                
                if (IsColorMatch(currentColor, config.targetColor, config.colorTolerance)) {
                    PerformClicks(config.clicksPerTrigger);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

// Thread do Auto Click
void AutoClickThread() {
    while (true) {
        if (config.autoClickEnabled) {
            if (GetAsyncKeyState(config.autoClickKey) & 0x8000) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                
                int delayMs = 1000 / config.autoClickCPS;
                std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

// Thread da Macro
void MacroThread() {
    while (true) {
        if (config.macroEnabled) {
            if (GetAsyncKeyState(config.macroKey) & 0x8000) {
                for (const auto& action : config.macroActions) {
                    keybd_event(action.first, 0, 0, 0);
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    keybd_event(action.first, 0, KEYEVENTF_KEYUP, 0);
                    std::this_thread::sleep_for(std::chrono::milliseconds(action.second));
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// Criar device DirectX
bool CreateDeviceD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    
    if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags,
                                       featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain,
                                       &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D() {
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget() {
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget() {
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// Função principal
int main() {
    // Criar janela
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"Kaisen Scripts", nullptr };
    RegisterClassExW(&wc);
    HWND hwnd = CreateWindowW(wc.lpszClassName, L"Kaisen Scripts v1.0", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, nullptr, nullptr, wc.hInstance, nullptr);

    // Inicializar Direct3D
    if (!CreateDeviceD3D(hwnd)) {
        CleanupDeviceD3D();
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Estilo moderno
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 8.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    
    // Cores personalizadas
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.10f, 0.95f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.10f, 0.30f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.30f, 0.15f, 0.45f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.25f, 0.12f, 0.38f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.17f, 0.53f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.22f, 0.68f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.18f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.30f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 0.25f, 0.90f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.35f, 1.00f, 1.00f);

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Iniciar threads
    std::thread triggerThread(TriggerBotThread);
    std::thread autoClickThread(AutoClickThread);
    std::thread macroThread(MacroThread);
    
    triggerThread.detach();
    autoClickThread.detach();
    macroThread.detach();

    // Main loop
    bool done = false;
    while (!done) {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // UI Principal
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::Begin("Kaisen Scripts", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::PushFont(io.Fonts->Fonts[0]);
        ImGui::TextColored(ImVec4(0.8f, 0.3f, 1.0f, 1.0f), "KAISEN SCRIPTS");
        ImGui::PopFont();
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Advanced Gaming Assistant v1.0");
        ImGui::Separator();

        // Trigger Bot Section
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.3f, 1.0f), "TRIGGER BOT");
        ImGui::Separator();
        
        bool triggerEnabled = config.triggerBotEnabled;
        if (ImGui::Checkbox("Ativar Trigger Bot", &triggerEnabled)) {
            config.triggerBotEnabled = triggerEnabled;
        }
        
        ImGui::SliderInt("Clicks por Trigger", &config.clicksPerTrigger, 1, 10);
        ImGui::SliderInt("Tolerancia de Cor", &config.colorTolerance, 0, 100);
        
        ImGui::Text("Tecla Trigger: Mouse 4 (XButton1)");

        // Auto Click Section
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(0.3f, 0.8f, 1.0f, 1.0f), "AUTO CLICK");
        ImGui::Separator();
        
        bool autoClickEnabled = config.autoClickEnabled;
        if (ImGui::Checkbox("Ativar Auto Click", &autoClickEnabled)) {
            config.autoClickEnabled = autoClickEnabled;
        }
        
        ImGui::SliderInt("CPS (Clicks Por Segundo)", &config.autoClickCPS, 1, 20);
        ImGui::Text("Tecla Auto Click: Mouse 5 (XButton2)");

        // Macro Section
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.5f, 1.0f), "MACRO");
        ImGui::Separator();
        
        bool macroEnabled = config.macroEnabled;
        if (ImGui::Checkbox("Ativar Macro", &macroEnabled)) {
            config.macroEnabled = macroEnabled;
        }
        
        ImGui::Text("Tecla Macro: F1");
        
        if (ImGui::Button("Configurar Macro", ImVec2(200, 30))) {
            // Macro padrão exemplo (pode ser customizado)
            config.macroActions.clear();
            config.macroActions.push_back({0x57, 50}); // W
            config.macroActions.push_back({0x41, 50}); // A
            config.macroActions.push_back({0x53, 50}); // S
            config.macroActions.push_back({0x44, 50}); // D
        }

        // Status
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.3f, 1.0f), "STATUS");
        ImGui::Separator();
        
        ImGui::Text("Trigger Bot: %s", config.triggerBotEnabled ? "ATIVO" : "INATIVO");
        ImGui::Text("Auto Click: %s", config.autoClickEnabled ? "ATIVO" : "INATIVO");
        ImGui::Text("Macro: %s", config.macroEnabled ? "ATIVO" : "INATIVO");

        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "AVISO: Use apenas para fins educacionais!");

        ImGui::End();

        // Rendering
        ImGui::Render();
        const float clear_color[4] = { 0.08f, 0.08f, 0.10f, 1.00f };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(hwnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}
