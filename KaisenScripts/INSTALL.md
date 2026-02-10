# Guia de Instalação - Kaisen Scripts

## 📋 Pré-requisitos

Você tem **DUAS OPÇÕES** para compilar o Kaisen Scripts:

### Opção 1: Versão Console (MAIS FÁCIL) ✅
- Não precisa de ImGui
- Interface de texto no console
- Compilação simples

### Opção 2: Versão com Interface Gráfica (MAIS BONITA) 🎨
- Precisa do Dear ImGui
- Interface moderna e visual
- Compilação um pouco mais complexa

---

## 🚀 OPÇÃO 1: Instalação Rápida (Console)

### Passo 1: Instalar Compilador

#### Windows com Visual Studio:
1. Baixe Visual Studio Community (GRATUITO)
   - Link: https://visualstudio.microsoft.com/downloads/
2. Durante instalação, selecione:
   - ✅ "Desktop development with C++"
3. Instale e reinicie

#### Windows com MinGW:
1. Baixe MinGW-w64
   - Link: https://www.mingw-w64.org/
   - Ou use: https://github.com/niXman/mingw-builds-binaries/releases
2. Extraia e adicione ao PATH
3. Teste: abra CMD e digite `g++ --version`

### Passo 2: Compilar

1. Abra o CMD no diretório do projeto
2. Execute:
   ```
   compile_console.bat
   ```
3. Pronto! Execute `KaisenScriptsConsole.exe`

---

## 🎨 OPÇÃO 2: Instalação Completa (Interface Gráfica)

### Passo 1: Instalar Visual Studio

1. Baixe Visual Studio Community 2019 ou 2022
   - Link: https://visualstudio.microsoft.com/downloads/
2. Durante instalação, selecione:
   - ✅ "Desktop development with C++"
   - ✅ "Windows 10/11 SDK"
3. Instale e reinicie

### Passo 2: Instalar CMake

1. Baixe CMake
   - Link: https://cmake.org/download/
2. Durante instalação, marque:
   - ✅ "Add CMake to system PATH"
3. Instale e reinicie

### Passo 3: Baixar Dear ImGui

1. Acesse: https://github.com/ocornut/imgui
2. Clique em "Code" → "Download ZIP"
3. Extraia o ZIP
4. Copie a pasta extraída para o diretório do projeto
5. Renomeie para `imgui`

Estrutura final:
```
kaisen-scripts/
├── imgui/
│   ├── imgui.h
│   ├── imgui.cpp
│   ├── imgui_draw.cpp
│   ├── imgui_widgets.cpp
│   ├── imgui_tables.cpp
│   └── backends/
│       ├── imgui_impl_win32.h
│       ├── imgui_impl_win32.cpp
│       ├── imgui_impl_dx11.h
│       └── imgui_impl_dx11.cpp
├── kaisen_scripts.cpp
├── CMakeLists.txt
└── build.bat
```

### Passo 4: Compilar

1. Execute `build.bat`
2. Aguarde a compilação
3. Execute `KaisenScripts.exe`

---

## 🔧 Solução de Problemas

### "Compilador não encontrado"

**Solução 1:** Use o Visual Studio Developer Command Prompt
1. Busque por "Developer Command Prompt" no menu Iniciar
2. Abra e navegue até o diretório do projeto
3. Execute os comandos de compilação

**Solução 2:** Adicione o compilador ao PATH
1. Procure onde o Visual Studio está instalado
2. Geralmente: `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\[versão]\bin\Hostx64\x64`
3. Adicione este caminho às variáveis de ambiente PATH

### "ImGui não encontrado"

**Problema:** Pasta `imgui` não existe ou está no lugar errado

**Solução:**
1. Baixe ImGui novamente
2. Certifique-se de extrair na pasta correta
3. A estrutura deve ser:
   ```
   projeto/
   ├── imgui/
   │   ├── imgui.h
   │   └── ...
   └── kaisen_scripts.cpp
   ```

### "Erro ao linkar d3d11.lib"

**Problema:** Windows SDK não instalado

**Solução:**
1. Abra Visual Studio Installer
2. Clique em "Modify"
3. Vá em "Individual Components"
4. Procure e instale:
   - ✅ Windows 10 SDK (ou 11)
5. Aplique as mudanças

### "CMake não encontrado"

**Solução:**
1. Reinstale CMake
2. Durante instalação, marque "Add to PATH"
3. Ou adicione manualmente:
   - Geralmente: `C:\Program Files\CMake\bin`

### "Programa fecha imediatamente"

**Soluções:**
1. Execute como Administrador
2. Verifique se antivírus não está bloqueando
3. Use a versão console para debug:
   ```
   compile_console.bat
   ```

### "Não consigo clicar em nada"

**Problema:** Programa precisa de privilégios elevados

**Solução:**
1. Clique com botão direito no executável
2. "Executar como administrador"
3. Sempre execute assim

---

## 📝 Compilação Manual (Avançado)

### Visual Studio (GUI):

1. Abra Visual Studio
2. File → New → Project
3. Escolha "Empty Project"
4. Adicione os arquivos:
   - `kaisen_scripts.cpp`
   - Todos os arquivos `.cpp` do ImGui
5. Properties → Linker → Input → Additional Dependencies:
   - Adicione: `d3d11.lib;dxgi.lib`
6. Build → Build Solution (F7)

### Linha de Comando (MSVC):

```cmd
cd path\to\project

REM Compilar versão console
cl /std:c++17 /O2 kaisen_scripts_console.cpp /Fe:KaisenScriptsConsole.exe

REM Compilar versão GUI (com ImGui)
cl /std:c++17 /I"imgui" /I"imgui\backends" ^
   kaisen_scripts.cpp ^
   imgui\imgui.cpp ^
   imgui\imgui_draw.cpp ^
   imgui\imgui_widgets.cpp ^
   imgui\imgui_tables.cpp ^
   imgui\backends\imgui_impl_win32.cpp ^
   imgui\backends\imgui_impl_dx11.cpp ^
   /link d3d11.lib /Fe:KaisenScripts.exe
```

### MinGW (g++):

```bash
# Versão console
g++ -std=c++17 -O2 kaisen_scripts_console.cpp -o KaisenScriptsConsole.exe

# Versão GUI (com ImGui)
g++ -std=c++17 -O2 \
    -I imgui -I imgui/backends \
    kaisen_scripts.cpp \
    imgui/imgui.cpp \
    imgui/imgui_draw.cpp \
    imgui/imgui_widgets.cpp \
    imgui/imgui_tables.cpp \
    imgui/backends/imgui_impl_win32.cpp \
    imgui/backends/imgui_impl_dx11.cpp \
    -o KaisenScripts.exe \
    -lgdi32 -ld3d11 -ldxgi -limm32
```

---

## ✅ Verificação Pós-Instalação

Depois de compilar com sucesso:

1. **Teste o executável:**
   - Execute o programa
   - Verifique se a interface aparece

2. **Teste as funcionalidades:**
   - Ative Trigger Bot (tecla 1 ou checkbox)
   - Segure Mouse 4 e mova o cursor sobre uma área vermelha
   - Deve clicar automaticamente

3. **Se algo não funcionar:**
   - Execute como Administrador
   - Verifique se antivírus não está bloqueando
   - Consulte a seção de troubleshooting do README

---

## 📚 Recursos Adicionais

- **Dear ImGui Docs:** https://github.com/ocornut/imgui/wiki
- **CMake Tutorial:** https://cmake.org/cmake/help/latest/guide/tutorial/
- **Visual Studio Docs:** https://docs.microsoft.com/visualstudio/

---

## 🆘 Ainda com problemas?

Se após seguir todos os passos você ainda tiver problemas:

1. Use a **versão console** (mais simples)
2. Verifique se você tem Windows 10/11
3. Certifique-se de ter direitos de Administrador
4. Tente desativar temporariamente o antivírus

---

**Dica:** Para iniciantes, recomendo começar com a **versão console**!
