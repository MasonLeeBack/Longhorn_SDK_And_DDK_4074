# Microsoft Developer Studio Project File - Name="ITBLDEF" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=ITBLDEF - Win32 x86 Debug MBCS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ITblDef.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ITblDef.mak" CFG="ITBLDEF - Win32 x86 Debug MBCS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ITBLDEF - Win32 x86 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ITBLDEF - Win32 x86 Debug MBCS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ITBLDEF - Win32 (ALPHA) axp Debug" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0



!IF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\ITBLDEF"
# PROP BASE Intermediate_Dir ".\ITBLDEF"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\x86_Debu"
# PROP Intermediate_Dir ".\x86_Debu"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_AFXEXT" /D "_AFXDLL" /c
# SUBTRACT BASE CPP /Fr /Yu
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_AFXEXT" /D "_AFXDLL" /Yu"modstandard.hpp" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD MTL /mktyplib203
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 dbuuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 modulecore.lib privlib.lib oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /pdb:none /map

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug MBCS"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\TEMPLAT0"
# PROP BASE Intermediate_Dir ".\TEMPLAT0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\x86_Debu\mbcs"
# PROP Intermediate_Dir ".\x86_Debu\mbcs"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_AFXEXT" /D "_AFXDLL" /c
# SUBTRACT BASE CPP /Fr /Yu
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_AFXEXT" /D "_AFXDLL" /Yu"modstandard.hpp" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD MTL /mktyplib203
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 dbuuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 modulecore.lib privlib.lib oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /pdb:none /map

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 (ALPHA) axp Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\TEMPLAT0"
# PROP BASE Intermediate_Dir ".\TEMPLAT0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\axp_debu\mbcs"
# PROP Intermediate_Dir ".\axp_debu\mbcs"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"modstandard.hpp" /MDd /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_AFXEXT" /D "_AFXDLL" /Yu"modstandard.hpp" /FD /MDd /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /alpha
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 modulecore.lib privlib.lib msad.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 modulecore.lib privlib.lib oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# SUBTRACT LINK32 /pdb:none /map

!ENDIF 

# Begin Target

# Name "ITBLDEF - Win32 x86 Debug"
# Name "ITBLDEF - Win32 x86 Debug MBCS"
# Name "ITBLDEF - Win32 (ALPHA) axp Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Modsrc\clib.cpp

!IF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug MBCS"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 (ALPHA) axp Debug"

NODEP_CPP_CLIB_=\
	".\col.hpp"\
	".\exterr.hpp"\
	".\iscfunc.h"\
	".\ist.h"\
	".\ledb.h"\
	".\ledberr.h"\
	".\lib.hpp"\
	".\modinfo.hpp"\
	".\ODClasses.hpp"\
	".\odcommon.hpp"\
	".\ODError.hpp"\
	".\ODMacros.hpp"\
	".\odstandard.hpp"\
	".\ODuleCore.h"\
	".\oledb.hpp"\
	".\oolingHooks.h"\
	".\parsestrm.hpp"\
	".\ransact.h"\
	".\rivcnst.h"\
	".\rivlib.h"\
	".\ropidl.h"\
	".\rvtrace.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	".\storage.hpp"\
	".\SuperLog.hpp"\
	".\table.hpp"\
	".\TMCommon.h"\
	".\transtn.hpp"\
	".\tree.hpp"\
	".\trings.h"\
	".\xtraLib.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Modsrc\DataSource.cpp

!IF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug MBCS"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 (ALPHA) axp Debug"

NODEP_CPP_DATAS=\
	".\ataSource.hpp"\
	".\clcommon.hpp"\
	".\col.hpp"\
	".\exterr.hpp"\
	".\iscfunc.h"\
	".\ist.h"\
	".\ledb.h"\
	".\ledberr.h"\
	".\llocator.hpp"\
	".\modinfo.hpp"\
	".\ODClasses.hpp"\
	".\odcommon.hpp"\
	".\ODError.hpp"\
	".\ODMacros.hpp"\
	".\odstandard.hpp"\
	".\ODuleCore.h"\
	".\oledb.hpp"\
	".\omsvcs.h"\
	".\oolingHooks.h"\
	".\parsestrm.hpp"\
	".\PropSet.hpp"\
	".\ransact.h"\
	".\rivcnst.h"\
	".\rivlib.h"\
	".\rivstd.h"\
	".\ropidl.h"\
	".\rovHooks.h"\
	".\roviderInfo.h"\
	".\rvtrace.h"\
	".\sdadc.h"\
	".\sdasc.h"\
	".\storage.hpp"\
	".\SuperLog.hpp"\
	".\table.hpp"\
	".\TMCommon.h"\
	".\transtn.hpp"\
	".\tree.hpp"\
	".\trings.h"\
	".\txdm.h"\
	".\vcprov.h"\
	".\VectorEx.hpp"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Modsrc\ExtraLib.cpp

!IF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug MBCS"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 (ALPHA) axp Debug"

NODEP_CPP_EXTRA=\
	".\col.hpp"\
	".\exterr.hpp"\
	".\iscfunc.h"\
	".\ist.h"\
	".\ledb.h"\
	".\ledberr.h"\
	".\modinfo.hpp"\
	".\ODClasses.hpp"\
	".\odcommon.hpp"\
	".\ODError.hpp"\
	".\ODMacros.hpp"\
	".\odstandard.hpp"\
	".\ODuleCore.h"\
	".\oledb.hpp"\
	".\oolingHooks.h"\
	".\parsestrm.hpp"\
	".\ransact.h"\
	".\rivcnst.h"\
	".\rivlib.h"\
	".\ropidl.h"\
	".\rvtrace.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	".\storage.hpp"\
	".\SuperLog.hpp"\
	".\table.hpp"\
	".\TMCommon.h"\
	".\transtn.hpp"\
	".\tree.hpp"\
	".\trings.h"\
	".\xtraLib.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Modsrc\ITBLDEF.CPP

!IF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug"

# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"modstandard.hpp"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug MBCS"

# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"modstandard.hpp"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 (ALPHA) axp Debug"

NODEP_CPP_ITBLD=\
	".\ataSource.hpp"\
	".\col.hpp"\
	".\exterr.hpp"\
	".\iscfunc.h"\
	".\ist.h"\
	".\ledb.h"\
	".\ledberr.h"\
	".\lib.hpp"\
	".\llocator.hpp"\
	".\modinfo.hpp"\
	".\ODClasses.hpp"\
	".\odcommon.hpp"\
	".\ODError.hpp"\
	".\ODMacros.hpp"\
	".\odstandard.hpp"\
	".\ODuleCore.h"\
	".\oledb.hpp"\
	".\oolingHooks.h"\
	".\parsestrm.hpp"\
	".\PropSet.hpp"\
	".\ransact.h"\
	".\rivcnst.h"\
	".\rivlib.h"\
	".\ropidl.h"\
	".\rovHooks.h"\
	".\roviderInfo.h"\
	".\rvtrace.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	".\storage.hpp"\
	".\SuperLog.hpp"\
	".\table.hpp"\
	".\TBLDEF.H"\
	".\TMCommon.h"\
	".\transtn.hpp"\
	".\tree.hpp"\
	".\trings.h"\
	".\VectorEx.hpp"\
	".\xtraLib.h"\
	
# ADD BASE CPP /Gt0 /Yu"modstandard.hpp"
# ADD CPP /Gt0 /Yu"modstandard.hpp"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Modsrc\res\ITblDef.rc
# ADD BASE RSC /l 0x409 /i "Modsrc\res"
# ADD RSC /l 0x409 /i "Modsrc\res" /i ".\Modsrc\res"
# End Source File
# Begin Source File

SOURCE=.\Modsrc\MODStandard.cpp

!IF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug"

# ADD CPP /Yc"modstandard.hpp"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug MBCS"

# ADD CPP /Yc"modstandard.hpp"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 (ALPHA) axp Debug"

NODEP_CPP_MODST=\
	".\ODClasses.hpp"\
	".\odcommon.hpp"\
	".\ODError.hpp"\
	".\ODMacros.hpp"\
	".\odstandard.hpp"\
	".\ODuleCore.h"\
	".\SuperLog.hpp"\
	".\TMCommon.h"\
	
# ADD BASE CPP /Gt0 /Yc"modstandard.hpp"
# ADD CPP /Gt0 /Yc"modstandard.hpp"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Modsrc\MODSTUB.CPP

!IF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug"

# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"modstandard.hpp"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug MBCS"

# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"modstandard.hpp"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 (ALPHA) axp Debug"

NODEP_CPP_MODSTU=\
	".\ODClasses.hpp"\
	".\odcommon.hpp"\
	".\ODError.hpp"\
	".\ODMacros.hpp"\
	".\odstandard.hpp"\
	".\ODuleCore.h"\
	".\SuperLog.hpp"\
	".\TMCommon.h"\
	
# ADD BASE CPP /Gt0 /Yu"modstandard.hpp"
# ADD CPP /Gt0 /Yu"modstandard.hpp"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Modsrc\MODSTUB.DEF
# End Source File
# Begin Source File

SOURCE=.\Modsrc\ProviderInfo.cpp

!IF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug MBCS"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 (ALPHA) axp Debug"

NODEP_CPP_PROVI=\
	".\ataSource.hpp"\
	".\clcommon.hpp"\
	".\col.hpp"\
	".\erviceComp.h"\
	".\exterr.hpp"\
	".\iscfunc.h"\
	".\ist.h"\
	".\ledb.h"\
	".\ledberr.h"\
	".\llocator.hpp"\
	".\modinfo.hpp"\
	".\ODClasses.hpp"\
	".\odcommon.hpp"\
	".\ODError.hpp"\
	".\ODMacros.hpp"\
	".\odstandard.hpp"\
	".\ODuleCore.h"\
	".\oledb.hpp"\
	".\omsvcs.h"\
	".\oolingHooks.h"\
	".\parsestrm.hpp"\
	".\PropSet.hpp"\
	".\ransact.h"\
	".\rivcnst.h"\
	".\rivlib.h"\
	".\rivstd.h"\
	".\ropidl.h"\
	".\rovHooks.h"\
	".\roviderInfo.h"\
	".\rvtrace.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\storage.hpp"\
	".\SuperLog.hpp"\
	".\table.hpp"\
	".\TMCommon.h"\
	".\transtn.hpp"\
	".\tree.hpp"\
	".\trings.h"\
	".\txdm.h"\
	".\vcintfs.h"\
	".\vcprov.h"\
	".\VectorEx.hpp"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Modsrc\ServiceComp.cpp

!IF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 x86 Debug MBCS"

!ELSEIF  "$(CFG)" == "ITBLDEF - Win32 (ALPHA) axp Debug"

NODEP_CPP_SERVI=\
	".\ataSource.hpp"\
	".\clcommon.hpp"\
	".\col.hpp"\
	".\erviceComp.h"\
	".\exterr.hpp"\
	".\iscfunc.h"\
	".\ist.h"\
	".\ledb.h"\
	".\ledberr.h"\
	".\llocator.hpp"\
	".\modinfo.hpp"\
	".\ODClasses.hpp"\
	".\odcommon.hpp"\
	".\ODError.hpp"\
	".\ODMacros.hpp"\
	".\odstandard.hpp"\
	".\ODuleCore.h"\
	".\oledb.hpp"\
	".\omsvcs.h"\
	".\oolingHooks.h"\
	".\parsestrm.hpp"\
	".\PropSet.hpp"\
	".\ransact.h"\
	".\rivcnst.h"\
	".\rivlib.h"\
	".\rivstd.h"\
	".\ropidl.h"\
	".\rovHooks.h"\
	".\roviderInfo.h"\
	".\rvtrace.h"\
	".\sdadc.h"\
	".\sdasc.h"\
	".\storage.hpp"\
	".\SuperLog.hpp"\
	".\table.hpp"\
	".\TMCommon.h"\
	".\transtn.hpp"\
	".\tree.hpp"\
	".\trings.h"\
	".\txdm.h"\
	".\vcintfs.h"\
	".\vcprov.h"\
	".\VectorEx.hpp"\
	

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Include\clib.hpp
# End Source File
# Begin Source File

SOURCE=.\Include\CPropSet.hpp
# End Source File
# Begin Source File

SOURCE=.\Include\CVectorEx.hpp
# End Source File
# Begin Source File

SOURCE=.\Include\DataSource.hpp
# End Source File
# Begin Source File

SOURCE=.\Include\ExtraLib.h
# End Source File
# Begin Source File

SOURCE=.\Include\ITBLDEF.H
# End Source File
# Begin Source File

SOURCE=.\Include\ProviderInfo.h
# End Source File
# Begin Source File

SOURCE=.\Include\ServiceComp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
