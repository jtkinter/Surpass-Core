#include "sppch.h"
#include "Light.h"

#include "Shader.h"

void Light::apply(const Shader& shader) const
{
	shader.setUniform3f("uLightPos", pos.x, pos.y, pos.z);
	shader.setUniform3f("uLightColor", color.x * intensity, color.y * intensity, color.z * intensity);
}