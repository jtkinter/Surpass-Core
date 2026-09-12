#include "sppch.h"

#include "Renderer.h"
#include "core/Camera.h"
#include "Shader.h"
#include "Mesh.h"

glm::mat4 Renderer::m_ViewMatrix{ 1.0f };
glm::mat4 Renderer::m_ProjectMatrix{ 1.0f };

void Renderer::init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::beginFrame(const Camera& camera)
{
	m_ViewMatrix = camera.getViewMatrix();
	m_ProjectMatrix = camera.getProjectionMatrix();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::endFrame()
{

}

void Renderer::draw(const Shader& shader, const Mesh& mesh)
{
	shader.use();
	shader.setUniformMat4("uView", m_ViewMatrix);
	shader.setUniformMat4("uProjection", m_ProjectMatrix);
	mesh.draw();
}