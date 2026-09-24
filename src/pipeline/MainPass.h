#pragma once
#include "RenderPass.h"
#include "world/Scene.h"
#include "renderer/Shader.h"
#include "renderer/Framebuffer.h"
#include "renderer/Texture.h"
#include <glad/glad.h>

namespace Surpass {

	class MainPass : public RenderPass
	{
	public:
		bool init(int width, int height) override;
		void execute(const Scene& scene, const Texture& texture, unsigned int depthAttachment);
		const Framebuffer& getFramebuffer() const { return m_Framebuffer; }

	private:
		Shader m_Shader;
		Framebuffer m_Framebuffer;
	};

}