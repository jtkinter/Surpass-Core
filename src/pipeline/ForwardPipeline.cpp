#include "sppch.h"
#include "ForwardPipeline.h"

namespace Surpass {

	bool ForwardPipeline::init(int width, int height)
	{
		m_ShadowPass = std::make_unique<ShadowPass>();
		m_MainPass = std::make_unique<MainPass>();
		m_PostPass = std::make_unique<PostProcessPass>();

		m_ShadowPass->init(1024, 1024);
		m_MainPass->init(width, height);
		m_PostPass->init(width, height);

		m_Width = width;
		m_Height = height;

		return true;
	}

	bool ForwardPipeline::resize(int width, int height)
	{
		m_ShadowPass->resize(width, height);
		m_MainPass->resize(width, height);
		m_PostPass->resize(width, height);
		return true;
	}

	void ForwardPipeline::render(Scene& scene)
	{
		m_ShadowPass->execute(scene);
		m_MainPass->setDepthInput(m_ShadowPass->getDepthOutput());
		m_MainPass->execute(scene);
		m_PostPass->setColorInput(m_MainPass->getColorOutput());
		m_PostPass->execute(scene);
	}

	void ForwardPipeline::setMainPass(std::unique_ptr<RenderPass> mainPass)
	{
		m_MainPass = std::move(mainPass);
		resize(m_Width, m_Height);
	}

}