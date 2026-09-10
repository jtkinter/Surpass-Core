#include "sppch.h"
#include "Window.h"
#include "core/EventDispatcher.h"

Window::Window(int width, int height, const std::string& title)
{
	if (!glfwInit())
	{
		Log::error("GLFW 初始化失败");
		std::exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		Log::error("窗口创建失败");
		glfwTerminate();
		std::exit(-1);
	}
	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Log::error("GLAD 初始化失败");
		glfwTerminate();
		std::exit(-1);
	}

	// 注册回调函数
	registerCallback();
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

void Window::registerCallback()
{
	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		ButtonState state;
		if (action == GLFW_PRESS) state = ButtonState::Pressed;
		else if (action == GLFW_RELEASE) state = ButtonState::Released;
		else state = ButtonState::Repeat;

		KeyEvent event(key, state);
		EventDispatcher::get().dispatch(event);
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
	{
		ScrollEvent event(x, y);
		EventDispatcher::get().dispatch(event);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
	{
		MouseMoveEvent event(x, y);
		EventDispatcher::get().dispatch(event);
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int key, int action, int mods)
	{
		ButtonState state;
		if (action == GLFW_PRESS) state = ButtonState::Pressed;
		else if (action == GLFW_RELEASE) state = ButtonState::Released;
		else state = ButtonState::Repeat;

		MouseKeyEvent event(key, state);
		EventDispatcher::get().dispatch(event);
	});
}