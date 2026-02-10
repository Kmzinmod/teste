# 🎮 KAISEN SCRIPTS - Pacote Completo

## 📦 Conteúdo do ZIP

Você baixou o pacote completo do Kaisen Scripts! Este arquivo contém TUDO que você precisa.

```
📁 KaisenScripts_Complete.zip
├── 📄 kaisen_scripts.cpp              (Código principal com interface gráfica)
├── 📄 kaisen_scripts_console.cpp      (Versão simplificada para console)
├── 📄 CMakeLists.txt                  (Configuração CMake)
├── 🔧 install_and_build.bat           ⭐ EXECUTE ESTE PRIMEIRO!
├── 🔧 build.bat                       (Script de compilação)
├── 🔧 compile_console.bat             (Compilação rápida da versão console)
├── 📖 README.md                       (Documentação principal)
├── 📖 INSTALL.md                      (Guia de instalação)
├── 📖 TUTORIAL_COMPLETO.md            (Tutorial passo a passo)
└── 📖 ONLINE_COMPILE.md               (Métodos alternativos)
```

---

## 🚀 INÍCIO RÁPIDO (2 MINUTOS)

### Passo 1: Extrair
1. Clique com botão direito no ZIP
2. "Extrair tudo..."
3. Escolha uma pasta (ex: `C:\KaisenScripts`)

### Passo 2: Executar Script Automático
1. Abra a pasta extraída
2. **Clique duas vezes em:** `install_and_build.bat`
3. Aguarde (vai instalar tudo automaticamente)
4. Pronto! O arquivo `KaisenScripts.exe` será criado

### Passo 3: Usar
1. Clique com botão direito em `KaisenScripts.exe`
2. "Executar como administrador"
3. Configure e divirta-se!

---

## ⚡ MÉTODOS DE COMPILAÇÃO

### Método 1: Automático (RECOMENDADO) ⭐
```
✅ Duplo clique em: install_and_build.bat
```
- Detecta compilador automaticamente
- Baixa Dear ImGui
- Compila tudo
- Cria o .exe

### Método 2: Console Simples (SEM ImGui)
```
✅ Duplo clique em: compile_console.bat
```
- Não precisa de Dear ImGui
- Interface de texto
- Compilação mais rápida

### Método 3: Manual com CMake
```batch
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

---

## 📋 PRÉ-REQUISITOS

### O que você PRECISA:
- ✅ Windows 10 ou 11
- ✅ Visual Studio Build Tools (o script instala automaticamente)
- ✅ 5 GB de espaço livre
- ✅ Conexão com internet (para baixar ferramentas)

### O script install_and_build.bat vai instalar:
- Visual Studio Build Tools (se necessário)
- Dear ImGui (automaticamente)
- CMake (se necessário)

---

## 🎯 FUNCIONALIDADES

### ⚡ Trigger Bot
- Detecção de cor em tempo real
- Zero delay (polling 1ms)
- 5 clicks simultâneos configuráveis
- Keybind: Mouse 4 (XButton1)

### 🖱️ Auto Click
- CPS configurável (1-20)
- Ativação por keybind
- Keybind: Mouse 5 (XButton2)

### ⌨️ Macro
- Sequências personalizáveis
- Delays ajustáveis
- Keybind: F1

### 🎨 Interface
- Design moderno roxo/cyberpunk
- Controles intuitivos
- Status em tempo real
- Ajustes dinâmicos

---

## 📖 DOCUMENTAÇÃO

### Para Iniciantes:
→ Leia: **TUTORIAL_COMPLETO.md**
- Passo a passo detalhado
- Troubleshooting completo
- Configurações avançadas

### Para Instalação:
→ Leia: **INSTALL.md**
- Guia de dependências
- Múltiplos métodos
- Solução de problemas

### Para Uso:
→ Leia: **README.md**
- Documentação completa
- Como usar cada feature
- Customização

### Compilação Online:
→ Leia: **ONLINE_COMPILE.md**
- Métodos alternativos
- GitHub Actions
- Docker

---

## 🔧 SOLUÇÃO RÁPIDA DE PROBLEMAS

### "Script não funciona"
```
Solução 1: Execute como Administrador
Solução 2: Use compile_console.bat
Solução 3: Leia INSTALL.md
```

### "Compilador não encontrado"
```
Solução: Instale Visual Studio Build Tools
Link: https://aka.ms/vs/17/release/vs_BuildTools.exe
```

### "ImGui não encontrado"
```
Solução: O script baixa automaticamente
Ou baixe manualmente: https://github.com/ocornut/imgui
```

### "Antivírus bloqueou"
```
Solução: Adicione exceção na pasta
Windows Security → Exclusões → Adicionar pasta
```

### "Programa não abre"
```
Solução 1: Execute como Administrador
Solução 2: Instale VC++ Redistributable
Link: https://aka.ms/vs/17/release/vc_redist.x64.exe
```

---

## ⚠️ AVISO LEGAL IMPORTANTE

```
╔════════════════════════════════════════════════════╗
║  ⚠️  APENAS PARA FINS EDUCACIONAIS  ⚠️            ║
╠════════════════════════════════════════════════════╣
║                                                    ║
║  ❌ NÃO use em jogos online                       ║
║  ❌ Você SERÁ banido permanentemente              ║
║  ❌ Viola Termos de Serviço de jogos              ║
║  ❌ Pode resultar em ação legal                   ║
║                                                    ║
║  ✅ Use para aprender programação                 ║
║  ✅ Use em ambientes de teste                     ║
║  ✅ Use para estudar automação                    ║
║  ✅ Use responsavelmente                          ║
║                                                    ║
╚════════════════════════════════════════════════════╝
```

**O desenvolvedor não se responsabiliza pelo uso indevido!**

---

## 🎓 APRENDIZADO

Este projeto é excelente para aprender:
- ✅ C++ moderno
- ✅ Windows API
- ✅ Threading
- ✅ Interface gráfica (ImGui)
- ✅ DirectX 11
- ✅ CMake
- ✅ Automação

---

## 📊 COMPARAÇÃO DE VERSÕES

| Característica | GUI (ImGui) | Console |
|----------------|-------------|---------|
| Interface Visual | ✅ Moderna | ❌ Texto |
| Fácil de Usar | ✅ Muito | ⚠️ Médio |
| Compilação | ⚠️ Complexa | ✅ Fácil |
| Tamanho do .exe | ~2 MB | ~500 KB |
| Dependências | ImGui + DX11 | Nenhuma |
| Tempo de Compilação | 2-5 min | 30 seg |
| **Recomendado para** | Uso geral | Iniciantes/Debug |

---

## 🚦 ESCOLHA SEU CAMINHO

### 🟢 Iniciante Total
1. Execute: `compile_console.bat`
2. Use a versão console primeiro
3. Depois tente a versão GUI

### 🟡 Intermediário
1. Execute: `install_and_build.bat`
2. Deixe o script fazer tudo
3. Use a versão com interface

### 🔴 Avançado
1. Leia o código fonte
2. Customize como quiser
3. Compile manualmente com CMake

---

## 💡 DICAS

### Para melhor experiência:
- ✅ Execute sempre como Administrador
- ✅ Adicione exceção no antivírus
- ✅ Use em ambiente de teste
- ✅ Configure o CPS adequadamente
- ✅ Ajuste a tolerância de cor

### Para customização:
- 📝 Edite o código fonte
- 🎨 Mude as cores do tema
- ⌨️ Altere os keybinds
- 🎯 Crie suas próprias macros

---

## 📞 PRÓXIMOS PASSOS

1. **Extraia o ZIP**
2. **Execute install_and_build.bat**
3. **Aguarde a compilação**
4. **Leia TUTORIAL_COMPLETO.md**
5. **Teste em ambiente seguro**
6. **Aprenda e divirta-se!**

---

## 🌟 RECURSOS EXTRAS

### Arquivos Incluídos:
- ✅ 2 versões completas do código
- ✅ 4 documentações diferentes
- ✅ 3 scripts de compilação
- ✅ Configuração CMake profissional
- ✅ Tudo pronto para usar!

### O que NÃO está incluído:
- ❌ Dear ImGui (baixado automaticamente)
- ❌ Visual Studio (instalado se necessário)
- ❌ Executável .exe (você compila!)

**Por quê?** Para sua segurança! Nunca execute .exe de fontes não confiáveis.

---

## ✅ CHECKLIST

Antes de começar, verifique:

- [ ] Windows 10/11 instalado
- [ ] Conexão com internet ativa
- [ ] 5 GB de espaço livre
- [ ] Direitos de Administrador
- [ ] Antivírus configurado (se necessário)
- [ ] ZIP extraído completamente
- [ ] Arquivos na mesma pasta

---

## 🎉 PRONTO PARA COMEÇAR?

1. **Feche este README**
2. **Execute: install_and_build.bat**
3. **Siga as instruções na tela**
4. **Em 5 minutos você terá seu .exe!**

**BOA SORTE E BOM APRENDIZADO! 🚀**

---

*Criado para fins educacionais • Use responsavelmente • Versão 1.0*
