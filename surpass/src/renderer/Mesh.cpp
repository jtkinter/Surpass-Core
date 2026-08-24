#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
	: m_IndexCount(indices.size())
{
	glGenVertexArrays(1, &m_Attribute);
	glBindVertexArray(m_Attribute);

	glGenBuffers(1, &m_Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_Element);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Element);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// TODO: 此处硬编码
	// 设置数据格式
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_Attribute);
	glDeleteBuffers(1, &m_Buffer);
	glDeleteBuffers(1, &m_Element);
}

void Mesh::draw() const
{
	glBindVertexArray(m_Attribute);
	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
}