#include "sppch.h"
#include "ShadowPass.h"
#include "renderer/Renderer.h"

namespace Surpass {

	bool ShadowPass::init(int width, int height)
	{
		m_Framebuffer.init({ width, height, true });
		m_Shader.init("res/shader/shadow.vert", "res/shader/shadow.frag");

		return true;
	}

	void ShadowPass::execute(const Scene& scene)
	{
		Renderer::beginPass({ &m_Framebuffer });
		m_Shader.use();
		m_Shader.setUniformMat4("uLightSpaceMatrix", scene.getLightSpaceMatrix());
		for (auto& m : scene.getModels())
			m.draw(m_Shader);
		Renderer::endPass();
	}
}