#include "sppch.h"
#include "OutlineMaskPass.h"

#include "renderer/Renderer.h"
#include "world/Scene.h"

namespace Surpass {

	bool OutlineMaskPass::init(int width, int height)
	{
		m_Framebuffer.init({ width, height });
		m_Shader.init(getResourceDir("shader/mask.vert"), getResourceDir("shader/mask.frag"));

		return true;
	}

	bool OutlineMaskPass::resize(int width, int height)
	{
		m_Framebuffer.resize(width, height);
		return true;
	}

	void OutlineMaskPass::execute(const Scene& scene)
	{
		Renderer::beginPass({ &m_Framebuffer, { 0.0f, 0.0f, 0.0f, 1.0f } });
		int index = scene.getSelectIndex();
		if (index >= 0)
		{
			m_Shader.use();
			const Model& model = scene.getModel(index);
			m_Shader.setUniformMat4("uModel", model.getTransform());
			m_Shader.setUniformMat4("uView", scene.getCamera().getViewMatrix());
			m_Shader.setUniformMat4("uProjection", scene.getCamera().getProjectionMatrix());
			model.draw(m_Shader);
		}
		
		Renderer::endPass();
	}

}