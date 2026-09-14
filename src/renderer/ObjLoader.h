#pragma once

#include "Vertex.h"

class ObjLoader
{
public:
	struct MeshData
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};

	static MeshData load(const std::string& filepath);
};