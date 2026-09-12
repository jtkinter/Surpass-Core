#pragma once
#include <cstddef>

struct Vertex2D
{
	glm::vec2 position;	// 位置坐标
	glm::vec2 texCoord;	// 纹理坐标

	static constexpr int POSITION_DIM = 2;

	static void setAttributePointers()
	{
		// 设置顶点格式
		glVertexAttribPointer(0, Vertex2D::POSITION_DIM, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, position));
		glEnableVertexAttribArray(0);

		// 设置纹理格式
		glVertexAttribPointer(1, Vertex2D::POSITION_DIM, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, texCoord));
		glEnableVertexAttribArray(1);
	}
};