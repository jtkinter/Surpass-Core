#include "Window.h"

#include "sppch.h"

Window::Window(int width, int height, const std::string& title)
{
	if (!glfwInit())
	{
		std::cerr << "GLFW 初始化失败" << std::endl;
		std::exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		std::cerr << "窗口创建失败" << std::endl;
		glfwTerminate();
		std::exit(-1);
	}
	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLAD 初始化失败" << std::endl;
		glfwTerminate();
		std::exit(-1);
	}
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Window::shouldClose() const 
{
	return glfwWindowShouldClose(m_Window);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_Window);
}

void Window::pollEvents () const
{
	glfwPollEvents();
}