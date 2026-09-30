#pragma once

#include <functional>
#include "Material.h"

namespace Surpass {

	class Mesh;
	class Shader;

	class Model
	{
	public:
		Model(const Mesh& mesh, const Material& material, const glm::mat4& transform = glm::mat4(1.0f));
		void draw(const Shader& shader) const;

		Material& getMaterial() { return m_Material; }
		const Material& getMaterial() const { return m_Material; }

	private:
		std::reference_wrapper<const Mesh> m_Mesh;
		Material m_Material;
		glm::mat4 m_Transform;
	};

}