#pragma once
#include <cstddef>

struct Vertex
{
	glm::vec3 position;	// 位置坐标
	glm::vec3 normals;	// 法线
	glm::vec2 texCoord;	// 纹理坐标

	static void setAttributePointers()
	{
		// 设置顶点格式
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		// 设置法线格式
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
		glEnableVertexAttribArray(1);

		// 设置纹理格式
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		glEnableVertexAttribArray(2);
	}
};