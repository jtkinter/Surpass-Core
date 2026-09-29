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
		void execute(const Scene& scene) override;

		unsigned int getDepthOutput() const override { return m_Framebuffer.getDepthAttachment(); }

	private:
		Framebuffer m_Framebuffer;
		Shader m_Shader;
	};

}