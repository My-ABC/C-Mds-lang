@echo off
setlocal enabledelayedexpansion

set VCToolsPath=C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build

if exist "%VCToolsPath%\vcvars64.bat" (
    call "%VCToolsPath%\vcvars64.bat" > nul 2>&1
) else (
    echo Error: Visual Studio Build Tools not found
    exit /b 1
)

:: ========== 配置 ==========
set SOURCES=src\*.c
set INCLUDE_PATHS=/Isrc /Iinclude

:: 配置输出目录
set OUT_DIR=build
set DEBUG=

if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

if "%1" == "clean" goto clean
if "%1" == "-d" goto debug

:release
echo Building in RELEASE mode...
set CFLAGS=/nologo /O2 /W3 /DNDEBUG %INCLUDE_PATHS%
set OUTPUT=%OUT_DIR%\Release\main.exe
set OBJ_DIR=%OUT_DIR%\Release
goto compile

:debug
echo Building in DEBUG mode...
set CFLAGS=/nologo /Od /Zi /W3 /D_DEBUG %INCLUDE_PATHS%
set OUTPUT=%OUT_DIR%\Debug\main.exe
set OBJ_DIR=%OUT_DIR%\Debug
shift
goto compile

:compile
:: 创建输出目录
if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"

:: 编译链接
cl %CFLAGS% /Fo%OBJ_DIR%\ /Fd%OBJ_DIR%\main.pdb /Fe%OUTPUT% %SOURCES% /link /ILK:%OBJ_DIR%\main.ilk /PDB:%OBJ_DIR%\main.pdb

if %errorlevel% == 0 (
    echo.
    echo ========================================
    echo Build succeeded: %OUTPUT%
    echo ========================================
) else (
    echo Build failed
)
goto end

:clean
echo Cleaning...
if exist "%OUT_DIR%" rmdir /s /q "%OUT_DIR%"
del /q *.pdb 2>nul
del /q *.ilk 2>nul
echo Clean completed
goto end

:end