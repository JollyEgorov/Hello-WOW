@echo off
chcp 1251
echo Building Hello-WOW with Windows colors...

:: Check for icon file
if not exist "dragon_icon_126573.ico" (
    echo WARNING: dragon_icon_126573.ico not found!
    echo Building without icon...
    goto :compile_without_icon
)

echo Icon found: dragon_icon_126573.ico
echo Creating resource file...

:: Create resource file
echo #include "windows.h" > resources.rc
echo IDI_ICON1 ICON "dragon_icon_126573.ico" >> resources.rc

:: Compile resources
windres resources.rc -o resources.o

:: Getting all .cpp files
set files=
for %%i in (*.cpp) do call :add_file "%%i"

echo Compiling files: %files%
echo.

:: Compile with resources and Windows libraries
g++ -static -static-libgcc -static-libstdc++ -mconsole %files% resources.o -o Hello-WOW.exe -O2 -s -luser32

:: Cleanup temporary files
del resources.rc
del resources.o 2>nul

goto :check_result

:compile_without_icon
:: Getting all .cpp files
set files=
for %%i in (*.cpp) do call :add_file "%%i"

echo Compiling files: %files%
echo.

:: Compile without resources
g++ -static -static-libgcc -static-libstdc++ -mconsole %files% -o Hello-WOW.exe -O2 -s -luser32

:check_result
if exist "Hello-WOW.exe" (
    echo Build successful!
    echo File size: 
    for %%F in ("Hello-WOW.exe") do echo %%~zF bytes
    echo.
    set /p run="Launch program? [Y/n]: "
    if /i not "%run%"=="n" (
        echo.
        echo --- LAUNCHING PROGRAM ---
        echo.
        Hello-WOW.exe
    )
) else (
    echo Build error!
)

pause
exit /b

:add_file
set files=%files% %1
goto :eof