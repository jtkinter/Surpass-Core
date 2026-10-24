#pragma once

#include <vector>
#include "renderer/Vertex.h"

namespace Surpass {

	struct MeshData
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		void computeTangents();
	};
}