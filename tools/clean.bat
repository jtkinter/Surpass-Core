@echo off
chcp 65001 >nul
echo.
cd /d "%~dp0.."
echo 清理开始

echo [1/4] 删除 bin/ 和 bin-int/ ...
if exist bin rmdir /s /q bin
if exist bin-int rmdir /s /q bin-int

echo [2/4] 删除 Visual Studio 缓存 .vs/ ...
if exist .vs rmdir /s /q .vs

echo [3/4] 删除 Premake 生成的解决方案和项目文件 ...
del /q *.sln 2>nul
del /q *.vcxproj 2>nul
del /q *.vcxproj.filters 2>nul
del /q *.vcxproj.user 2>nul

echo [4/4] 删除 lib 下的残留项目文件 ...
del /q lib\glad\*.vcxproj 2>nul
del /q lib\glad\*.vcxproj.filters 2>nul
del /q lib\glad\*.vcxproj.user 2>nul
del /q lib\glfw\*.vcxproj 2>nul
del /q lib\glfw\*.vcxproj.filters 2>nul
del /q lib\glfw\*.vcxproj.user 2>nul
if exist lib\glad\bin rmdir /s /q lib\glad\bin
if exist lib\glad\bin-int rmdir /s /q lib\glad\bin-int
if exist lib\glfw\bin rmdir /s /q lib\glfw\bin
if exist lib\glfw\bin-int rmdir /s /q lib\glfw\bin-int

echo 清理完成。
pause