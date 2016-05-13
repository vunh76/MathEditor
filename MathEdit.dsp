# Microsoft Developer Studio Project File - Name="MathEdit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MathEdit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MathEdit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MathEdit.mak" CFG="MathEdit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MathEdit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MathEdit - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MathEdit", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MathEdit - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MathEdit - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MathEdit - Win32 Release"
# Name "MathEdit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\About.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MathEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MathEdit.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolBarBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBarBtnCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBarDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\About.h
# End Source File
# Begin Source File

SOURCE=.\EditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\MathEdit.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarBtn.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarBtnCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\mathsym\arrows.bmp
# End Source File
# Begin Source File

SOURCE=.\res\arrows.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\brace.bmp
# End Source File
# Begin Source File

SOURCE=.\res\brace.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\braces.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\coredata.bmp
# End Source File
# Begin Source File

SOURCE=.\res\coredata.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\derivative.bmp
# End Source File
# Begin Source File

SOURCE=.\res\derivative.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\dotsymb.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\equation.bmp
# End Source File
# Begin Source File

SOURCE=.\res\equation.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\frs.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\function.bmp
# End Source File
# Begin Source File

SOURCE=.\res\function.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\integral.bmp
# End Source File
# Begin Source File

SOURCE=.\res\integral.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\Integrals.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\lower_greek.bmp
# End Source File
# Begin Source File

SOURCE=.\res\lower_greek.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MathEdit.ico
# End Source File
# Begin Source File

SOURCE=.\res\MathEdit.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MathEditDoc.ico
# End Source File
# Begin Source File

SOURCE=.\mathsym\matrix.bmp
# End Source File
# Begin Source File

SOURCE=.\res\matrix.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\moresymb.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\Operator.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\pbyq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pbyq.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\prod.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prod.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\specialc.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\sum.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sum.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\upper_greek.bmp
# End Source File
# Begin Source File

SOURCE=.\res\upper_greek.bmp
# End Source File
# Begin Source File

SOURCE=.\mathsym\vector.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vector.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
