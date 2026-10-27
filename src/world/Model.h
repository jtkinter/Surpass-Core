#pragma once

#include <functional>
#include "Material.h"
#include "renderer/Mesh.h"

namespace Surpass {

	class Shader;

	class Model
	{
	public:
		Model(const Mesh* mesh, const Material* material, const glm::mat4& transform = glm::mat4(1.0f));
		void draw(const Shader& shader) const;

		const Material& getMaterial() const { return *m_Material; }
		const Boundbox& getBoundbox() const
		{
			if (!m_Mesh) return Boundbox();
			return m_Mesh->getBoundbox().transformed(m_Transform);
		}

		bool inValid() const { return !(m_Mesh && m_Material); }

	private:
		const Mesh* m_Mesh;
		const Material* m_Material;
		glm::mat4 m_Transform;
	};

}