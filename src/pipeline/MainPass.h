#pragma once
#include "RenderPass.h"
#include "renderer/Shader.h"
#include "renderer/Framebuffer.h"
#include "renderer/Texture.h"
#include <glad/glad.h>

namespace Surpass {

	class MainPass : public RenderPass
	{
	public:
		bool init(int width, int height) override;
		bool resize(int width, int height) override;
		void execute(const Scene& scene) override;
		const Framebuffer& getFramebuffer() const { return m_Framebuffer; }

		void setTexture(const Texture* texture) { m_Texture = texture; }
		void setDepthInput(unsigned int input) override { m_DepthAttachment = input; }

		unsigned int getColorOutput() const override { return m_Framebuffer.getColorAttachment(); }

	private:
		Shader m_Shader;
		Framebuffer m_Framebuffer;
		unsigned int m_DepthAttachment = 0;
		const Texture* m_Texture = nullptr;
	};

}