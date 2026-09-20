#pragma once

namespace Surpass {

	class Framebuffer
	{
	public:
		Framebuffer(int width, int height);
		~Framebuffer();

		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator=(const Framebuffer&) = delete;
		Framebuffer(const Framebuffer&&) = delete;
		Framebuffer&& operator=(const Framebuffer&&) = delete;

		void bind();
		void unbind();

		unsigned int getColorAttachment() const { return m_ColorAttachment; }

	private:
		void invalidate();
		void destroy();

		int m_Width;
		int m_Height;

		unsigned int m_Framebuffer = 0;
		unsigned int m_ColorAttachment = 0;
		unsigned int m_DepthAttachment = 0;
	};
}