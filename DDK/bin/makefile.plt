#
# If not defined, specify where to get incs and libs.
#

!IFNDEF _NTROOT
_NTROOT=\nt
!ENDIF

!IFNDEF BASEDIR
BASEDIR=$(_NTDRIVE)$(_NTROOT)
!ENDIF

# A couple of overrides

!ifndef _NT_TARGET_VERSION # Default to current OS version
_NT_TARGET_VERSION = 0x600
!endif

!ifndef _NT_TOOLS_VERSION # Default to current VC version
_NT_TOOLS_VERSION = 0x700
!endif

!ifndef SDK_PATH
SDK_PATH = $(BASEDIR)\public\sdk
!endif

!ifndef SDK_INC_PATH
SDK_INC_PATH = $(SDK_PATH)\inc
!endif

!ifndef SDK_REF_PATH
SDK_REF_PATH = $(SDK_PATH)\ref
!endif

!ifndef SDK_INC16_PATH
SDK_INC16_PATH = $(SDK_PATH)\inc16
!endif

!ifndef SDK_LIB_DEST
SDK_LIB_DEST = $(SDK_PATH)\lib
!endif

!ifndef SDK_LIB_PATH
SDK_LIB_PATH = $(SDK_LIB_DEST)\*
!endif

!ifndef SDK_LIB16_PATH
SDK_LIB16_PATH=$(SDK_PATH)\lib16
!endif

!ifndef DDK_PATH
DDK_PATH = $(BASEDIR)\public\ddk
!endif

!ifndef DDK_INC_PATH
DDK_INC_PATH = $(DDK_PATH)\inc
!endif

!ifndef DDK_LIB_DEST
DDK_LIB_DEST = $(DDK_PATH)\lib
!endif

!ifndef DDK_LIB_PATH
DDK_LIB_PATH = $(DDK_LIB_DEST)\*
!endif

!ifndef IFSKIT_PATH
IFSKIT_PATH = $(BASEDIR)\public\ifskit
!endif

!ifndef IFSKIT_INC_PATH
IFSKIT_INC_PATH = $(IFSKIT_PATH)\inc
!endif

!ifndef IFSKIT_LIB_DEST
IFSKIT_LIB_DEST = $(IFSKIT_PATH)\lib
!endif

!ifndef IFSKIT_LIB_PATH
IFSKIT_LIB_PATH = $(IFSKIT_LIB_DEST)\*
!endif

!ifndef HALKIT_PATH
HALKIT_PATH = $(BASEDIR)\public\halkit
!endif

!ifndef HALKIT_INC_PATH
HALKIT_INC_PATH = $(HALKIT_PATH)\inc
!endif

!ifndef HALKIT_LIB_DEST
HALKIT_LIB_DEST = $(HALKIT_PATH)\lib
!endif

!ifndef HALKIT_LIB_PATH
HALKIT_LIB_PATH = $(HALKIT_LIB_DEST)\*
!endif

!ifndef PROCESSOR_PATH
PROCESSOR_PATH = $(BASEDIR)\public\processorkit
!endif

!ifndef PROCESSOR_INC_PATH
PROCESSOR_INC_PATH = $(PROCESSOR_PATH)\inc
!endif

!ifndef PROCESSOR_LIB_DEST
PROCESSOR_LIB_DEST = $(PROCESSOR_PATH)\lib
!endif

!ifndef PROCESSOR_LIB_PATH
PROCESSOR_LIB_PATH = $(PROCESSOR_LIB_DEST)\*
!endif

!ifndef WDM_INC_PATH
WDM_INC_PATH = $(DDK_INC_PATH)\wdm
!endif

!ifndef CRT_INC_PATH
CRT_INC_PATH = $(SDK_INC_PATH)\crt
!endif

!ifndef IOSTREAMS_INC_PATH
IOSTREAMS_INC_PATH = $(SDK_INC_PATH)\crt\iostreams
!endif

!ifndef STL6_INC_PATH
STL6_INC_PATH = $(SDK_INC_PATH)\crt\stl60
!endif

!ifndef STL7_INC_PATH
STL7_INC_PATH = $(SDK_INC_PATH)\crt\stl70
!endif

!ifndef CRT_LIB_PATH
CRT_LIB_PATH = $(SDK_LIB_PATH)
!endif

!ifndef OAK_INC_PATH
OAK_INC_PATH = $(BASEDIR)\public\oak\inc
!endif

!ifndef ATL_LIB_PATH
ATL_LIB_PATH=$(SDK_LIB_PATH)
!endif

!ifndef MFC_LIB_PATH
MFC_LIB_PATH=$(SDK_LIB_PATH)
!endif

# "mfc$(MFC_VER)" will be appended to this in makefile.def to
# create MFC_INC_PATH
!ifndef MFC_INC_ROOT
MFC_INC_ROOT=$(SDK_INC_PATH)
!endif

# "atl$(ATL_VER)" will be appended to this in makefile.def to
# create ATL_INC_PATH
!ifndef ATL_INC_ROOT
ATL_INC_ROOT=$(SDK_INC_PATH)
!endif

!ifndef WPP_CONFIG_PATH
# If this ever changes you must change the DDK's setenv.bat
WPP_CONFIG_PATH = $(BASEDIR)\tools\WppConfig
!endif

!ifndef PUBLIC_INTERNAL_PATH
PUBLIC_INTERNAL_PATH = $(BASEDIR)\public\internal
!endif

COPYRIGHT_STRING = Copyright (c) Microsoft Corporation. All rights reserved.

# debugging support
!if defined(BUILD_DEBUG)
TYPE=rem
NOECHO=
!else
TYPE=@type
NOECHO=@
!endif

!ifndef PUBLISH_CMD
PUBLISH_CMD=$(NOECHO)perl $(NTMAKEENV)\publish.pl publish.log
!endif

!ifndef BINDROP_CMD
! ifdef NOLINK
# Only drop binaries if we are linking in this pass.
BINDROP_CMD=rem No bindrop pass during link
!else
BINDROP_CMD=perl $(NTMAKEENV)\publish.pl $(_PROJECT_)_publish.log
!endif
!endif

!ifndef BUILD_PASS
# Old build.exe.  Guess the correct pass.
!ifdef PASS0ONLY
BUILD_PASS=PASS0
!elseif defined(LINKONLY)
BUILD_PASS=PASS2
!elseif defined(NOLINK) && !defined(PASS0ONLY)
BUILD_PASS=PASS1
!else
# catch all - someone used build -z or build -2
BUILD_PASS=PASSALL
!endif
!endif

#
# Set the flag which indicates whether we should be publishing binaries
# to 0 by default.  the project.mk file is responsible for parsing
# BINARY_PUBLISH_PROJECTS to determine if its value should be changed.
#

BINPUBLISH=0

#
# Define global project paths.
#

!if exists($(NTMAKEENV)\projects.inc)
!include $(NTMAKEENV)\projects.inc
!endif

!if exists($(NTMAKEENV)\..\testsrc\projects.inc)
!include $(NTMAKEENV)\..\testsrc\projects.inc
!else
!ifdef NTTESTENV
!include $(NTMAKEENV)\projects.tst.inc
!endif
!endif

#
# Find and include the project configuration file.
#

!if exists(.\project.mk)
_PROJECT_MK_PATH=.
!elseif exists(..\project.mk)
_PROJECT_MK_PATH=..
!elseif exists(..\..\project.mk)
_PROJECT_MK_PATH=..\..
!elseif exists(..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..
!elseif exists(..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..
!elseif exists(..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..
!elseif exists(..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..
!elseif exists(..\..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..\..
!elseif exists(..\..\..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..\..\..
!elseif exists(..\..\..\..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..\..\..\..
!elseif exists(..\..\..\..\..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..\..\..\..\..
!elseif exists(..\..\..\..\..\..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..\..\..\..\..\..
!elseif exists(..\..\..\..\..\..\..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..\..\..\..\..\..\..
!elseif exists(..\..\..\..\..\..\..\..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..\..\..\..\..\..\..\..
!elseif exists(..\..\..\..\..\..\..\..\..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..\..\..\..\..\..\..\..\..
!elseif exists(..\..\..\..\..\..\..\..\..\..\..\..\..\..\..\project.mk)
_PROJECT_MK_PATH=..\..\..\..\..\..\..\..\..\..\..\..\..\..\..
!endif

!if "$(_PROJECT_MK_PATH)" != ""
#!message "Including $(_PROJECT_MK_PATH)\project.mk"
!include $(_PROJECT_MK_PATH)\project.mk
!if exists($(_PROJECT_MK_PATH)\myproject.mk)
!include $(_PROJECT_MK_PATH)\myproject.mk
!endif
!else
#!message "Unable to find project.mk. Update makefile.plt or create project.mk."
!endif

!IFDEF _PROJECT_

PROJECT_ROOT=$(BASEDIR)\$(_PROJECT_)
PROJECT_PUBLIC_PATH=$(PUBLIC_INTERNAL_PATH)\$(_PROJECT_)

# for the test projects, enlisted in $(BASEDIR)\testsrc\<project>,
# redefine this to rm "\testsrc" so we don't see it in public\internal
!IFDEF _PROJ_
PROJECT_PUBLIC_PATH=$(PUBLIC_INTERNAL_PATH)\$(_PROJ_)
!ENDIF

PROJECT_INC_PATH=$(PROJECT_PUBLIC_PATH)\inc
PROJECT_REF_PATH=$(PROJECT_PUBLIC_PATH)\ref
PRIVATE_INC_PATH=$(PROJECT_INC_PATH)
PROJECT_LIB_DEST=$(PROJECT_PUBLIC_PATH)\lib
PROJECT_LIB_PATH=$(PROJECT_LIB_DEST)\$(TARGET_DIRECTORY)
PROJECT_INF_PATH=$(PROJECT_PUBLIC_PATH)\inf

!ELSE
#!message "ERROR: _PROJECT_ is not defined. Should be defined in project.mk."
!ENDIF

#
# If not defined, define the build message banner.
#

!IFNDEF BUILDMSG
BUILDMSG=
!ENDIF

!if ("$(NTDEBUG)" == "") || ("$(NTDEBUG)" == "ntsdnodbg")
FREEBUILD=1
! ifndef BUILD_TYPE
BUILD_TYPE=fre
! endif
!else
FREEBUILD=0
! ifndef BUILD_TYPE
BUILD_TYPE=chk
! endif
!endif


# Allow alternate object directories.

!if !defined(BUILD_ALT_DIR) && defined(CHECKED_ALT_DIR) && !$(FREEBUILD)
BUILD_ALT_DIR=d
!endif

_OBJ_DIR = obj$(BUILD_ALT_DIR)

#
# define a simple macro that can be used for the object subdir in makefile.inc/sources files
#
O = $(_OBJ_DIR)\$(TARGET_DIRECTORY)

#
# Determine which target is being built (i386 or ia64) and define
# the appropriate target variables.
#

!IFNDEF 386
386=0
!ENDIF

!IFNDEF AMD64
AMD64=0
!ENDIF

!IFNDEF PPC
PPC=0
!ENDIF

!IFNDEF MPPC
MPPC=0
!ENDIF

!IFNDEF IA64
IA64=0
!ENDIF

!IFNDEF ARM
ARM=0
!ENDIF

# Disable for now.
MIPS=0
AXP64=0
ALPHA=0

#
# Default to building for the i386 target, if no target is specified.
#

!IF !$(386)
! IF !$(AMD64)
!  IF !$(MPPC)
!   IF !$(IA64)
!    IF !$(ARM)
386=1
!    ENDIF
!   ENDIF
!  ENDIF
! ENDIF
!ENDIF

#
# Define the target platform specific information.
#

!if $(386)

ASM_SUFFIX=asm
ASM_INCLUDE_SUFFIX=inc

TARGET_BRACES=

!ifdef SUBSTITUTE_386_CC
TARGET_CPP=$(SUBSTITUTE_386_CC)
!else
TARGET_CPP=cl
!endif

TARGET_DEFINES=-Di386 -D_X86_
TARGET_DIRECTORY=i386
TLB_SWITCHES=/tlb
!ifndef _NTTREE
! ifdef _NTX86TREE
_NTTREE=$(_NTX86TREE)
! elseif defined(_NT386TREE)
_NTTREE=$(_NT386TREE)
! endif
!endif

VCCOM_SUPPORTED=1
SCP_SUPPORTED=1
WIN64=0
PLATFORM_MFC_VER=0x0600
MACHINE_TYPE=ix86
ANSI_ANNOTATION=0
TARGET_CSC=csc

!elseif $(AMD64)

ASM_SUFFIX=asm
ASM_INCLUDE_SUFFIX=inc

TARGET_BRACES=
TARGET_CPP=cl
TARGET_DEFINES=-D_AMD64_ -D_WIN64 -D_AMD64_WORKAROUND_
TARGET_DIRECTORY=amd64
TLB_SWITCHES=/tlb
!ifndef HOST_TARGETCPU
HOST_TARGETCPU=i386
!endif

!ifndef _NTTREE
! ifdef _NTAMD64TREE
_NTTREE=$(_NTAMD64TREE)
! endif
!endif

VCCOM_SUPPORTED=1
SCP_SUPPORTED=0
WIN64=1
PLATFORM_MFC_VER=0x0600
MACHINE_TYPE=amd64
ANSI_ANNOTATION=0

!elseif $(MPPC)

ASM_SUFFIX=s
ASM_INCLUDE_SUFFIX=h

TARGET_BRACES=-B
TARGET_CPP=cl
TARGET_DEFINES=-DMPPC -D_MPPC_
TARGET_DIRECTORY=mppc
TLB_SWITCHES=/tlb
WIN64=0
PLATFORM_MFC_VER=0x0421
MACHINE_TYPE=mppc

!ifndef _NTTREE
! ifdef _NTMPPCTREE
_NTTREE=$(_NTMPPCTREE)
! endif
!endif
ANSI_ANNOTATION=1

!elseif $(IA64)

ASM_SUFFIX=s
ASM_INCLUDE_SUFFIX=h

TARGET_BRACES=-B
TARGET_CPP=cl
TARGET_DEFINES=-DIA64 -D_IA64_
TARGET_DIRECTORY=ia64
TLB_SWITCHES=/tlb
# default to X86 for now
!ifndef HOST_TARGETCPU
HOST_TARGETCPU=i386
!endif

!ifndef _NTTREE
! ifdef _NTIA64TREE
_NTTREE=$(_NTIA64TREE)
! endif
!endif

WIN64=1
PLATFORM_MFC_VER=0x0600
SCP_SUPPORTED=0
MACHINE_TYPE=ia64
ANSI_ANNOTATION=0

!elseif $(ARM)

ASM_SUFFIX=s
ASM_INCLUDE_SUFFIX=inc

TARGET_BRACES=
TARGET_CPP=clarm
TARGET_DEFINES=-D_ARM_
TARGET_DIRECTORY=arm
TLB_SWITCHES=/tlb
!ifndef HOST_TARGETCPU
HOST_TARGETCPU=i386
!endif

!ifndef _NTTREE
! ifdef _NTARMTREE
_NTTREE=$(_NTARMTREE)
! endif
!endif

VCCOM_SUPPORTED=0
SCP_SUPPORTED=0
WIN64=0
PLATFORM_MFC_VER=0x0600
MACHINE_TYPE=arm
ANSI_ANNOTATION=0

!else
!error Must define the target as 386, mppc ia64, amd64, or arm.
!endif

#
#  These flags don't depend on i386 etc. however have to be in this file.
#
#  MIDL_OPTIMIZATION is the optimization flag set for the current NT.
#  MIDL_OPTIMIZATION_NO_ROBUST is the current optimization without robust.
#
!ifdef MIDL_PROTOCOL
MIDL_PROTOCOL_DEFAULT=-protocol $(MIDL_PROTOCOL)
!else
# MIDL_PROTOCOL_DEFAULT=-protocol all
!endif

!IFNDEF MIDL_OPTIMIZATION
MIDL_OPTIMIZATION=-Oicf -robust -error all $(MIDL_PROTOCOL_DEFAULT)
!ENDIF
MIDL_OPTIMIZATION_NO_ROBUST=-Oicf -error all -no_robust
MIDL_OPTIMIZATION_NT4=-Oicf -error all -no_robust
MIDL_OPTIMIZATION_NT5=-Oicf -robust -error all $(MIDL_PROTOCOL_DEFAULT)
!ifdef SUBSTITUTE_MIDL_CC
MIDL_CPP=$(SUBSTITUTE_MIDL_CC)
!else
MIDL_CPP=$(TARGET_CPP)
!endif
MIDL_FLAGS=$(TARGET_DEFINES) -D_WCHAR_T_DEFINED -nologo 

#
# If not defined, simply set to default
#

!IFNDEF HOST_TARGETCPU
HOST_TARGETCPU=$(TARGET_DIRECTORY)
!ENDIF

! if $(WIN64)
MIDL_ALWAYS_GENERATE_STUBS=1
! else
MIDL_ALWAYS_GENERATE_STUBS=0
! endif

CLEANSE_PUBLISHED_HDR=copy

PATH_TOOLS16=$(BASEDIR)\tools\tools16

# If a build path is defined, use it.

!ifdef BUILD_PATH
PATH=$(BUILD_PATH)
!endif

BINPLACE_PLACEFILE_DIR=$(NTMAKEENV)

!if exist ($(BASEDIR)\__blddate__)
!include $(BASEDIR)\__blddate__
!endif

!if exist ($(BASEDIR)\__bldnum__)
!include $(BASEDIR)\__bldnum__
!endif

ASMMETA_JS=cscript.exe /E:jscript /nologo $(RAZZLETOOLPATH)\asmmeta.js

!if [set O=$(O)]
!endif
!if [set _OBJ_DIR=$(_OBJ_DIR)]
!endif

#
# Form this particularly so build.exe reports errors.
#
BUILD_ERROR_MSG=NMAKE :ERROR $(MAKEDIR):
BUILD_WARNING_MSG=WARNING : WARNING $(MAKEDIR):

BUILD_ERROR_MSG_MULTIPLE_LINES=NMAKE :ERROR
BUILD_WARNING_MSG_MULTIPLE_LINES=WARNING : WARNING

!if \
 [set BUILD_ERROR_MSG=$(BUILD_ERROR_MSG)] && \
 [set BUILD_ERROR_MSG_MULTIPLE_LINES=$(BUILD_ERROR_MSG_MULTIPLE_LINES)] && \
 [set BUILD_WARNING_MSG=$(BUILD_WARNING_MSG)] && \
 [set BUILD_WARNING_MSG_MULTIPLE_LINES=$(BUILD_WARNING_MSG_MULTIPLE_LINES)]
!endif

!if defined(BUILD_DEBUG)
BUILD_NOKEEP=KEEP
!else
BUILD_NOKEEP=NOKEEP
!endif

!if "$(BUILD_COMPLUS_INSTALLROOT)" != ""
COMPLUS_INSTALLROOT=$(BUILD_COMPLUS_INSTALLROOT)
!if [set COMPLUS_INSTALLROOT=$(BUILD_COMPLUS_INSTALLROOT)]
!endif
!endif

!if "$(SDK_INC_PATH)" != "" && exist($(SDK_INC_PATH)\ntverpmk.inc)
!include $(SDK_INC_PATH)\ntverpmk.inc
!endif

!if "$(BASEDIR)" != "" && exist($(BASEDIR)\buildmachinetag.txt)
!include $(BASEDIR)\buildmachinetag.txt
!endif

!if "$(BASE_LIB_PATH)" != "" && exist($(BASE_LIB_PATH)\versionsmk.inc)
!include $(BASE_LIB_PATH)\versionsmk.inc
!elseif "$(PUBLIC_INTERNAL_PATH)" != "" && exist($(PUBLIC_INTERNAL_PATH)\versionsmk.inc)
!include $(PUBLIC_INTERNAL_PATH)\versionsmk.inc
!endif

