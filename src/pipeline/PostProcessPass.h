#pragma once
#include "RenderPass.h"
#include "renderer/Shader.h"
#include "renderer/FullScreenQuad.h"

namespace Surpass {

	class PostProcessPass : public RenderPass
	{
	public:
		bool init(int width, int height) override;
		bool resize(int width, int height) override;
		void execute(const Scene& scene) override;

		void setColorInput(unsigned int input) override { m_ColorAttachment = input; }

	private:
		Shader m_Shader;
		FullScreenQuad m_Quad;
		int m_Width = 0;
		int m_Height = 0;

		unsigned int m_ColorAttachment = 0;
	};

}