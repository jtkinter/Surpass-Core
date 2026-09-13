#pragma once

class Camera;
class Shader;
class Mesh;

class Renderer
{
public:
	static void init();

	static void beginFrame(const Camera& camera);
	static void endFrame();

	static void draw(const Shader& shader, const Mesh& mesh, const glm::mat4& model = glm::mat4(1.0f));

private:
	static glm::mat4 m_ViewMatrix;
	static glm::mat4 m_ProjectMatrix;
};