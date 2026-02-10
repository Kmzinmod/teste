# Kaisen Scripts - Trigger Bot

## ⚠️ AVISO LEGAL

**ESTE SOFTWARE É APENAS PARA FINS EDUCACIONAIS!**

- O uso deste software em jogos online pode violar os Termos de Serviço
- Pode resultar em banimento permanente de contas
- Use apenas em ambientes de teste ou para aprendizado
- O desenvolvedor não se responsabiliza pelo uso indevido

## 🎯 Funcionalidades

### Trigger Bot
- **Zero Delay**: Reconhecimento instantâneo de cor
- **Detecção de Cor**: Identifica quando um pixel fica vermelho
- **Múltiplos Clicks**: 5 clicks simultâneos configuráveis
- **Keybind**: Mouse 4 (XButton1) por padrão

### Auto Click
- **CPS Configurável**: De 1 a 20 clicks por segundo
- **Keybind**: Mouse 5 (XButton2) por padrão
- **Ativação por Tecla**: Segure para ativar

### Macro
- **Sequência Personalizável**: Configure suas próprias macros
- **Keybind**: F1 por padrão
- **Delays Configuráveis**: Ajuste o tempo entre ações

## 🎨 Interface

- Interface gráfica moderna com Dear ImGui
- Tema roxo/cyberpunk
- Controles intuitivos
- Status em tempo real

## 📦 Dependências

Para compilar este projeto, você precisa:

1. **Dear ImGui** - Interface gráfica
   - `imgui.h`
   - `imgui.cpp`
   - `imgui_impl_win32.h/cpp`
   - `imgui_impl_dx11.h/cpp`
   - `imgui_draw.cpp`
   - `imgui_widgets.cpp`
   - `imgui_tables.cpp`

2. **DirectX 11 SDK** (incluído no Windows SDK)

3. **Compilador C++** (Visual Studio 2019+ ou MinGW)

## 🔨 Como Compilar

### Opção 1: Visual Studio

1. Crie um novo projeto Win32 Application
2. Adicione `kaisen_scripts.cpp`
3. Baixe Dear ImGui de: https://github.com/ocornut/imgui
4. Adicione todos os arquivos ImGui ao projeto
5. Configure as propriedades do projeto:
   - C++ → Language → C++ Standard: C++17
   - Linker → Input → Additional Dependencies: `d3d11.lib`
6. Compile em Release x64

### Opção 2: Linha de Comando (MSVC)

```bash
cl /std:c++17 /EHsc /I"path\to\imgui" kaisen_scripts.cpp imgui.cpp imgui_draw.cpp imgui_widgets.cpp imgui_tables.cpp imgui_impl_win32.cpp imgui_impl_dx11.cpp /link d3d11.lib /OUT:KaisenScripts.exe
```

### Opção 3: CMake (Recomendado)

Crie um arquivo `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.15)
project(KaisenScripts)

set(CMAKE_CXX_STANDARD 17)

# Adicione o caminho do ImGui
set(IMGUI_DIR "path/to/imgui")

include_directories(${IMGUI_DIR})

add_executable(KaisenScripts
    kaisen_scripts.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_impl_win32.cpp
    ${IMGUI_DIR}/imgui_impl_dx11.cpp
)

target_link_libraries(KaisenScripts d3d11)
```

Então compile:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## 🎮 Como Usar

1. **Execute o programa** como Administrador
2. **Configure as opções**:
   - Ative/desative cada funcionalidade
   - Ajuste CPS, clicks por trigger, tolerância de cor
3. **Use as teclas**:
   - **Mouse 4 (XButton1)**: Trigger Bot
   - **Mouse 5 (XButton2)**: Auto Click
   - **F1**: Macro

### Configurando o Trigger Bot

1. Ative "Ativar Trigger Bot"
2. Ajuste "Clicks por Trigger" (padrão: 5)
3. Ajuste "Tolerância de Cor" se necessário (0-100)
4. A cor alvo é vermelho RGB(255, 0, 0)
5. Segure Mouse 4 e mire no alvo
6. Quando o pixel central ficar vermelho, os clicks serão executados

### Configurando Auto Click

1. Ative "Ativar Auto Click"
2. Ajuste o CPS desejado (1-20)
3. Segure Mouse 5 para clicar automaticamente

### Configurando Macro

1. Ative "Ativar Macro"
2. Clique em "Configurar Macro" para usar a macro padrão (WASD)
3. Para customizar, edite o código na função `MacroThread()`

## ⚙️ Personalização

### Mudando Keybinds

No código, edite estas linhas:

```cpp
int triggerKey = VK_XBUTTON1; // Mouse 4
int autoClickKey = VK_XBUTTON2; // Mouse 5
int macroKey = VK_F1; // F1
```

Virtual Key Codes comuns:
- `VK_LBUTTON` (0x01) - Botão esquerdo do mouse
- `VK_RBUTTON` (0x02) - Botão direito do mouse
- `VK_XBUTTON1` (0x05) - Mouse 4
- `VK_XBUTTON2` (0x06) - Mouse 5
- `VK_F1` a `VK_F12` - Teclas F1-F12
- `VK_SHIFT` (0x10) - Shift
- `VK_CONTROL` (0x11) - Ctrl

### Mudando Cor Alvo

```cpp
COLORREF targetColor = RGB(255, 0, 0); // Vermelho
```

Exemplos:
- Azul: `RGB(0, 0, 255)`
- Verde: `RGB(0, 255, 0)`
- Amarelo: `RGB(255, 255, 0)`

### Criando Macros Customizadas

Edite a função onde configura macro:

```cpp
config.macroActions.clear();
config.macroActions.push_back({VK_CODE, delay_ms});
```

Exemplo - Macro de combo:
```cpp
config.macroActions.push_back({0x51, 50}); // Q
config.macroActions.push_back({0x57, 50}); // W
config.macroActions.push_back({0x45, 100}); // E (com delay maior)
config.macroActions.push_back({0x52, 50}); // R
```

## 🛠️ Troubleshooting

### "Não consigo compilar"
- Certifique-se de ter todas as dependências do ImGui
- Verifique se o Windows SDK está instalado
- Use Visual Studio 2019 ou superior

### "O programa não detecta as cores"
- Execute como Administrador
- Aumente a tolerância de cor
- Verifique se a cor alvo está correta

### "Os clicks não funcionam"
- Execute como Administrador
- Verifique se a tecla está configurada corretamente
- Alguns jogos bloqueiam inputs sintéticos

### "Programa trava/fecha"
- Atualize drivers gráficos
- Compile em Release ao invés de Debug
- Verifique se há antivírus bloqueando

## 📝 Notas Técnicas

- **Delay Zero**: Usa polling de 1ms para máxima responsividade
- **Detecção de Cor**: GetPixel() no cursor atual
- **Multi-threading**: Threads separadas para cada funcionalidade
- **Inputs Sintéticos**: mouse_event() e keybd_event() do Windows

## 🔐 Detecção Anti-Cheat

Este software pode ser detectado por:
- BattlEye
- Easy Anti-Cheat (EAC)
- Vanguard (Riot)
- VAC (Valve)
- Outros sistemas anti-cheat

**NÃO USE EM JOGOS ONLINE COMPETITIVOS!**

## 📄 Licença

Este projeto é apenas para fins educacionais. Use por sua conta e risco.

## 🤝 Contribuindo

Este é um projeto educacional. Contribuições são bem-vindas para melhorias:
- Melhor detecção de cores
- Interface mais intuitiva
- Mais opções de configuração
- Gravação/reprodução de macros

---

**Lembre-se: Este software é apenas para aprendizado e testes em ambientes controlados!**
