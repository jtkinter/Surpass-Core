#include "sppch.h"
#include "Model.h"

#include "renderer/Mesh.h"
#include "renderer/Shader.h"
#include "renderer/Renderer.h"

namespace Surpass {

	Model::Model(const Mesh& mesh, const glm::mat4& transform)
		: m_Mesh(mesh), m_Transform(transform)
	{
	}

	void Model::draw(const Shader& shader) const
	{
		Renderer::draw(shader, m_Mesh.get(), m_Transform);
	}

}