@echo off
if not exist tools\premake5.exe (
    echo 请下载 premake5.exe 并放到 tools/ 目录下
    pause
    exit /b 1
)
.\tools\premake5 vs2022
pause