#include "sppch.h"
#include "PostProcessPass.h"
#include "renderer/Renderer.h"

namespace Surpass {

	bool PostProcessPass::init(int width, int height)
	{
		m_Shader.init(getResourceDir("shader/postprocess.vert"), getResourceDir("shader/postprocess.frag"));
		m_Quad.init();
		m_Width = width;
		m_Height = height;

		return true;
	}

	bool PostProcessPass::resize(int width, int height)
	{
		m_Width = width;
		m_Height = height;
		return true;
	}

	void PostProcessPass::execute(const Scene& scene)
	{
		Renderer::beginPass({ nullptr, {0.0f, 0.0f, 0.0f, 1.0f}, true, true, m_Width, m_Height });
		m_Shader.use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		m_Shader.setUniform1i("uScreenTexture", 0);
		m_Quad.draw();
		Renderer::endPass();
	}
}