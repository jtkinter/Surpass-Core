#pragma once

#include "world/MeshData.h"

namespace Surpass {

	class Primitive
	{
	public:
		static MeshData cube(float size = 1.0f);
		static MeshData sphere(float radius = 0.5f, int segments = 32, int rings = 16);
		static MeshData plane(float width = 1.0f, float depth = 1.0f);
	};

}