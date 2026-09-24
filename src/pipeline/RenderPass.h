#pragma once

namespace Surpass {
	
	class RenderPass
	{
	public:
		virtual ~RenderPass() = default;

		virtual bool init(int width = 0, int height = 0) = 0;
		//virtual bool resize(int width, int height) {};
	};
}