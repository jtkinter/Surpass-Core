#include "sppch.h"
#include "Scene.h"

namespace Surpass {

	void Scene::addModels(const std::vector<Surpass::Model>& models)
	{
		m_Models.insert(m_Models.end(), models.begin(), models.end());
	}

	void Scene::addLight(const Surpass::Light& light)
	{
		m_Lights.push_back(light);
		m_LightVersion++;
	}

	void Scene::addLights(const std::vector<Surpass::Light>& lights)
	{
		size_t remaining = MAX_LIGHTS - m_Lights.size();

		if (remaining == 0)
		{
			Surpass::Log::warn("光源已达上限：", MAX_LIGHTS, "，无法新增");
			return;
		}

		size_t diff = lights.size();
		if (diff > remaining)
		{
			diff = remaining;
			Surpass::Log::warn("光源添加超出上限：", MAX_LIGHTS, "，仅添加个数：", remaining);
		}
		m_Lights.insert(m_Lights.end(), lights.begin(), lights.begin() + diff);
		m_LightVersion += diff;
	}

	void Scene::setSceneCenter(const glm::vec3& center)
	{
		m_SceneCenter = center;
		m_LightVersion++;
	}

}