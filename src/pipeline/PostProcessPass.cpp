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

		m_Shader.use();
		m_Shader.setUniform3f("uOutlineColor", 1.0f, 0.5f, 0.0f);
		m_Shader.setUniform1f("uOutlineWidth", 3.0f);

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

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_MaskAttachment);
		m_Shader.setUniform1i("uOutlineMask", 1);
		m_Shader.setUniform1i("uHasOutline", m_MaskAttachment != 0 ? 1 : 0);
		m_Shader.setUniform2f("uTexelSize", 1.0f / m_Width, 1.0f / m_Height);

		m_Quad.draw();
		Renderer::endPass();
	}
}