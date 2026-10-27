#include "sppch.h"
#include "Boundbox.h"

namespace Surpass {

	Boundbox Boundbox::transformed(const glm::mat4& m) const
	{
		glm::vec3 corners[8] = {
			{ min_point.x, min_point.y, min_point.z }, { max_point.x, min_point.y, min_point.z },
			{ min_point.x, max_point.y, min_point.z }, { max_point.x, max_point.y, min_point.z },
			{ min_point.x, min_point.y, max_point.z }, { max_point.x, min_point.y, max_point.z },
			{ min_point.x, max_point.y, max_point.z }, { max_point.x, max_point.y, max_point.z },
		};

		Boundbox result;
		result.min_point = result.max_point = glm::vec3(m * glm::vec4(corners[0], 1.0f));

		for (int i = 1; i < 8; ++i)
		{
			glm::vec3 p = glm::vec3(m * glm::vec4(corners[i], 1.0f));
			result.expand(p);
		}

		return result;
	}

}