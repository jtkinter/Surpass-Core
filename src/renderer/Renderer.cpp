#include "sppch.h"

#include "Renderer.h"
#include "core/Camera.h"
#include "Shader.h"
#include "Mesh.h"

namespace Surpass {

	glm::mat4 Renderer::m_ViewMatrix{ 1.0f };
	glm::mat4 Renderer::m_ProjectMatrix{ 1.0f };

	void Renderer::init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	void Renderer::beginFrame(const Camera& camera)
	{
		m_ViewMatrix = camera.getViewMatrix();
		m_ProjectMatrix = camera.getProjectionMatrix();
	}

	void Renderer::endFrame()
	{

	}

	void Renderer::beginPass(const PassDesc& desc)
	{
		if (desc.target)
			desc.target->bind();
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, desc.viewportWidth, desc.viewportHeight);
		}

		GLbitfield mask = 0;
		if (desc.clearColorBit)
		{
			glClearColor(desc.color.r, desc.color.g, desc.color.b, desc.color.a);
			mask |= GL_COLOR_BUFFER_BIT;
		}
		if (desc.clearDepthBit)
			mask |= GL_DEPTH_BUFFER_BIT;

		if (mask) glClear(mask);
	}

	void Renderer::endPass()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::draw(const Shader& shader, const Mesh& mesh, const glm::mat4& model)
	{
		shader.use();
		shader.setUniformMat4("uModel", model);
		shader.setUniformMat4("uView", m_ViewMatrix);
		shader.setUniformMat4("uProjection", m_ProjectMatrix);
		mesh.draw();
	}

}