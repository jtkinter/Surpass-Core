#pragma once
#include "RenderPass.h"
#include "renderer/Framebuffer.h"
#include "renderer/Shader.h"
#include "world/Scene.h"
#include "world/Camera.h"
#include "core/Config.h"

#include <glm/glm.hpp>
#include <vector>
#include <array>

namespace Surpass {

	class ShadowPass : public RenderPass
	{
	public:
		bool init(int width, int height) override;
		void execute(const Scene& scene) override;

		unsigned int getDepthOutput() const override { return m_DepthOutputs.empty() ? 0 : m_DepthOutputs[0] ; }
		const std::vector<unsigned int>& getDepthOutputs() const override { return m_DepthOutputs; }

	private:
		std::array<Framebuffer, MAX_LIGHTS> m_Framebuffers;
		std::vector<unsigned int> m_DepthOutputs;
		Shader m_Shader;
	};

}