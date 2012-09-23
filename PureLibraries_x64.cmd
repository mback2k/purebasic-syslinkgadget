@echo off
set TARGET=x64

:: The destination purebasic path
set PUREBASIC_HOME=C:\PROGRA~1\PureBasic

:: All the PureBasic tools needed by the makefile, relative to the PureBasic home directory
set PB_LIBRARIES=%PUREBASIC_HOME%/SDK/VisualC/PureLibraries
set PB_LIBRARIAN=%PUREBASIC_HOME%/Compilers/polib.exe
set PB_LIBRARYMAKER=%PUREBASIC_HOME%/SDK/LibraryMaker.exe

:: The dependancies useful to develop on Windows
set PB_VS8=C:/Program Files (x86)/Microsoft Visual Studio 10.0
set PB_PLATEFORM_SDK=C:/Program Files/Microsoft SDKs/Windows/v7.1
set PB_DIRECTX9_SDK=C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)

set PB_VC8=cl.exe -I"%PB_VS8%/VC/include" -I"%PB_LIBRARIES%" -DWINDOWS -DVISUALC -DX64 -I"%PB_PLATEFORM_SDK%/Include" -I"%PB_PLATEFORM_SDK%/Include/crt" -I. -I"%PB_DIRECTX9_SDK%/Include" /nologo /GS- /D_CRT_NOFORCE_MANIFEST

:: Add UnxUtils to the path
set PATH=D:/Dev/unxutils/usr/local/wbin;%PATH%

:: Add VisualC++ to the path, so we have access to cl.exe
set PATH=%PB_VS8%/VC/bin/amd64;%PB_VS8%/Common7/IDE;%PATH%

cmd
