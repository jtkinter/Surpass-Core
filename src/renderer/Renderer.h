#pragma once

#include "Framebuffer.h"
#include <glm/glm.hpp>

namespace Surpass {

	class Shader;
	class Mesh;

	struct PassDesc
	{
		Framebuffer* target = nullptr;
		glm::vec4 color{ 0.2f, 0.3f, 0.3f, 1.0f };
		bool clearColorBit = true;
		bool clearDepthBit = true;
		int viewportWidth = 0;
		int viewportHeight = 0;
	};

	class Renderer
	{
	public:
		static void init();

		static void beginFrame();
		static void endFrame();

		static void beginPass(const PassDesc& desc);
		static void endPass();

		static void draw(const Shader& shader, const Mesh& mesh, const glm::mat4& model = glm::mat4(1.0f));
	};

}