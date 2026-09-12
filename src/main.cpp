#include "sppch.h"
#include "core/Window.h"
#include "core/Input.h"
#include "renderer/Shader.h"
#include "renderer/Vertex.h"
#include "renderer/Mesh.h"
#include "renderer/Texture.h"
#include "core/Time.h"
#include "core/Camera.h"
#include "renderer/Renderer.h"


int main()
{
	Window window(800, 600, "Surpass Engine");

	Camera camera(45.0f, window.getAspectRatio());
	camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

	// 设置顶点
	std::vector<Vertex2D> vertices = {
		{ {-0.25f, -0.5f}, { 0.0f, 0.0f} },
		{ { 0.25f, -0.5f}, { 1.0f, 0.0f} },
		{ { 0.25f,  0.5f}, { 1.0f, 1.0f} },
		{ {-0.25f,  0.5f}, { 0.0f, 1.0f} }
	};

	// 设置渲染索引
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	Mesh mesh(vertices, indices);
	Texture texture("res/textures/logov0_1.png");
	Shader shader("res/shader/vertex.vert", "res/shader/fragment.frag");

	Renderer::init();

	// 循环
	while (!window.shouldClose())
	{
		Input::get().update();
		window.pollEvents();

		Time::update();
		
		float speed = 3.0f * Time::getDeltaTime();
		float rotSpeed = 50.0f * Time::getDeltaTime();

		// WASD移动 目前ws是放大缩小
		if (Input::get().isKeyPressed(GLFW_KEY_W)) camera.move(camera.getUp() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_S)) camera.move(-camera.getUp() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_A)) camera.move(-camera.getRight() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_D)) camera.move(camera.getRight() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_Q)) camera.rotate(0.0f, -rotSpeed);
		if (Input::get().isKeyPressed(GLFW_KEY_E)) camera.rotate(0.0f, rotSpeed);
		if (Input::get().isKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			auto& mouseDelta = Input::get().getMouseDelta();
			float mouseSpeed = 0.15f;
			camera.rotate(-mouseDelta.y * mouseSpeed, mouseDelta.x * mouseSpeed);
		}

		float scroll = Input::get().getScrollOffset();
		if (scroll != 0.0f)
		{
			camera.move(camera.getForward() * scroll * 0.25f);
			Input::get().resetScrollOffset();
		}

		// 绘制图像
		Renderer::beginFrame(camera);
		
		shader.use();
		texture.bind(0);
		shader.setUniform1i("uTexture", 0);
		
		Renderer::draw(shader, mesh);
		Renderer::endFrame();

		window.swapBuffers();
	}

	glfwTerminate();

	return 0;
}