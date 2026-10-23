#include "sppch.h"
#include "MainPass.h"
#include "renderer/Renderer.h"
#include "world/Light.h"
#include "world/Camera.h"

namespace Surpass {

	bool MainPass::init(int width, int height)
	{
		m_Shader.init(getResourceDir("shader/vertex.vert"), getResourceDir("shader/fragment.frag"));
		m_Framebuffer.init({ width, height });

		return true;
	}

	bool MainPass::resize(int width, int height)
	{
		m_Framebuffer.resize(width, height);
		return true;
	}

	void MainPass::execute(const Scene& scene)
	{
		Renderer::beginPass({ &m_Framebuffer });
		m_Shader.use();

		const Camera& camera = scene.getCamera();
		m_Shader.setUniform3f("uViewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		m_Shader.setUniformMat4("uView", camera.getViewMatrix());
		m_Shader.setUniformMat4("uProjection", camera.getProjectionMatrix());

		const auto& matrices = scene.getLightSpaceMatrices();
		int count = (int)std::min({ m_DepthAttachments.size(), matrices.size(), (size_t)MAX_LIGHTS });
		for (int i = 0; i < count; ++i)
		{
			std::string idx = "[" + std::to_string(i) + "]";

			glActiveTexture(GL_TEXTURE1 + i);
			glBindTexture(GL_TEXTURE_2D, m_DepthAttachments[i]);
			m_Shader.setUniform1i("uShadowMap" + idx, 1 + i);
			m_Shader.setUniformMat4("uLightSpaceMatrices" + idx, matrices[i]);
		}
		//m_Shader.setUniform1i("uShadowLightCount", count);

		const auto& lightToShadow = scene.getLightToShadowMap();
		const std::vector<Light>& lights = scene.getLights();
		for (int i = 0; i < lights.size(); ++i)
		{
			std::string name = "uLightToShadow[" + std::to_string(i) + "]";
			int idx = (i < lightToShadow.size()) ? lightToShadow[i] : -1;
			m_Shader.setUniform1i(name, idx);
			lights[i].apply(m_Shader, i);
		}
			
		m_Shader.setUniform1i("uLightCount", (int)lights.size());

		for (auto& m : scene.getModels())
		{
			m.getMaterial().apply(m_Shader);
			m.draw(m_Shader);
		}
		
		Renderer::endPass();
	}

}