#include "sppch.h"
#include "MainPass.h"
#include "renderer/Renderer.h"
#include "world/Light.h"
#include "world/Camera.h"

namespace Surpass {

	bool MainPass::init(int width, int height)
	{
		m_Shader.init("res/shader/vertex.vert", "res/shader/fragment.frag");
		m_Framebuffer.init({ width, height });

		return true;
	}

	void MainPass::execute(const Scene& scene, const Texture& texture, unsigned int depthAttachment)
	{
		Renderer::beginPass({ &m_Framebuffer });
		m_Shader.use();

		const Camera& camera = scene.getCamera();
		m_Shader.setUniform3f("uViewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		m_Shader.setUniformMat4("uView", camera.getViewMatrix());
		m_Shader.setUniformMat4("uProjection", camera.getProjectionMatrix());

		texture.bind(0);
		m_Shader.setUniform1i("uTexture", 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthAttachment);
		m_Shader.setUniform1i("uShadowMap", 1);
		m_Shader.setUniformMat4("uLightSpaceMatrix", scene.getLightSpaceMatrix());

		const std::vector<Light>& lights = scene.getLights();
		for (int i = 0; i < lights.size(); ++i)
			lights[i].apply(m_Shader, i);

		for (auto& m : scene.getModels())
			m.draw(m_Shader);
		m_Shader.setUniform1i("uLightCount", (int)lights.size());



		Renderer::endPass();
	}

}