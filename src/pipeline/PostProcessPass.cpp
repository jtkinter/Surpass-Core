#include "sppch.h"
#include "PostProcessPass.h"
#include "renderer/Renderer.h"

namespace Surpass {

	bool PostProcessPass::init(int width, int height)
	{
		m_Shader.init("res/shader/postprocess.vert", "res/shader/postprocess.frag");
		m_Quad.init();
		m_Width = width;
		m_Height = height;

		return true;
	}

	void PostProcessPass::execute(unsigned int colorAttachment)
	{
		Renderer::beginPass({ nullptr, {0.0f, 0.0f, 0.0f, 1.0f}, true, true, m_Width, m_Height });
		m_Shader.use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorAttachment);
		m_Shader.setUniform1i("uScreenTexture", 0);
		m_Quad.draw();
		Renderer::endPass();
	}
}