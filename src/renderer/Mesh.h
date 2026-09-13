#pragma once

struct Vertex;

class Mesh 
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	~Mesh();

	// ½ûÖ¹¿½±´
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	void draw() const;

private:
	unsigned int m_Attribute, m_Buffer, m_Element;
	unsigned int m_IndexCount;
};