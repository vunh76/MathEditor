# Microsoft Developer Studio Project File - Name="MEditorLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=MEditorLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MEditorLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MEditorLib.mak" CFG="MEditorLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MEditorLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "MEditorLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MEditorLib", LBAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MEditorLib - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "MEditorLib - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "MEditorLib - Win32 Release"
# Name "MEditorLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Box.cpp
# End Source File
# Begin Source File

SOURCE=.\BoxHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdDelete.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdDelSel.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdInsert.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdTyping.cpp
# End Source File
# Begin Source File

SOURCE=.\Command.cpp
# End Source File
# Begin Source File

SOURCE=.\CompositeBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Cursor.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\MacroCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\MBrace.cpp
# End Source File
# Begin Source File

SOURCE=.\MEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\MFrac.cpp
# End Source File
# Begin Source File

SOURCE=.\MI.cpp
# End Source File
# Begin Source File

SOURCE=.\MN.cpp
# End Source File
# Begin Source File

SOURCE=.\MO.cpp
# End Source File
# Begin Source File

SOURCE=.\MRoot.cpp
# End Source File
# Begin Source File

SOURCE=.\MRow.cpp
# End Source File
# Begin Source File

SOURCE=.\MSubSup.cpp
# End Source File
# Begin Source File

SOURCE=.\MSymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\MTable.cpp
# End Source File
# Begin Source File

SOURCE=.\MUnderOver.cpp
# End Source File
# Begin Source File

SOURCE=.\Over.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserException.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserMathText.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Text.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Box.h
# End Source File
# Begin Source File

SOURCE=.\BoxHolder.h
# End Source File
# Begin Source File

SOURCE=.\CmdDelete.h
# End Source File
# Begin Source File

SOURCE=.\CmdDelSel.h
# End Source File
# Begin Source File

SOURCE=.\CmdInsert.h
# End Source File
# Begin Source File

SOURCE=.\CmdTyping.h
# End Source File
# Begin Source File

SOURCE=.\Command.h
# End Source File
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\CompositeBox.h
# End Source File
# Begin Source File

SOURCE=.\Cursor.h
# End Source File
# Begin Source File

SOURCE=.\EditorCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Factory.h
# End Source File
# Begin Source File

SOURCE=.\MacroCommand.h
# End Source File
# Begin Source File

SOURCE=.\MBrace.h
# End Source File
# Begin Source File

SOURCE=.\MEntity.h
# End Source File
# Begin Source File

SOURCE=.\MFrac.h
# End Source File
# Begin Source File

SOURCE=.\MI.h
# End Source File
# Begin Source File

SOURCE=.\MN.h
# End Source File
# Begin Source File

SOURCE=.\MO.h
# End Source File
# Begin Source File

SOURCE=.\MRoot.h
# End Source File
# Begin Source File

SOURCE=.\MRow.h
# End Source File
# Begin Source File

SOURCE=.\MSubSup.h
# End Source File
# Begin Source File

SOURCE=.\MSymbol.h
# End Source File
# Begin Source File

SOURCE=.\MTable.h
# End Source File
# Begin Source File

SOURCE=.\MUnderOver.h
# End Source File
# Begin Source File

SOURCE=.\Over.h
# End Source File
# Begin Source File

SOURCE=.\Parser.h
# End Source File
# Begin Source File

SOURCE=.\ParserException.h
# End Source File
# Begin Source File

SOURCE=.\ParserMathText.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# End Group
# Begin Group "Resource files"

# PROP Default_Filter "bmp"
# End Group
# End Target
# End Project
