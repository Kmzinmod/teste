@echo off
echo ========================================
echo   KAISEN SCRIPTS - Console Version
echo   Compilacao Simples (sem ImGui)
echo ========================================
echo.

REM Compilar versão console (não precisa de ImGui)
echo [INFO] Compilando versao console...
echo.

REM Tentar com cl (MSVC)
where cl >nul 2>nul
if %errorlevel% equ 0 (
    echo [OK] Compilador MSVC encontrado!
    cl /EHsc /std:c++17 /O2 kaisen_scripts_console.cpp /Fe:KaisenScriptsConsole.exe /link user32.lib gdi32.lib
    
    if errorlevel 0 (
        echo.
        echo [OK] Compilacao concluida!
        echo Executavel: KaisenScriptsConsole.exe
        echo.
        del *.obj 2>nul
        
        echo Deseja executar agora? (S/N)
        set /p run=
        if /i "%run%"=="S" (
            start KaisenScriptsConsole.exe
        )
        goto :end
    )
)

REM Tentar com g++ (MinGW)
where g++ >nul 2>nul
if %errorlevel% equ 0 (
    echo [OK] Compilador MinGW encontrado!
    g++ -std=c++17 -O2 kaisen_scripts_console.cpp -o KaisenScriptsConsole.exe -lgdi32 -luser32
    
    if %errorlevel% equ 0 (
        echo.
        echo [OK] Compilacao concluida!
        echo Executavel: KaisenScriptsConsole.exe
        echo.
        
        echo Deseja executar agora? (S/N)
        set /p run=
        if /i "%run%"=="S" (
            start KaisenScriptsConsole.exe
        )
        goto :end
    )
)

echo.
echo [ERRO] Nenhum compilador encontrado!
echo.
echo Por favor, instale um dos seguintes:
echo 1. Visual Studio (inclui MSVC)
echo 2. MinGW-w64
echo.
echo Ou use o prompt do Visual Studio Developer Command Prompt
echo.

:end
pause
