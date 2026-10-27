#include "sppch.h"
#include "Ray.h"

#include <limits>
#include "Boundbox.h"

namespace Surpass {

	bool intersectRayBoundbox(const Ray& ray, const Boundbox& box, float& out)
	{
		float tmin = 0;
		float tmax = std::numeric_limits<float>::max();
		for (int i = 0; i < 3; ++i)
		{
			if (std::abs(ray.direction[i]) < 1e-8f)
			{
				if (ray.origin[i] < box.min_point[i] || ray.origin[i] > box.max_point[i])
					return false;
			}
			else
			{
				float t1 = (box.min_point[i] - ray.origin[i]) / ray.direction[i];
				float t2 = (box.max_point[i] - ray.origin[i]) / ray.direction[i];
				if (t1 > t2) std::swap(t1, t2);

				tmin = std::max(tmin, t1);
				tmax = std::min(tmax, t2);

				if (tmin > tmax) return false;
			}
		}

		out = tmin;
		return true;
	}

}