#pragma once

#include <vector>
#include "renderer/Vertex.h"
#include "geometry/Boundbox.h"

namespace Surpass {

	struct MeshData
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		Boundbox bounds;

		void computeTangents();
		void computeBounds();
	};
}