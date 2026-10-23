#include "sppch.h"
#include "ShadowPass.h"
#include "renderer/Renderer.h"

namespace Surpass {

	bool ShadowPass::init(int width, int height)
	{
		m_Shader.init(getResourceDir("shader/shadow.vert"), getResourceDir("shader/shadow.frag"));

		m_DepthOutputs.resize(MAX_LIGHTS);
		for (int i = 0; i < MAX_LIGHTS; ++i)
		{
			m_Framebuffers[i].init({ width, height, true });
			m_DepthOutputs[i] = m_Framebuffers[i].getDepthAttachment();
		}

		return true;
	}

	void ShadowPass::execute(const Scene& scene)
	{
		const auto& matrices = scene.getLightSpaceMatrices();
		if (matrices.empty()) return;

		m_Shader.use();

		size_t count = std::min(matrices.size(), (size_t)MAX_LIGHTS);
		for (size_t i = 0; i < count; ++i)
		{
			Renderer::beginPass({ &m_Framebuffers[i]});
			m_Shader.setUniformMat4("uLightSpaceMatrix", matrices[i]);
			for (auto& m : scene.getModels())
				m.draw(m_Shader);
			Renderer::endPass();
		}
	}
}