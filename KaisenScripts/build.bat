@echo off
echo ========================================
echo   KAISEN SCRIPTS - BUILD SCRIPT
echo ========================================
echo.

REM Verificar se ImGui existe
if not exist "imgui" (
    echo [ERRO] Pasta 'imgui' nao encontrada!
    echo.
    echo Por favor, baixe Dear ImGui:
    echo 1. Visite: https://github.com/ocornut/imgui
    echo 2. Baixe a versao mais recente
    echo 3. Extraia para a pasta 'imgui' neste diretorio
    echo.
    pause
    exit /b 1
)

echo [OK] Dear ImGui encontrado!
echo.

REM Criar pasta build
if not exist "build" mkdir build
cd build

echo [INFO] Configurando projeto com CMake...
cmake -G "Visual Studio 17 2022" -A x64 ..

if errorlevel 1 (
    echo.
    echo [ERRO] Falha ao configurar o projeto!
    echo.
    echo Tentando com Visual Studio 16 2019...
    cmake -G "Visual Studio 16 2019" -A x64 ..
    
    if errorlevel 1 (
        echo [ERRO] CMake falhou. Verifique se o Visual Studio esta instalado.
        cd ..
        pause
        exit /b 1
    )
)

echo.
echo [INFO] Compilando projeto (Release)...
cmake --build . --config Release

if errorlevel 1 (
    echo.
    echo [ERRO] Falha ao compilar!
    cd ..
    pause
    exit /b 1
)

echo.
echo ========================================
echo   COMPILACAO CONCLUIDA COM SUCESSO!
echo ========================================
echo.
echo Executavel criado em: build\Release\KaisenScripts.exe
echo.

cd ..

REM Copiar executável para raiz
if exist "build\Release\KaisenScripts.exe" (
    copy "build\Release\KaisenScripts.exe" "KaisenScripts.exe"
    echo [OK] Executavel copiado para a raiz do projeto
)

echo.
echo Pressione qualquer tecla para executar o programa...
pause >nul

if exist "KaisenScripts.exe" (
    echo.
    echo [INFO] Iniciando Kaisen Scripts...
    echo.
    start KaisenScripts.exe
) else (
    echo [ERRO] Executavel nao encontrado!
)

echo.
pause
