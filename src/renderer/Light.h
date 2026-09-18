#pragma once
class Shader;

class Light
{
public:
	glm::vec3 pos{ 50.0f, 50.0f, 50.0f };
	glm::vec3 color{ 1.0f, 1.0f, 1.0f };
	float intensity = 1.0f;

	void apply(const Shader& shader, int index) const;
};