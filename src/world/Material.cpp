#include "sppch.h"
#include "Material.h"

namespace Surpass {

	void Material::apply(const Shader& shader) const
	{
		shader.setUniform3f("uBaseColor", baseColor.x, baseColor.y, baseColor.z);
		shader.setUniform1f("uShininess", shininess);

		if (diffuseMap)
		{
			diffuseMap->bind(0);
			shader.setUniform1i("uDiffuseMap", 0);
			shader.setUniform1i("uHasDiffuseMap", 1);
		}
		else
			shader.setUniform1i("uHasDiffuseMap", 0);
	}
}