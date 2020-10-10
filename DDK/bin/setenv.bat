@echo off


if NOT "%DDKBUILDENV%"=="" goto :AlreadyDefinedError

REM
REM Get the root of the DDK from the user
REM
if "%1"=="" goto usage
set BASEDIR=%1
shift

@rem
@rem reasonable defaults
@rem

set _FreeBuild=true
set _IA64bit=false
set _AMD64bit=false
set _HalBuild=false
set _BscMake=FALSE
set _VersionedHeaders=FALSE
set _LatestOsTarget=wlh

REM This default value will be overridden if one of the legacy
REM build environments is invoked.
set _title=Windows Longhorn Preview

:NextArg
REM
REM Ways to get script usage
REM
if /I "%1"=="/?"     goto usage
if /I "%1"=="-?"     goto usage
if /I "%1"=="\?"     goto usage
if /I "%1"=="-help"  goto usage
if /I "%1"=="/help?" goto usage

REM
REM Valid target architectures
REM (undecoracted '64' implies IA-64)
REM
if /I "%1"=="64"     goto ArgOK
if /I "%1"=="amd64"  goto ArgOK
if /I "%1"=="I386"   goto ArgOK
if /I "%1"=="IA64"   goto ArgOK
if /I "%1"=="IA32"   goto ArgOK
if /I "%1"=="x86"    goto ArgOK
if /I "%1"=="x86-64" goto ArgOK

REM
REM Checked or Free builds
REM
if /I "%1"=="f"       goto ArgOK
if /I "%1"=="fre"     goto ArgOK
if /I "%1"=="free"    goto ArgOK
if /I "%1"=="c"       goto ArgOK
if /I "%1"=="chk"     goto ArgOK
if /I "%1"=="CHK"     goto ArgOK
if /I "%1"=="checked" goto ArgOK

REM
REM Valid target operating system versions
REM
if /I "%1"=="w2k"  goto ArgOK
if /I "%1"=="Wlh"  goto ArgOK
if /I "%1"=="WNet" goto ArgOK
if /I "%1"=="WXP"  goto ArgOK

REM
REM Valid subkit build environments
REM
if /I "%1"=="hal" goto ArgOK

REM
REM Final checks
REM
if /I "%1"=="bscmake" goto ArgOK
if /I "%1"=="hdr_ver" goto ArgOK
if NOT "%1"=="" goto usage
if "%1" == ""   goto :GetStarted

:ArgOK

if /I "%1"=="64"      set _IA64bit=true
if /I "%1"=="amd64"   set _AMD64bit=true
if /I "%1"=="I386"    set _IA32bit=true
if /I "%1"=="IA64"    set _IA64bit=true
if /I "%1"=="IA32"    set _IA32bit=true
if /I "%1"=="x86"     set _IA32bit=true
if /I "%1"=="x86-64"  set _AMD64bit=true

if /I "%1"=="f"       set _FreeBuild=true
if /I "%1"=="fre"     set _FreeBuild=true
if /I "%1"=="free"    set _FreeBuild=true
if /I "%1"=="c"       set _FreeBuild=false
if /I "%1"=="chk"     set _FreeBuild=false
if /I "%1"=="CHK"     set _FreeBuild=false
if /I "%1"=="checked" set _FreeBuild=false

if /I "%1"=="w2k"     set DDK_TARGET_OS=Win2K
if /I "%1"=="Wlh"     set DDK_TARGET_OS=WinLH
if /I "%1"=="WNet"    set DDK_TARGET_OS=WinNET
if /I "%1"=="WXP"     set DDK_TARGET_OS=WinXP

if /I "%1"=="hal"     set _HalBuild=true
if /I "%1"=="bscmake" set _BscMake=TRUE
if /I "%1"=="hdr_ver" set _VersionedHeaders=TRUE

shift
goto :NextArg

@rem
@rem OK, do the real stuff now
@rem

:GetStarted

set _NT_TOOLS_VERSION=0x700
set COFFBASE_TXT_FILE=%BASEDIR%\bin\coffbase.txt

@rem Make sure DDK_TARGET_OS is set to the default if not passed at the CMD line
if "%DDK_TARGET_OS%"=="" set DDK_TARGET_OS=WinLH

if /I "%DDK_TARGET_OS%"=="Win2K"    goto W2K
if /I "%DDK_TARGET_OS%"=="WinLH"    goto WLH
if /I "%DDK_TARGET_OS%"=="WinNET"   goto WNET
if /I "%DDK_TARGET_OS%"=="WinXP"    goto WXP
REM Fall thru to WLH by default


REM
REM Target OS specific settings
REM

:WLH
set _ddkspec=wlh
set _NT_TARGET_VERSION=0x600
goto END_OF_TARGETS

:WNET
echo Windows 2003 Server build environments are not supported in this preview release
goto :end

:WXP
echo Windows XP build environments are not supported in this preview release
goto :end

:W2K
echo Windows 2000 build environments are not supported in this preview release
goto :end

:END_OF_TARGETS

if "%_HalBuild%"=="false" set NT_UP=0
if "%_HalBuild%"=="true"  set _title=%_title% HAL Kit

REM
REM Target architectures section
REM

if "%PROCESSOR_ARCHITECTURE%"==""      set PROCESSOR_ARCHITECTURE=x86
if "%PROCESSOR_ARCHITECTURE%"=="x86"   set CPU=x86
if "%PROCESSOR_ARCHITECTURE%"=="IA64"  set CPU=IA64
if "%PROCESSOR_ARCHITECTURE%"=="AMD64" set CPU=AMD64
if "%CPU%"=="" goto cpuerror

if "%_AMD64bit%" == "true" goto setAMD64
if "%_IA64bit%"  == "true" goto setIA64

set PATH=%BASEDIR%\bin\x86;%PATH%
set BUILD_DEFAULT_TARGETS=-386
set _BUILDARCH=x86
goto envtest

:setAMD64
set _title=%_title% AMD64
set BUILD_DEFAULT_TARGETS=-AMD64
set _BUILDARCH=AMD64
set AMD64=1
set BUILD_OPTIONS=%BUILD_OPTIONS% ~imca ~e100bex ~toastpkg

if not "%PROCESSOR_ARCHITECTURE%"=="AMD64" goto amd64crosscompile
rem AMD64 Native builds
@ECHO WARNING: AMD64 Native compiling isn't supported. Using cross compilers.
REM goto envtest

:amd64crosscompile
rem X86 to AMD64 cross compile
set PATH=%BASEDIR%\bin\Win64\x86\amd64;%BASEDIR%\bin\x86;%PATH%
goto envtest

:setIA64
set _title=%_title% IA64
set BUILD_DEFAULT_TARGETS=-IA64
set _BUILDARCH=IA64
set IA64=1

if not "%PROCESSOR_ARCHITECTURE%"=="IA64" goto ia64crosscompile
rem IA-64 Native builds
set PATH=%BASEDIR%\bin\IA64\;%PATH%
goto envtest

:ia64crosscompile
rem X86 to IA-64 cross compile
set PATH=%BASEDIR%\bin\Win64\x86;%BASEDIR%\bin\x86;%PATH%

REM
REM Checked v. Free section
REM
:envtest
if NOT "%DDKBUILDENV%"=="" goto UseExistingDDKBuildSetting
if "%_FreeBuild%" == "true" goto free
goto checked

:UseExistingDDKBuildSetting
if /I "%DDKBUILDENV%"=="FRE"     goto free
if /I "%DDKBUILDENV%"=="FREE"    goto free
if /I "%DDKBUILDENV%"=="CHK"     goto checked
if /I "%DDKBUILDENV%"=="CHECKED" goto checked
REM Clear this to avoid possibly tainting the env. with a bad value
set DDKBUILDENV=
goto usage

:free
rem set up an NT free build environment
set _title=%_title% Free Build Environment
set BUILD_ALT_DIR=fre_%_ddkspec%_%_BUILDARCH%
set NTDBGFILES=1
set NTDEBUG=ntsdnodbg
set NTDEBUGTYPE=windbg
set MSC_OPTIMIZATION=
set DDKBUILDENV=fre
goto done

:checked
rem set up an NT checked build environment
set _title=%_title% Checked Build Environment
set BUILD_ALT_DIR=chk_%_ddkspec%_%_BUILDARCH%
set NTDBGFILES=1
set NTDEBUG=ntsd
set NTDEBUGTYPE=both
set MSC_OPTIMIZATION=/Od /Oi
set DDKBUILDENV=chk

REM Turn on deprecated funciton checking by default for checked
REM WLH build environments.
if /I "%DDK_TARGET_OS%"=="WinLH" (
    set DEPRECATE_DDK_FUNCTIONS=1
)

:done
@rem buffer_overflow_checks only on for x86 Server 2003 and all LH BE
if "%DDK_TARGET_OS%" =="Win2K" goto no_bo_checks
if "%DDK_TARGET_OS%" =="WinXP" goto no_bo_checks
if "%DDK_TARGET_OS%" =="WinLH" set BUFFER_OVERFLOW_CHECKS=1
if "%_BUILDARCH%"=="x86" set BUFFER_OVERFLOW_CHECKS=1
:no_bo_checks


REM
REM Begin common section
REM

set PROJECT_ROOT=%BASEDIR%\src

set PREFAST_ROOT=%BASEDIR%\bin\x86\prefast
set Path=%BASEDIR%\bin;%PREFAST_ROOT%\scripts;%path%

set Lib=%BASEDIR%\lib
set Include=%BASEDIR%\inc\%_ddkspec%
set WPP_CONFIG_PATH=%BASEDIR%\bin\wppconfig

set NTMAKEENV=%BASEDIR%\bin
set BUILD_MAKE_PROGRAM=nmake.exe
set BUILD_DEFAULT=-ei -nmake -i
set BUILD_MULTIPROCESSOR=1
set NO_BINPLACE=TRUE
if /I "%_BscMake%" NEQ "TRUE" set NO_BROWSER_FILE=TRUE
set PUBLISH_CMD=@echo Publish not available...

if "%tmp%"=="" set tmp=%TEMP%

set NEW_CRTS=1

set CRT_INC_PATH=%BASEDIR%\inc\crt
@rem "\atl$(ATL_VER)" will be appended to the ATL_INC_PATH/ATL_INC_ROOT
@rem  by makefile.def
set ATL_INC_PATH=%BASEDIR%\inc
set ATL_INC_ROOT=%BASEDIR%\inc
set MFC_INCLUDES=%BASEDIR%\inc\mfc42
set PROCESSOR_INC_PATH=%BASEDIR%\inc\processor

if "%_VersionedHeaders%"=="TRUE" (
    set SDK_INC_PATH=%BASEDIR%\inc\%_LatestOsTarget%
    set DDK_INC_PATH=%BASEDIR%\inc\ddk\%_LatestOsTarget%
    set WDM_INC_PATH=%BASEDIR%\inc\ddk\wdm\%_LatestOsTarget%
    set OAK_INC_PATH=%BASEDIR%\inc\%_LatestOsTarget%
    set IFSKIT_INC_PATH=%BASEDIR%\inc\ifs\%_LatestOsTarget%
    set HALKIT_INC_PATH=%BASEDIR%\inc\hal\%_LatestOsTarget%
    set DRIVER_INC_PATH=%BASEDIR%\inc\ddk\%_LatestOsTarget%
) else (
    set SDK_INC_PATH=%BASEDIR%\inc\%_ddkspec%
    set DDK_INC_PATH=%BASEDIR%\inc\ddk\%_ddkspec%
    set WDM_INC_PATH=%BASEDIR%\inc\ddk\wdm\%_ddkspec%
    set OAK_INC_PATH=%BASEDIR%\inc\%_ddkspec%
    set IFSKIT_INC_PATH=%BASEDIR%\inc\ifs\%_ddkspec%
    set HALKIT_INC_PATH=%BASEDIR%\inc\hal\%_ddkspec%
    set DRIVER_INC_PATH=%BASEDIR%\inc\ddk\%_ddkspec%
)

set SDK_LIB_DEST=%BASEDIR%\lib\%_ddkspec%
set DDK_LIB_DEST=%SDK_LIB_DEST%
set IFSKIT_LIB_DEST=%SDK_LIB_DEST%

set SDK_LIB_PATH=%BASEDIR%\lib\%_ddkspec%\*
set DDK_LIB_PATH=%SDK_LIB_PATH%
set HALKIT_LIB_PATH=%SDK_LIB_PATH%
set PROCESSOR_LIB_PATH=%SDK_LIB_PATH%
set IFSKIT_LIB_PATH=%SDK_LIB_PATH%

set CRT_LIB_PATH=%BASEDIR%\lib\crt\*
set ATL_LIB_PATH=%BASEDIR%\lib\atl\*
set MFC_LIB_PATH=%BASEDIR%\lib\mfc\*

REM Don't require coffbase.txt entries
set LINK_LIB_IGNORE=4198

REM Don't do font mapping by default.
set RCNOFONTMAP=1

if "%_IA64bit%"  == "true" Goto SkipToolSettings
if "%_AMD64bit%" == "true" Goto SkipToolSettings
if "%_HalBuild%" == "true" Goto SkipToolSettings
REM set _ML_=/Zvc6
REM set _CL_=/Ztmp
REM set _LINK_=/Tmp

:SkipToolSettings

set USERNAME=WinDDK
if "%_VersionedHeaders%"=="TRUE" (
    set _title=%_title% [Versioned Headers]
    set BUILD_ALT_DIR=%BUILD_ALT_DIR%_vh
)
title %_title%
if "%OS%" == "Windows_NT" goto WinNT
if not "%OS%" == "Windows_NT" goto Win9x
goto end

:WinNT
cd /d %BASEDIR%
doskey /macrofile=%BASEDIR%\bin\generic.mac
doskey /macrofile=%BASEDIR%\bin\ddktree.mac

goto end


%BASEDIR%\bin\x86\MkCDir %BASEDIR%
if exist %BASEDIR%\bin\ChngeDir.bat call %BASEDIR%\bin\ChngeDir.bat
goto end


:AlreadyDefinedError
echo.
echo ERROR: This window already has the DDK build environment set.  Please open 
echo        a new window if you want to change or reset your build environment.
echo.

goto end

:cpuerror

echo.
echo Error: PROCESSOR_ARCHITECTURE environment variable not recognized.
echo.
echo.

goto end

:Win9x
@echo ERROR: The Windows DDK no longer supports Windows 95/98/Me as a development
@echo        platform.
goto end

:usage
echo.
echo Usage: "setenv <directory> [fre|chk] [64|AMD64] [hal] [WXP|WNET|W2K] [bscmake]"
echo.
echo   By default, setenv.bat will set the environment variable NO_BROWSER_FILE.
echo   Using the "bscmake" option will cause setenv.bat to not define this variable.
echo.
echo   Example:  setenv d:\ddk chk        set checked environment
echo   Example:  setenv d:\ddk            set free environment for Windows Server 2003 (default)
echo   Example:  setenv d:\ddk fre WNET   Same
echo   Example:  setenv d:\ddk fre 64     sets IA64 bit free environment
echo   Example:  setenv d:\ddk fre AMD64  sets AMD64 bit free environment
echo   Example:  setenv d:\ddk fre WXP    sets free build environment for Windows XP
echo   Example:  setenv d:\ddk hal        sets free hal environment
echo   Example:  setenv d:\ddk fre hal    Same
echo.
echo.

:end
set _FreeBuild=
set _AMD64bit=
set _IA64bit=
set _HalBuild=
set _ddkspec=
set _title=
set _BscMake=
set _VersionedHeaders=
set _LatestOsTarget=
REM Clearing undefined env. vars may set ERRORLEVEL to 1, make sure it's 0.
set ERRORLEVEL=0

