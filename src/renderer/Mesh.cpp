#include "sppch.h"
#include "Mesh.h"

#include "Vertex.h"

Mesh::Mesh(const std::vector<Vertex2D>& vertices, const std::vector<unsigned int>& indices)
	: m_IndexCount(indices.size())
{
	glGenVertexArrays(1, &m_Attribute);
	glBindVertexArray(m_Attribute);

	glGenBuffers(1, &m_Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_Element);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Element);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	Vertex2D::setAttributePointers();

	// ½â°ó
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