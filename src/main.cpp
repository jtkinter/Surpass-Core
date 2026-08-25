#include "sppch.h"
#include "utils/Utils.h"
#include "renderer/Shader.h"
#include "renderer/Mesh.h"
#include "core/Window.h"
#include "renderer/Texture.h"
#include "renderer/Vertex.h"


int main()
{
	Window window(800, 600, "Surpass Engine");

	// 设置顶点
	std::vector<Vertex2D> vertices = {
		{ -0.25f, -0.5f, 0.0f, 0.0f },
		{  0.25f, -0.5f, 1.0f, 0.0f },
		{  0.25f,  0.5f, 1.0f, 1.0f },
		{ -0.25f,  0.5f, 0.0f, 1.0f }
	};

	// 设置渲染索引
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	Mesh mesh(vertices, indices);
	Texture texture("res/textures/logov0_1.png");
	Shader shader("res/shader/vertex.vert", "res/shader/fragment.frag");

	// 解决透明区域没有加载问题
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 循环
	while (!window.shouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 绘制图像
		shader.use();
		texture.bind(0);
		shader.setUniform1i("uTexture", 0);
		mesh.draw();

		window.swapBuffers();
		window.pollEvents();
	}

	glfwTerminate();

	return 0;
}