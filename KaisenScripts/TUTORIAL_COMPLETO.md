# 🎮 KAISEN SCRIPTS - Tutorial Completo Passo a Passo

## ⏱️ TEMPO TOTAL: 10 MINUTOS

---

## 🚀 MÉTODO MAIS RÁPIDO (Para Iniciantes)

### ✅ O que você precisa:
- Windows 10 ou 11
- Conexão com internet
- 10 minutos

---

## 📋 PASSO 1: Baixar Ferramentas (5 minutos)

### 1.1 - Baixar Visual Studio Build Tools

1. **Abra seu navegador**
2. **Cole este link:** https://aka.ms/vs/17/release/vs_BuildTools.exe
3. **Clique em Download**
4. **Aguarde o download** (70-100 MB)

### 1.2 - Instalar Build Tools

1. **Execute o instalador** (vs_BuildTools.exe)
2. **Aguarde carregar**
3. **Marque:** "Desktop development with C++"
   ```
   ☑️ Desktop development with C++
   ```
4. **Clique:** Install (vai baixar ~5GB)
5. **Aguarde** (5-15 minutos dependendo da internet)
6. **Reinicie o computador** quando solicitado

---

## 📥 PASSO 2: Baixar os Arquivos (1 minuto)

Você já tem os arquivos que eu criei:

```
✅ kaisen_scripts.cpp
✅ kaisen_scripts_console.cpp
✅ CMakeLists.txt
✅ build.bat
✅ compile_console.bat
✅ install_and_build.bat  ← NOVO!
```

**Organize assim:**

1. Crie uma pasta: `C:\KaisenScripts`
2. Coloque TODOS os arquivos lá
3. Estrutura:
   ```
   C:\KaisenScripts\
   ├── kaisen_scripts.cpp
   ├── kaisen_scripts_console.cpp
   ├── install_and_build.bat
   ├── compile_console.bat
   ├── build.bat
   ├── CMakeLists.txt
   └── README.md
   ```

---

## ⚡ PASSO 3: Compilar! (2 minutos)

### Opção A: Automático (RECOMENDADO)

1. **Abra a pasta** `C:\KaisenScripts`
2. **Clique duas vezes em:** `install_and_build.bat`
3. **Aguarde** - o script vai:
   - ✅ Detectar o compilador
   - ✅ Baixar Dear ImGui automaticamente
   - ✅ Compilar o projeto
   - ✅ Criar o KaisenScripts.exe
4. **Pronto!** O .exe estará na pasta

### Opção B: Manual (se a Opção A falhar)

1. **Pressione:** Windows + R
2. **Digite:** cmd
3. **Pressione:** Ctrl + Shift + Enter (abre como Admin)
4. **Digite:**
   ```batch
   cd C:\KaisenScripts
   compile_console.bat
   ```
5. **Aguarde compilar**
6. **Pronto!** KaisenScriptsConsole.exe criado

---

## 🎮 PASSO 4: Executar (30 segundos)

1. **Localize o arquivo:**
   - `KaisenScripts.exe` (versão GUI) OU
   - `KaisenScriptsConsole.exe` (versão console)

2. **Clique com botão direito** no .exe
3. **Selecione:** "Executar como administrador"
4. **Se aparecer aviso do Windows Defender:**
   - Clique em "Mais informações"
   - Clique em "Executar assim mesmo"

5. **PRONTO!** O programa vai abrir!

---

## 🎯 PASSO 5: Configurar e Usar

### Interface (Versão GUI):

```
╔════════════════════════════════════╗
║     KAISEN SCRIPTS v1.0            ║
╠════════════════════════════════════╣
║ TRIGGER BOT                        ║
║ ☑️ Ativar Trigger Bot              ║
║ Clicks: [====5====] 5              ║
║ Tolerância: [====30===] 30         ║
╠════════════════════════════════════╣
║ AUTO CLICK                         ║
║ ☑️ Ativar Auto Click               ║
║ CPS: [====10===] 10                ║
╠════════════════════════════════════╣
║ MACRO                              ║
║ ☑️ Ativar Macro                    ║
║ [Configurar Macro]                 ║
╚════════════════════════════════════╝
```

### Como Usar:

#### Trigger Bot:
1. **Marque:** ☑️ Ativar Trigger Bot
2. **Ajuste:** Número de clicks (1-10)
3. **No jogo:** Segure **Mouse 4**
4. **Mire:** Em algo vermelho
5. **Resultado:** Vai clicar automaticamente!

#### Auto Click:
1. **Marque:** ☑️ Ativar Auto Click
2. **Ajuste:** CPS desejado (1-20)
3. **No jogo:** Segure **Mouse 5**
4. **Resultado:** Cliques automáticos!

#### Macro:
1. **Marque:** ☑️ Ativar Macro
2. **Clique:** Configurar Macro
3. **No jogo:** Pressione **F1**
4. **Resultado:** Executa sequência WASD!

---

## 🔧 SOLUÇÃO DE PROBLEMAS

### "Não encontrei o install_and_build.bat"
**Solução:** Use `compile_console.bat` para versão simples

### "Compilador não encontrado"
**Solução:**
1. Abra: Menu Iniciar
2. Procure: "Developer Command Prompt"
3. Execute e rode os comandos lá

### "ImGui não encontrado"
**Solução:**
1. Baixe: https://github.com/ocornut/imgui/archive/refs/heads/master.zip
2. Extraia
3. Renomeie pasta para "imgui"
4. Coloque em `C:\KaisenScripts\imgui\`

### "Antivírus bloqueou"
**Solução:**
1. Abra Windows Security
2. Proteção contra vírus e ameaças
3. Gerenciar configurações
4. Adicionar exclusão
5. Adicione a pasta `C:\KaisenScripts`

### "Programa não abre"
**Solução:**
1. Verifique se executou como Administrador
2. Instale Visual C++ Redistributable:
   - https://aka.ms/vs/17/release/vc_redist.x64.exe

### "Não funciona no jogo"
**Motivos:**
- Anti-cheat detectou
- Precisa executar como Admin
- Jogo bloqueia inputs sintéticos

---

## 📊 COMPARAÇÃO DE VERSÕES

| Recurso | GUI (com ImGui) | Console |
|---------|----------------|---------|
| Interface Bonita | ✅ | ❌ |
| Fácil de Usar | ✅ | ⚠️ |
| Compilação | Mais Difícil | Fácil |
| Tamanho | ~2MB | ~500KB |
| Dependências | Precisa ImGui | Nenhuma |
| **Recomendado** | Sim | Iniciantes |

---

## ⚙️ CONFIGURAÇÕES AVANÇADAS

### Mudar Keybinds (no código):

Abra `kaisen_scripts.cpp` e edite:

```cpp
// Linha ~20
int triggerKey = VK_XBUTTON1;    // Mouse 4
int autoClickKey = VK_XBUTTON2;  // Mouse 5  
int macroKey = VK_F1;            // F1
```

**Códigos comuns:**
- `VK_F1` a `VK_F12` = Teclas F
- `VK_SHIFT` = Shift
- `VK_CONTROL` = Ctrl
- `VK_MENU` = Alt
- `0x51` = Q
- `0x57` = W
- `0x45` = E
- `0x52` = R

### Mudar Cor Alvo:

```cpp
// Linha ~25
COLORREF targetColor = RGB(255, 0, 0); // Vermelho
```

**Outras cores:**
- Azul: `RGB(0, 0, 255)`
- Verde: `RGB(0, 255, 0)`
- Roxo: `RGB(128, 0, 128)`

### Criar Macro Customizada:

No botão "Configurar Macro":

```cpp
config.macroActions.clear();
config.macroActions.push_back({0x51, 100}); // Q + 100ms
config.macroActions.push_back({0x57, 100}); // W + 100ms
config.macroActions.push_back({0x45, 200}); // E + 200ms
config.macroActions.push_back({0x52, 100}); // R + 100ms
```

---

## 📹 VÍDEO TUTORIAL (Conceitual)

Se este fosse um vídeo, seria assim:

```
00:00 - Introdução
00:30 - Download Build Tools
02:00 - Instalação
05:00 - Organizando arquivos
06:00 - Compilação automática
08:00 - Primeira execução
09:00 - Configuração
09:45 - Teste prático
10:00 - Encerramento
```

---

## ✅ CHECKLIST FINAL

Antes de considerar pronto:

- [ ] Visual Studio Build Tools instalado
- [ ] Arquivos na pasta C:\KaisenScripts
- [ ] Compilado com sucesso (.exe criado)
- [ ] Testado execução como Admin
- [ ] Antivírus configurado (se necessário)
- [ ] Keybinds testadas
- [ ] Funcionalidades testadas

---

## 🎓 APRENDA MAIS

Quer entender o código?

1. **C++ Básico:**
   - https://www.learncpp.com/

2. **Windows API:**
   - https://docs.microsoft.com/windows/win32/

3. **ImGui Tutorial:**
   - https://github.com/ocornut/imgui/wiki

4. **Game Hacking Ético:**
   - https://guidedhacking.com/

---

## ⚠️ AVISO LEGAL (IMPORTANTE!)

```
╔════════════════════════════════════════════╗
║  ESTE SOFTWARE É APENAS EDUCACIONAL!       ║
║                                            ║
║  ❌ NÃO use em jogos online                ║
║  ❌ Você SERÁ banido                       ║
║  ❌ Viola Termos de Serviço                ║
║  ✅ Use para aprender programação          ║
║  ✅ Use em ambientes de teste              ║
╚════════════════════════════════════════════╝
```

---

## 🆘 PRECISA DE AJUDA?

Se mesmo seguindo tudo você travou:

1. **Releia este guia** com calma
2. **Use a versão Console** (mais fácil)
3. **Procure por "C++ compiler windows"** no YouTube
4. **Considere pedir ajuda** a um amigo programador

---

**BOA SORTE! 🎮**

Lembre-se: O objetivo é **APRENDER**, não trapacear! 😊
