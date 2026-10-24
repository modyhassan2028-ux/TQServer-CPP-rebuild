@echo off
rem build_win.bat - build the NpcServer with the
rem EXACT-REPLICA Win32 console window (the
rem ORIGINAL's own RT_DIALOG 102 template).
rem Requires MSVC (x64 Native Tools prompt).
cl /nologo /EHsc /std:c++17 /O2 /D_WIN32 /DWIN32 ^
   /I Exe /I . ^
   Exe\NpcServer\*.cpp Exe\NpcServer\Win\NpcWinDialog.cpp ^
   /Fe:NpcServer.exe ^
   /link user32.lib gdi32.lib comctl32.lib
