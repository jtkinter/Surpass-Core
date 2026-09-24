#pragma once

namespace Surpass {

	struct FramebufferSpec
	{
		int width = 0;
		int height = 0;
		bool depthOnly = false;
	};

	class Framebuffer
	{
	public:
		Framebuffer() = default;
		Framebuffer(const FramebufferSpec& spec);
		~Framebuffer();

		void init(const FramebufferSpec& spec);

		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator=(const Framebuffer&) = delete;
		Framebuffer(Framebuffer&&) = delete;
		Framebuffer& operator=(const Framebuffer&&) = delete;

		void bind();
		void unbind();

		unsigned int getColorAttachment() const { return m_ColorAttachment; }
		unsigned int getDepthAttachment() const { return m_DepthAttachment; }

	private:
		void destroy();

		int m_Width = 0;
		int m_Height = 0;

		unsigned int m_Framebuffer = 0;
		unsigned int m_ColorAttachment = 0;
		unsigned int m_DepthAttachment = 0;

		FramebufferSpec m_Spec;
	};
}