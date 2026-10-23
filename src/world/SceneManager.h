#pragma once
#include "Scene.h"
#include <vector>
#include <glm/glm.hpp>
#include <core/Config.h>

namespace Surpass {

	class SceneManager
	{
	public:
		SceneManager()
		{
			m_LightCameras.resize(MAX_LIGHTS,
				Camera(-m_CameraSize, m_CameraSize, -m_CameraSize, m_CameraSize, 1.0f, 50.0f));
		}

		void update(Scene& scene)
		{
			check_update_Lighting(scene);
		}

	private:
		void check_update_Lighting(Scene& scene);

		float m_CameraSize = 5.0f;
		std::vector<Camera> m_LightCameras;
		uint32_t m_LastLightVersion = 0;
	};

}