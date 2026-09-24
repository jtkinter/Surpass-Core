#pragma once

namespace Surpass {

	struct Vertex;

	class Mesh 
	{
	public:
		Mesh() = default;
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();

		void init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		Mesh(Mesh&&) = delete;
		Mesh& operator=(const Mesh&&) = delete;

		void draw() const;

	private:
		unsigned int m_Attribute = 0, m_Buffer = 0, m_Element = 0;
		unsigned int m_IndexCount;
	};

}