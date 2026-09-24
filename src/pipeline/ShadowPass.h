#pragma once
#include "RenderPass.h"
#include "renderer/Framebuffer.h"
#include "renderer/Shader.h"
#include "world/Scene.h"
#include "world/Camera.h"
#include <glm/glm.hpp>

namespace Surpass {

	class ShadowPass : public RenderPass
	{
	public:
		bool init(int width, int height) override;
		void execute(const Scene& scene);

		const Framebuffer& getFramebuffer() const { return m_Framebuffer; }

	private:
		Framebuffer m_Framebuffer;
		Shader m_Shader;
	};

}