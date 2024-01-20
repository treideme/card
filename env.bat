::=============================================================================
:: Script: env.bat
:: Author: Thomas Reidemeister <treideme@gmail.com>
::   This script bootstraps the paths and needed tools for Windows builds/development.
::
::=============================================================================
@ECHO OFF
:: VS Build tools
IF NOT EXIST "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" (
    ECHO Please install VC Build tools for Visual C++
    EXIT /B 1
) ELSE (
    ECHO VC Build tools found
)
:: Configure environment
CALL "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64

WHERE python
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: python was not found, please install and make sure it is in PATH
    exit /B 1
)

WHERE xxd
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: xxd was not found, please install and make sure it is in PATH
    exit /B 1
)

WHERE meson
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: meson was not found, please install and make sure it is in PATH
    exit /B 1
)

:: Change prompt
set PROMPT=[ENV] $P$G