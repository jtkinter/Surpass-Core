#include "sppch.h"
#include "Mesh.h"

#include "Vertex.h"
#include "geometry/Boundbox.h"
#include "world/MeshData.h"

namespace Surpass {

	Mesh::Mesh(const MeshData& meshData)
	{
		init(meshData);
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Boundbox& bounds)
	{
		init(vertices, indices, bounds);
	}

	Mesh::~Mesh()
	{
		if(m_Attribute)
			glDeleteVertexArrays(1, &m_Attribute);
		if(m_Buffer)
			glDeleteBuffers(1, &m_Buffer);
		if(m_Element)
			glDeleteBuffers(1, &m_Element);
	}

	void Mesh::init(const MeshData& meshData)
	{
		init(meshData.vertices, meshData.indices, meshData.bounds);
	}

	void Mesh::init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Boundbox& bounds)
	{
		m_Bounds = bounds;
		if (m_Bounds.inValid() && !vertices.empty())
		{
			for (const auto& v : vertices)
				m_Bounds.expand(v.position);
		}

		m_IndexCount = indices.size();

		glGenVertexArrays(1, &m_Attribute);
		glBindVertexArray(m_Attribute);

		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &m_Element);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Element);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		Vertex::setAttributePointers();

		// ½â°ó
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::draw() const
	{
		glBindVertexArray(m_Attribute);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
	}

	bool Mesh::inValid()
	{
		return !(m_Attribute || m_Buffer || m_Element);
	}

}