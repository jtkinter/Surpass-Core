#pragma once

// 核心组件
#include "core/Window.h"
#include "core/Input.h"
#include "core/Time.h"
#include "core/Log.h"

// 渲染实现
#include "renderer/Shader.h"
#include "renderer/Vertex.h"
#include "renderer/Mesh.h"
#include "renderer/Texture.h"
#include "renderer/Renderer.h"
#include "renderer/ObjLoader.h"
#include "renderer/Framebuffer.h"
#include "renderer/FullScreenQuad.h"

// 数据类型
#include "world/Camera.h"
#include "world/Light.h"
#include "world/Model.h"
#include "world/Scene.h"
#include "world/SceneManager.h"

// pass管线
#include "pipeline/ShadowPass.h"
#include "pipeline/MainPass.h"
#include "pipeline/PostProcessPass.h"

// 通用工具
#include "utils/TextureGenerator.h"