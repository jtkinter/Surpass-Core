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

	float getAspectRatio() const { return (float)m_Width / m_Height; }

private:
	void registerCallback();

	GLFWwindow* m_Window;

	int m_Width;
	int m_Height;
};