#pragma once

#include <functional>
#include "Material.h"

namespace Surpass {

	class Mesh;
	class Shader;

	class Model
	{
	public:
		Model(const Mesh* mesh, const Material* material, const glm::mat4& transform = glm::mat4(1.0f));
		void draw(const Shader& shader) const;

		const Material& getMaterial() const { return *m_Material; }

		bool inValid() const { return !(m_Mesh && m_Material); }

	private:
		const Mesh* m_Mesh;
		const Material* m_Material;
		glm::mat4 m_Transform;
	};

}