#include <Windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include <conio.h>

// Versão Console do Kaisen Scripts (sem ImGui)
// Use esta versão se tiver problemas com a interface gráfica

struct Config {
    std::atomic<bool> triggerBotEnabled{false};
    std::atomic<bool> autoClickEnabled{false};
    std::atomic<bool> macroEnabled{false};
    
    int triggerKey = VK_XBUTTON1;
    int autoClickKey = VK_XBUTTON2;
    int macroKey = VK_F1;
    
    int clicksPerTrigger = 5;
    int autoClickCPS = 10;
    
    COLORREF targetColor = RGB(255, 0, 0);
    int colorTolerance = 30;
    
    std::vector<std::pair<int, int>> macroActions;
} config;

COLORREF GetColorAtCursor() {
    POINT cursor;
    GetCursorPos(&cursor);
    HDC hdc = GetDC(NULL);
    COLORREF color = GetPixel(hdc, cursor.x, cursor.y);
    ReleaseDC(NULL, hdc);
    return color;
}

bool IsColorMatch(COLORREF color1, COLORREF color2, int tolerance) {
    int r1 = GetRValue(color1), g1 = GetGValue(color1), b1 = GetBValue(color1);
    int r2 = GetRValue(color2), g2 = GetGValue(color2), b2 = GetBValue(color2);
    return (abs(r1 - r2) <= tolerance && abs(g1 - g2) <= tolerance && abs(b1 - b2) <= tolerance);
}

void PerformClicks(int count) {
    for (int i = 0; i < count; i++) {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void TriggerBotThread() {
    while (true) {
        if (config.triggerBotEnabled && (GetAsyncKeyState(config.triggerKey) & 0x8000)) {
            COLORREF currentColor = GetColorAtCursor();
            if (IsColorMatch(currentColor, config.targetColor, config.colorTolerance)) {
                PerformClicks(config.clicksPerTrigger);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void AutoClickThread() {
    while (true) {
        if (config.autoClickEnabled && (GetAsyncKeyState(config.autoClickKey) & 0x8000)) {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            int delayMs = 1000 / config.autoClickCPS;
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void MacroThread() {
    while (true) {
        if (config.macroEnabled && (GetAsyncKeyState(config.macroKey) & 0x8000)) {
            for (const auto& action : config.macroActions) {
                keybd_event(action.first, 0, 0, 0);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                keybd_event(action.first, 0, KEYEVENTF_KEYUP, 0);
                std::this_thread::sleep_for(std::chrono::milliseconds(action.second));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void PrintMenu() {
    system("cls");
    SetColor(13); // Magenta
    std::cout << "\n";
    std::cout << "  ██╗  ██╗ █████╗ ██╗███████╗███████╗███╗   ██╗\n";
    std::cout << "  ██║ ██╔╝██╔══██╗██║██╔════╝██╔════╝████╗  ██║\n";
    std::cout << "  █████╔╝ ███████║██║███████╗█████╗  ██╔██╗ ██║\n";
    std::cout << "  ██╔═██╗ ██╔══██║██║╚════██║██╔══╝  ██║╚██╗██║\n";
    std::cout << "  ██║  ██╗██║  ██║██║███████║███████╗██║ ╚████║\n";
    std::cout << "  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝╚═╝  ╚═══╝\n";
    SetColor(11); // Cyan
    std::cout << "           SCRIPTS v1.0 - Console Edition\n";
    SetColor(8); // Gray
    std::cout << "         Advanced Gaming Assistant\n\n";
    SetColor(7); // White
    
    std::cout << "  ╔════════════════════════════════════════════╗\n";
    std::cout << "  ║           FUNCIONALIDADES                  ║\n";
    std::cout << "  ╠════════════════════════════════════════════╣\n";
    
    SetColor(config.triggerBotEnabled ? 10 : 12);
    std::cout << "  ║ [1] Trigger Bot      ";
    std::cout << (config.triggerBotEnabled ? "[ATIVO]  " : "[INATIVO]");
    SetColor(7);
    std::cout << "        ║\n";
    
    SetColor(config.autoClickEnabled ? 10 : 12);
    std::cout << "  ║ [2] Auto Click       ";
    std::cout << (config.autoClickEnabled ? "[ATIVO]  " : "[INATIVO]");
    SetColor(7);
    std::cout << "        ║\n";
    
    SetColor(config.macroEnabled ? 10 : 12);
    std::cout << "  ║ [3] Macro            ";
    std::cout << (config.macroEnabled ? "[ATIVO]  " : "[INATIVO]");
    SetColor(7);
    std::cout << "        ║\n";
    
    std::cout << "  ╠════════════════════════════════════════════╣\n";
    std::cout << "  ║           CONFIGURACOES                    ║\n";
    std::cout << "  ╠════════════════════════════════════════════╣\n";
    std::cout << "  ║ [4] Ajustar CPS        (" << config.autoClickCPS << " CPS)";
    if (config.autoClickCPS < 10) std::cout << " ";
    std::cout << "       ║\n";
    std::cout << "  ║ [5] Clicks/Trigger     (" << config.clicksPerTrigger << " clicks)";
    if (config.clicksPerTrigger < 10) std::cout << " ";
    std::cout << "    ║\n";
    std::cout << "  ║ [6] Tolerancia Cor     (" << config.colorTolerance << ")";
    if (config.colorTolerance < 10) std::cout << "  ";
    else if (config.colorTolerance < 100) std::cout << " ";
    std::cout << "          ║\n";
    std::cout << "  ║ [7] Configurar Macro                       ║\n";
    std::cout << "  ╠════════════════════════════════════════════╣\n";
    std::cout << "  ║ [0] Sair                                   ║\n";
    std::cout << "  ╚════════════════════════════════════════════╝\n\n";
    
    SetColor(14); // Yellow
    std::cout << "  TECLAS:\n";
    SetColor(7);
    std::cout << "  • Mouse 4: Trigger Bot\n";
    std::cout << "  • Mouse 5: Auto Click\n";
    std::cout << "  • F1: Macro\n\n";
    
    SetColor(12); // Red
    std::cout << "  AVISO: Use apenas para fins educacionais!\n\n";
    SetColor(7);
    
    std::cout << "  Escolha uma opcao: ";
}

int main() {
    SetConsoleTitle(L"Kaisen Scripts - Console Edition");
    
    // Macro padrão
    config.macroActions = {
        {0x57, 50}, // W
        {0x41, 50}, // A
        {0x53, 50}, // S
        {0x44, 50}  // D
    };
    
    // Iniciar threads
    std::thread triggerThread(TriggerBotThread);
    std::thread autoClickThread(AutoClickThread);
    std::thread macroThread(MacroThread);
    
    triggerThread.detach();
    autoClickThread.detach();
    macroThread.detach();
    
    while (true) {
        PrintMenu();
        
        char choice = _getch();
        
        switch (choice) {
            case '1':
                config.triggerBotEnabled = !config.triggerBotEnabled;
                break;
            case '2':
                config.autoClickEnabled = !config.autoClickEnabled;
                break;
            case '3':
                config.macroEnabled = !config.macroEnabled;
                break;
            case '4':
                system("cls");
                std::cout << "\nNovo CPS (1-20): ";
                std::cin >> config.autoClickCPS;
                if (config.autoClickCPS < 1) config.autoClickCPS = 1;
                if (config.autoClickCPS > 20) config.autoClickCPS = 20;
                break;
            case '5':
                system("cls");
                std::cout << "\nClicks por Trigger (1-10): ";
                std::cin >> config.clicksPerTrigger;
                if (config.clicksPerTrigger < 1) config.clicksPerTrigger = 1;
                if (config.clicksPerTrigger > 10) config.clicksPerTrigger = 10;
                break;
            case '6':
                system("cls");
                std::cout << "\nTolerancia de Cor (0-100): ";
                std::cin >> config.colorTolerance;
                if (config.colorTolerance < 0) config.colorTolerance = 0;
                if (config.colorTolerance > 100) config.colorTolerance = 100;
                break;
            case '7':
                system("cls");
                SetColor(11);
                std::cout << "\n=== CONFIGURACAO DE MACRO ===\n\n";
                SetColor(7);
                std::cout << "Macro WASD configurada!\n";
                std::cout << "Para customizar, edite o codigo fonte.\n\n";
                system("pause");
                break;
            case '0':
                std::cout << "\n\nSaindo...\n";
                return 0;
        }
    }
    
    return 0;
}
