#pragma once
#include "RenderPipeline.h"
#include "world/SceneManager.h"
#include "ShadowPass.h"
#include "MainPass.h"
#include "PostProcessPass.h"
#include "renderer/Texture.h"

namespace Surpass {

	class ForwardPipeline : public RenderPipeline
	{
	public:
		bool init(int width, int height) override;
		bool resize(int width, int height) override;
		void render(Scene& scene) override;

		void setMainPass(std::unique_ptr<RenderPass> mainPass);

	private:
		std::unique_ptr<RenderPass> m_ShadowPass;
		std::unique_ptr<RenderPass> m_MainPass;
		std::unique_ptr<RenderPass> m_PostPass;
	
		int m_Width = 0;
		int m_Height = 0;
	};

}