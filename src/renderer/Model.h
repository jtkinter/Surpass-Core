#pragma once

#include <functional>

namespace Surpass {

	class Mesh;
	class Shader;

	class Model
	{
	public:
		Model(const Mesh& mesh, glm::mat4& transform = glm::mat4(1.0f));
		void draw(const Shader& shader);

	private:
		std::reference_wrapper<const Mesh> m_Mesh;
		glm::mat4 m_Transform;
	};

}