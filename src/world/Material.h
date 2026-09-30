#pragma once

#include "renderer/Texture.h"
#include "renderer/Shader.h"

namespace Surpass {

	struct Material
	{
		glm::vec3 baseColor{ 1.0f,1.0f,1.0f };
		float shininess = 32.0f;
		const Texture* diffuseMap = nullptr;

		void apply(const Shader& shader) const;
	};

}