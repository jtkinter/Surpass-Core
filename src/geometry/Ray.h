#pragma once
#include <glm/glm.hpp>

namespace Surpass {

	struct Boundbox;

	struct Ray
	{
		glm::vec3 origin{ 0.0f };
		glm::vec3 direction{ 0.0f, 0.0f, -1.0f };
	};


	bool intersectRayBoundbox(const Ray& ray, const Boundbox& box, float& out);
}