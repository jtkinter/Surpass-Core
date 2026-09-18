#include "sppch.h"
#include "Light.h"

#include "Shader.h"

void Light::apply(const Shader& shader, int index) const
{
	std::string posName = "uLightPos[" + std::to_string(index) + ']';
	std::string colorName = "uLightColor[" + std::to_string(index) + ']';

	shader.setUniform3f(posName, pos.x, pos.y, pos.z);
	shader.setUniform3f(colorName, color.x * intensity, color.y * intensity, color.z * intensity);
}