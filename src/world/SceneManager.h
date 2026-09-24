#pragma once
#include "Scene.h"
#include <glm/glm.hpp>

namespace Surpass {

	class SceneManager
	{
	public:
		void update(Scene& scene)
		{
			check_update_Lighting(scene);
		}

	private:
		void check_update_Lighting(Scene& scene);

		float cameraSize = 5.0f;
		Camera m_LightCamera{ -cameraSize, cameraSize, -cameraSize, cameraSize, 1.0f, 50.0f };
		uint32_t m_LastLightVersion = 0;
	};

}