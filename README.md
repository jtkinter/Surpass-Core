# Surpass-Engine Surpass游戏引擎开发
Surpass Engine – A C++/OpenGL game engine core built from scratch, exploring the underlying principles of computer graphics and engine architecture.

## 软件介绍
### 开发运行环境
**操作系统**：Windows11
**IDE**：Visual Studio 2022（Community）
**适用平台**：x64

### 使用的第三方库
GLFW | 3.5.1
GLAD | Core Profile 4.6

### 项目结构
```
surpass
-> lib          // 存放第三方库
---> glad
---> glfw
-> res          // 资产
---> shader
-> src          // 源代码
---> core
---> rederer
---> utils
```

### 下一步
- 引入纹理
- 解决Mesh中的硬编码
- 引入premake管理项目
- 实现预编译

## 开发日志
2026.8.22 
完成openGL的导入

2026.8.23 
实现渲染三角形
完成函数封装
引入uniform
将glsl源代码整理成文件并让文件识别出来

2026.8.24
实现Utils类、Shader类、Mesh类和Window类封装