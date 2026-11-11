@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1 && cl /O2 /Os /LD /MD /nologo /I "C:\Users\Windows\AppData\Local\Python\pythoncore-3.14-64\include" gd_core_py/gd_core/CoreEvent.c /link /LIBPATH:"C:\Users\Windows\AppData\Local\Python\pythoncore-3.14-64\libs" python314.lib /OUT:gd_core_py/gd_core/CoreEvent.pyd
