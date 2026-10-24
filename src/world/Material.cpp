#include "sppch.h"
#include "Material.h"
#include "core/Config.h"

namespace Surpass {

	void Material::apply(const Shader& shader) const
	{
		shader.setUniform3f("uBaseColor", baseColor.x, baseColor.y, baseColor.z);
		shader.setUniform1f("uShininess", shininess);

		if (diffuseMap)
		{
			diffuseMap->bind(DIFFUSE_IDX);
			shader.setUniform1i("uDiffuseMap", 0);
			shader.setUniform1i("uHasDiffuseMap", 1);
		}
		else
			shader.setUniform1i("uHasDiffuseMap", 0);

		if (normalMap)
		{
			normalMap->bind(NORMAL_IDX);
			shader.setUniform1i("uNormalMap", NORMAL_IDX);
			shader.setUniform1i("uHasNormalMap", 1);
		}
		else
			shader.setUniform1i("uHasNormalMap", 0);
	}
}