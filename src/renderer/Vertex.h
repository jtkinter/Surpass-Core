#pragma once

#include <glad/glad.h>

struct Vertex2D
{
	float x, y;	// 位置坐标
	float u, v;	// 纹理坐标

	static constexpr int POSITION_DIM = 2;

	static void setAttributePointers()
	{
		// 设置顶点格式
		glVertexAttribPointer(0, Vertex2D::POSITION_DIM, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, x));
		glEnableVertexAttribArray(0);

		// 设置纹理格式
		glVertexAttribPointer(1, Vertex2D::POSITION_DIM, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, u));
		glEnableVertexAttribArray(1);
	}
};