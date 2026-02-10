@echo off
title Kaisen Scripts - Instalador Automatico
color 0D

echo.
echo  ================================================
echo   KAISEN SCRIPTS - INSTALADOR AUTOMATICO
echo  ================================================
echo.
echo  Este script vai:
echo  1. Verificar dependencias
echo  2. Baixar Dear ImGui automaticamente
echo  3. Compilar o projeto
echo  4. Executar o programa
echo.
echo  Pressione qualquer tecla para continuar...
pause >nul

cls
echo.
echo [1/4] Verificando compilador...
echo.

where cl >nul 2>nul
if %errorlevel% equ 0 (
    echo [OK] Visual Studio encontrado!
    set COMPILER=MSVC
    goto download_imgui
)

where g++ >nul 2>nul
if %errorlevel% equ 0 (
    echo [OK] MinGW encontrado!
    set COMPILER=MINGW
    goto download_imgui
)

echo [ERRO] Nenhum compilador encontrado!
echo.
echo SOLUCAO RAPIDA:
echo.
echo Opcao 1 - Instalar Visual Studio Build Tools (RECOMENDADO):
echo 1. Abra: https://aka.ms/vs/17/release/vs_BuildTools.exe
echo 2. Execute o instalador
echo 3. Selecione "Desktop development with C++"
echo 4. Instale e reinicie este script
echo.
echo Opcao 2 - Usar versao Console (SEM ImGui):
echo 1. Execute: compile_console.bat
echo.
pause
exit /b 1

:download_imgui
cls
echo.
echo [2/4] Verificando Dear ImGui...
echo.

if exist "imgui" (
    echo [OK] ImGui ja existe!
    goto compile
)

echo Dear ImGui nao encontrado.
echo.
echo BAIXAR AUTOMATICAMENTE? (S/N)
set /p download=

if /i not "%download%"=="S" goto manual_imgui

echo.
echo Baixando Dear ImGui...
echo.

where powershell >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERRO] PowerShell nao encontrado!
    goto manual_imgui
)

powershell -Command "& { [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -Uri 'https://github.com/ocornut/imgui/archive/refs/heads/master.zip' -OutFile 'imgui.zip' }"

if not exist "imgui.zip" (
    echo [ERRO] Falha ao baixar!
    goto manual_imgui
)

echo Extraindo...
powershell -Command "Expand-Archive -Path 'imgui.zip' -DestinationPath '.' -Force"
rename "imgui-master" "imgui"
del imgui.zip

if exist "imgui" (
    echo [OK] ImGui instalado com sucesso!
    goto compile
) else (
    goto manual_imgui
)

:manual_imgui
cls
echo.
echo ================================================
echo  INSTALACAO MANUAL DO DEAR IMGUI
echo ================================================
echo.
echo Por favor, siga estes passos:
echo.
echo 1. Abra: https://github.com/ocornut/imgui
echo 2. Clique em [Code] - [Download ZIP]
echo 3. Extraia o ZIP
echo 4. Renomeie a pasta para "imgui"
echo 5. Mova para este diretorio
echo.
echo Estrutura esperada:
echo   projeto/
echo   ├── imgui/
echo   │   ├── imgui.h
echo   │   ├── imgui.cpp
echo   │   └── backends/
echo   └── kaisen_scripts.cpp
echo.
echo Pressione qualquer tecla apos instalar o ImGui...
pause >nul
goto download_imgui

:compile
cls
echo.
echo [3/4] Compilando projeto...
echo.

if not exist "build" mkdir build
cd build

if "%COMPILER%"=="MSVC" (
    echo Usando MSVC...
    cmake -G "Visual Studio 17 2022" -A x64 .. 2>nul
    if errorlevel 1 (
        cmake -G "Visual Studio 16 2019" -A x64 .. 2>nul
    )
    if errorlevel 1 (
        cmake -G "Visual Studio 15 2017" -A x64 .. 2>nul
    )
    
    cmake --build . --config Release
) else (
    echo Usando MinGW...
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .
)

if errorlevel 1 (
    echo.
    echo [ERRO] Falha na compilacao!
    echo.
    echo ALTERNATIVA: Use a versao Console
    echo Execute: compile_console.bat
    echo.
    cd ..
    pause
    exit /b 1
)

cd ..

if exist "build\Release\KaisenScripts.exe" (
    copy "build\Release\KaisenScripts.exe" "KaisenScripts.exe" >nul
) else if exist "build\KaisenScripts.exe" (
    copy "build\KaisenScripts.exe" "KaisenScripts.exe" >nul
)

:execute
cls
echo.
echo  ================================================
echo   COMPILACAO CONCLUIDA COM SUCESSO!
echo  ================================================
echo.
echo  Executavel criado: KaisenScripts.exe
echo.
echo [4/4] Deseja executar agora? (S/N)
set /p run=

if /i "%run%"=="S" (
    echo.
    echo Iniciando Kaisen Scripts...
    echo.
    start KaisenScripts.exe
)

echo.
echo ================================================
echo  CONCLUIDO!
echo ================================================
echo.
echo Executavel: KaisenScripts.exe
echo.
echo LEMBRE-SE:
echo - Execute sempre como Administrador
echo - Use apenas para fins educacionais
echo - Nao use em jogos online!
echo.
pause
exit /b 0
