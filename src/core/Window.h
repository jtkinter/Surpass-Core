#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Surpass {

	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window();

		bool shouldClose() const;
		void swapBuffers() const;
		void pollEvents() const;

		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		float getAspectRatio() const { return (float)m_Width / m_Height; }

	private:
		void registerCallback();

		GLFWwindow* m_Window;

		int m_Width;
		int m_Height;
	};

}