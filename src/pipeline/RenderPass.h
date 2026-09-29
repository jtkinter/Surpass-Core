#pragma once
#include "world/Scene.h"

namespace Surpass {
	
	class RenderPass
	{
	public:
		virtual ~RenderPass() = default;

		virtual bool init(int width = 0, int height = 0) = 0;
		virtual bool resize(int width, int height) { return true; }
		virtual void execute(const Scene& scene) = 0;

		virtual unsigned int getColorOutput() const { return 0; }
		virtual unsigned int getDepthOutput() const { return 0; }

		virtual void setColorInput(unsigned int input) {};
		virtual void setDepthInput(unsigned int input) {};
	};
}