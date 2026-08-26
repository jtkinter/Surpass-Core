#pragma once

struct GLFWwindow;

class Window 
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	bool shouldClose() const;
	void swapBuffers() const;
	void pollEvents() const;

private:
	GLFWwindow* m_Window;
};