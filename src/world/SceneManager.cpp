#include "sppch.h"
#include "SceneManager.h"

namespace Surpass {

	void SceneManager::check_update_Lighting(Scene& scene)
	{
		uint32_t version = scene.getLightVersion();
		if (version == m_LastLightVersion) return;
		m_LastLightVersion = version;

		glm::vec3 center = scene.getSceneCenter();
		Light mainLight = scene.getLights()[0];

		glm::vec3 lightDir = glm::normalize(center - mainLight.pos);
		scene.setLightDir(lightDir);
		glm::vec3 viewPos = center - lightDir * 20.0f;
		m_LightCamera.setPosition(viewPos);
		m_LightCamera.setRotation(glm::degrees(asin(lightDir.y)), glm::degrees(atan2(lightDir.z, lightDir.x)));
		glm::mat4 lightSpace = m_LightCamera.getProjectionMatrix() * m_LightCamera.getViewMatrix();
		scene.setLightSpaceMatrix(lightSpace);
	}

}