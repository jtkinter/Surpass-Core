#include <GLFW/glfw3.h>
#include <iostream>
#include "utils/Utils.h"
#include "renderer/Shader.h"
#include "renderer/Mesh.h"
#include "core/Window.h"

int main()
{
	Window window(800, 600, "Surpass Engine");

	// 设置顶点
	std::vector<float> vertices = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	// 设置渲染索引
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	Mesh mesh(vertices, indices);
	Shader shader("res/shader/vertex.vert", "res/shader/fragment.frag");

	// 循环
	while (!window.shouldClose())
	{
		float time = (float)glfwGetTime();
		float green = (sin(time) + 1.0f) / 2.0f;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 绘制图像
		shader.use();
		shader.setUniform1f("uGreen", green);
		mesh.draw();

		window.swapBuffers();
		window.pollEvents();
	}

	glfwTerminate();

	return 0;
}