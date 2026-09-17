#include "sppch.h"
#include "Model.h"

#include "Mesh.h"
#include "Shader.h"
#include "Renderer.h"

Model::Model(const Mesh& mesh, glm::mat4& transform)
	: m_Mesh(mesh), m_Transform(transform)
{
}

void Model::draw(const Shader& shader)
{
	Renderer::draw(shader, m_Mesh, m_Transform);
}