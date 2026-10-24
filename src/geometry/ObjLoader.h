#pragma once

#include "world/MeshData.h"

namespace Surpass {

	class ObjLoader
	{
	public:
		static MeshData load(const std::string& filepath);
	};

}