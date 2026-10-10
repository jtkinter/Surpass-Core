#pragma once
#include "renderer/Vertex.h"
#include <vector>

namespace Surpass {

	class Primitive
	{
	public:
		struct MeshData
		{
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
		};

		static MeshData cube(float size = 1.0f);
		static MeshData sphere(float radius = 0.5f, int segments = 32, int rings = 16);
		static MeshData plane(float width = 1.0f, float depth = 1.0f);
	};

}