# Surpass-Core Surpass渲染内核
一个从零开始构建的 C++/OpenGL 渲染内核。

## 软件介绍
### 开发运行环境
**操作系统**：Windows11
**IDE**：Visual Studio 2022（Community）
**适用平台**：x64

### 使用的第三方库
```
GLFW | 3.5.1
GLAD | Core Profile 4.6
stb  | 
```

### 项目结构
```
Surpass-Core    // 项目根目录
-> bin          // 项目最终生成程序
-> bin-int      // 项目中间产物
-> lib          // 存放第三方库
---> glad
---> glfw
-> res          // 资产
---> shader
-> src          // 源代码
---> core
---> rederer
---> utils
-> tools        // 环境构建文件
```

### 如何快速构建项目
项目使用环境构建工具Premake，无需自行下载
双击 build.bat
保证终端无报错后，会在根目录生成一个.sln文件，点击即可使用

### 下一步
- 进一步使用premake管理项目
- 开发相机，引入glm库，同时顺便完善事件处理系统

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
初步引入premake管理

2026.8.25
实现预编译，加入sppch.h和sppch.cpp文件
引入纹理，实现Texture类
解决Mesh中的硬编码

2026.8.26
简单实现按键获取，并封装事件和事件派发器类
修复预编译bug和删掉对应include


## 许可证

本项目采用 **Apache License 2.0** 进行开源。

你可以自由地使用、修改、分发本项目的代码，包括用于商业目的。但需保留原始版权声明，并在修改时标注变更内容。

详细的许可证条款请查看 [LICENSE](./LICENSE) 文件。

> **品牌声明**：本项目名称 "Surpass" 及 Logo 是项目的品牌标识，未经授权不得用于商业宣传或误导性用途。