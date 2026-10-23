#include "sppch.h"
#include "SceneManager.h"

namespace Surpass {

	void SceneManager::check_update_Lighting(Scene& scene)
	{
		uint32_t version = scene.getLightVersion();
		if (version == m_LastLightVersion) return;
		m_LastLightVersion = version;

		const std::vector<Light>& lights = scene.getLights();
		if (lights.empty()) return;
		
		glm::vec3 center = scene.getSceneCenter();

		std::vector<glm::mat4> matrices;
		std::vector<int> lightToShadow(lights.size(), -1);

		int shadowIndex = 0;
		for (size_t i = 0; i < lights.size(); ++i)
		{
			if (!lights[i].castShadow) continue;

			glm::vec3 lightDir = glm::normalize(center - lights[i].pos);
			glm::vec3 viewPos = center - lightDir * 20.0f;

			Camera& cam = m_LightCameras[i];
			cam.setPosition(viewPos);
			cam.setRotation(glm::degrees(asin(lightDir.y)), glm::degrees(atan2(lightDir.z, lightDir.x)));

			matrices.push_back(cam.getProjectionMatrix() * cam.getViewMatrix());
			lightToShadow[i] = shadowIndex++;
		}

		scene.setLightSpaceMatrices(matrices);
		scene.setLightToShadowMap(lightToShadow);
	}

}