#pragma once
#include "world/Scene.h"

namespace Surpass {

	class RenderPipeline
	{
	public:
		virtual ~RenderPipeline() = default;

		virtual bool init(int width, int height) = 0;
		virtual bool resize(int width, int height) = 0;
		virtual void render(Scene& scene) = 0;
	};
}