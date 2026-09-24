#pragma once
#include "RenderPass.h"
#include "renderer/Shader.h"
#include "renderer/FullScreenQuad.h"

namespace Surpass {

	class PostProcessPass : public RenderPass
	{
	public:
		bool init(int width, int height) override;
		void execute(unsigned int colorAttachment);

	private:
		Shader m_Shader;
		FullScreenQuad m_Quad;
		int m_Width = 0;
		int m_Height = 0;
	};

}