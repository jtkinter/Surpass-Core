#pragma once

#include "geometry/Boundbox.h"

namespace Surpass {

	struct Vertex;
	struct MeshData;

	class Mesh 
	{
	public:
		Mesh() = default;
		Mesh(const MeshData& meshData);
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Boundbox& bounds = Boundbox{});
		~Mesh();

		void init(const MeshData& meshData);
		void init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Boundbox& bounds = Boundbox{});

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		Mesh(Mesh&&) = delete;
		Mesh& operator=(Mesh&&) = delete;

		void draw() const;
		bool inValid();

		const Boundbox& getBoundbox() const { return m_Bounds; }

	private:
		unsigned int m_Attribute = 0, m_Buffer = 0, m_Element = 0;
		unsigned int m_IndexCount;
		Boundbox m_Bounds;
	};

}