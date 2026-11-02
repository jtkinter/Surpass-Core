#pragma once
#include "RenderPass.h"
#include "renderer/Shader.h"
#include "renderer/Framebuffer.h"

namespace Surpass {

	class OutlineMaskPass : public RenderPass
	{
	public:
		bool init(int width, int height) override;
		bool resize(int width, int height) override;
		void execute(const Scene& scene) override;

		unsigned int getColorOutput() const override { return m_Framebuffer.getColorAttachment(); }

	private:
		Shader m_Shader;
		Framebuffer m_Framebuffer;
	};

}