# Microsoft Developer Studio Project File - Name="drawtexthook" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=drawtexthook - Win32 Debug
!MESSAGE "drawtexthook - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "drawtexthook - Win32 Debug" (basierend auf  "Win32 (x86) Application")

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "drawtexthook - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /Gr /MD /W3 /O1 /D "UNICODE" /FD /GF /c
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32 kernel32.lib user32.lib shlwapi.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "drawtexthook - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /Gr /MD /W3 /Gm /Zi /O1 /D "_DEBUG" /D "UNICODE" /FR /FD /GF /c
# ADD RSC /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32 kernel32.lib user32.lib shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "drawtexthook - Win32 Release"
# Name "drawtexthook - Win32 Debug"
# Begin Group "Quellcodedateien"
# PROP Default_Filter "cpp;c;def"
# Begin Source File
SOURCE=drawtexthook.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"
# PROP Default_Filter "h;hpp;inl"
# End Group
# Begin Group "Ressourcendateien"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;gif;jpg;png"
# Begin Source File
SOURCE=drawtexthook.rc
# End Source File
# End Group
# Begin Source File
SOURCE=.\manifest
# End Source File
# End Target
# End Project
