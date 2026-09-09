#include "sppch.h"
#include "core/Window.h"
#include "core/Input.h"
#include "renderer/Shader.h"
#include "renderer/Vertex.h"
#include "renderer/Mesh.h"
#include "renderer/Texture.h"
#include "core/Time.h"
#include "core/Camera.h"


int main()
{
	Window window(800, 600, "Surpass Engine");

	Camera camera(45.0f, 800.0f / 600.0f);
	camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

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
		Input::get().update();
		window.pollEvents();

		Time::update();
		
		float speed = 3.0f * Time::getDeltaTime();

		// WASD移动 目前ws是放大缩小
		if (Input::get().isKeyPressed(GLFW_KEY_W)) camera.move(camera.getForward() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_S)) camera.move(-camera.getForward() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_A)) camera.move(-camera.getRight() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_D)) camera.move(camera.getRight() * speed);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 绘制图像
		shader.use();
		shader.setUniformMat4("uView", camera.getViewMatrix());
		shader.setUniformMat4("uProjection", camera.getProjectionMatrix());

		texture.bind(0);
		shader.setUniform1i("uTexture", 0);
		mesh.draw();

		window.swapBuffers();
	}

	glfwTerminate();

	return 0;
}