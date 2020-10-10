@echo off

echo.
echo      Configures NDIS Test on Win2k, WinXP, Win2k3 and Longhorn for the LDK
echo.

if "%1"=="" goto usage

:install

if "%PROCESSOR_ARCHITECTURE%"=="x86" goto configx86
if "%PROCESSOR_ARCHITECTURE%"=="IA64" goto configia64
if "%PROCESSOR_ARCHITECTURE%"=="AMD64" goto configamd64

goto end_msg


rem Configures NDISTest for x86
:configx86
echo.
goto end_msg


rem Configures NDISTest for ia64
:configia64
rmdir /s /q %1\scripts\mini6
goto end_msg


rem Configures NDISTest for amd64
:configamd64
rmdir /s /q %1\scripts\mini6
goto end_msg

:end_msg
    echo.
    echo.
    echo.
    echo                +----------------------------+
    echo                  NDIS Test Config complete
    echo                +----------------------------+
    echo.
    echo       All documentation has been moved to the "Documentation" 
    echo            option of the "help" menu of ndtest.exe
    echo.
    goto end

:usage
    echo.
    echo Usage: ldksetup targetfolder
    echo.
    echo.
    goto end

:end

