#pragma once
#include <glm/glm.hpp>
#include <limits>

namespace Surpass {

	struct Boundbox
	{
		glm::vec3 min_point{  std::numeric_limits<float>::max() };
		glm::vec3 max_point{ -std::numeric_limits<float>::max() };

		bool inValid() const { return min_point.x > max_point.x || min_point.y > max_point.y || min_point.z > max_point.z; }

		void expand(const glm::vec3& point)
		{
			min_point = glm::min(min_point, point);
			max_point = glm::max(max_point, point);
		}

		Boundbox transformed(const glm::mat4& m) const;
	};

}