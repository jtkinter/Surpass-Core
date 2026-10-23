#pragma once
#include "RenderPass.h"
#include "renderer/Shader.h"
#include "renderer/Framebuffer.h"
#include "renderer/Texture.h"
#include <glad/glad.h>
#include "core/Config.h"
#include <array>


namespace Surpass {

	class MainPass : public RenderPass
	{
	public:
		bool init(int width, int height) override;
		bool resize(int width, int height) override;
		void execute(const Scene& scene) override;
		//const Framebuffer& getFramebuffer() const { return m_Framebuffers.empty() ? 0 : m_Framebuffers[0]; }

		void setDepthInput(unsigned int input) override { m_DepthAttachments[0] = input; }
		void setDepthInputs(const std::vector<unsigned int>& inputs) override { m_DepthAttachments = inputs; }

		unsigned int getColorOutput() const override { return m_Framebuffer.getColorAttachment(); }

	private:
		Shader m_Shader;
		Framebuffer m_Framebuffer;
		std::vector<unsigned int> m_DepthAttachments;
	};

}