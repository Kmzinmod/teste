# Guia de Compilação Online - Kaisen Scripts

## ⚡ Compilação Sem Instalar Nada!

Se você não quer instalar Visual Studio ou MinGW, pode usar compiladores online e depois baixar o .exe

### 📱 Método 1: Repl.it (Mais Fácil)

1. Acesse: https://replit.com/
2. Crie conta grátis
3. Create Repl → C++
4. Cole o código de `kaisen_scripts_console.cpp`
5. Clique em Run
6. **PROBLEMA:** Repl.it não suporta Windows APIs

❌ **Não funciona para este projeto** (precisa de APIs do Windows)

---

### 💻 Método 2: Compilador Local Portátil

Sem precisar instalar nada no sistema!

#### Passo 1: Baixar MinGW Portátil

1. Acesse: https://winlibs.com/
2. Baixe: "GCC 13.2.0 + MinGW-w64 11.0.1 (UCRT) - release 2"
3. Extraia para `C:\MinGW`

#### Passo 2: Compilar

Crie um arquivo `compile_portable.bat`:

```batch
@echo off
set PATH=C:\MinGW\bin;%PATH%

echo Compilando versao Console...
g++ -std=c++17 -O2 kaisen_scripts_console.cpp -o KaisenScripts.exe -lgdi32 -luser32 -static

if exist KaisenScripts.exe (
    echo.
    echo [OK] Compilado com sucesso!
    echo Executavel: KaisenScripts.exe
) else (
    echo [ERRO] Falha na compilacao!
)

pause
```

Execute o `.bat` e pronto!

---

### 🌐 Método 3: GitHub Actions (Automático)

Use GitHub para compilar automaticamente:

1. Crie repositório no GitHub
2. Faça upload dos arquivos
3. Crie `.github/workflows/build.yml`:

```yaml
name: Build Kaisen Scripts

on:
  push:
    branches: [ main ]
  workflow_dispatch:

jobs:
  build:
    runs-on: windows-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup MSVC
      uses: microsoft/setup-msbuild@v1
    
    - name: Download ImGui
      run: |
        Invoke-WebRequest -Uri "https://github.com/ocornut/imgui/archive/refs/heads/master.zip" -OutFile "imgui.zip"
        Expand-Archive -Path "imgui.zip" -DestinationPath "."
        Rename-Item -Path "imgui-master" -NewName "imgui"
    
    - name: Build with CMake
      run: |
        mkdir build
        cd build
        cmake -G "Visual Studio 17 2022" -A x64 ..
        cmake --build . --config Release
    
    - name: Upload Artifact
      uses: actions/upload-artifact@v3
      with:
        name: KaisenScripts-Windows
        path: build/Release/KaisenScripts.exe
```

4. Vá em Actions → Execute workflow
5. Baixe o .exe na seção Artifacts

---

### 🎯 Método 4: Pedir para Alguém Compilar

**ATENÇÃO:** Nunca execute .exe de fontes não confiáveis!

Se você conhece alguém com Visual Studio:
1. Envie o código fonte
2. Peça para compilar
3. Verifique o hash do arquivo

---

### ✅ Método 5: Docker (Para Avançados)

```dockerfile
FROM debian:latest

RUN apt-get update && apt-get install -y \
    mingw-w64 \
    cmake \
    git

WORKDIR /app
COPY . .

RUN x86_64-w64-mingw32-g++ -std=c++17 -O2 \
    kaisen_scripts_console.cpp \
    -o KaisenScripts.exe \
    -lgdi32 -luser32 -static
```

Compilar:
```bash
docker build -t kaisen-builder .
docker run --rm -v ${PWD}:/out kaisen-builder cp KaisenScripts.exe /out/
```

---

## 🔒 Por Que Não Posso Baixar um .exe Pronto?

1. **Segurança:** Arquivos .exe podem conter malware
2. **Antivírus:** Vai bloquear/deletar automaticamente
3. **Legal:** Distribuir software de automação de jogos é área cinzenta
4. **Confiança:** Você nunca deve executar .exe de desconhecidos

---

## 📦 Solução MAIS FÁCIL (Recomendada)

Use o script de instalação automática que criei:

1. Execute: `install_and_build.bat`
2. Ele vai:
   - ✅ Detectar seu compilador
   - ✅ Baixar ImGui automaticamente
   - ✅ Compilar tudo
   - ✅ Criar o .exe

**Total: 2 minutos!**

---

## 💡 Ainda Muito Difícil?

Use a **versão Console** (sem ImGui):

```batch
# Instalar MinGW Portátil (5 minutos)
1. Baixe: https://winlibs.com/
2. Extraia

# Compilar (30 segundos)
set PATH=C:\caminho\para\mingw\bin;%PATH%
g++ kaisen_scripts_console.cpp -o Kaisen.exe
```

Pronto!

---

## ⚠️ Lembrete Final

Este software é apenas para **fins educacionais**. 
Não use em jogos online - você SERÁ banido!
