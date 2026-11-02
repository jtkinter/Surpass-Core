#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
		Boundbox getBoundbox() const
		{
			if (!m_Mesh) return Boundbox();
			return m_Mesh->getBoundbox().transformed(m_Transform);
		}

		bool inValid() const { return !(m_Mesh && m_Material); }

		void setTransform(const glm::mat4& transform) { m_Transform = transform; }
		const glm::mat4& getTransform() const { return m_Transform; }
		glm::vec3 getPosition() const { return glm::vec3(m_Transform[3]); }

		void move(const glm::vec3 offset) { m_Transform = glm::translate(glm::mat4(1.0f), offset) * m_Transform; }
		void rotate(float angle, const glm::vec3& axis) { m_Transform = glm::rotate(glm::mat4(1.0f), angle, axis) * m_Transform; }

	private:
		const Mesh* m_Mesh;
		const Material* m_Material;
		glm::mat4 m_Transform;
	};

}