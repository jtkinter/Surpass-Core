#include "sppch.h"
#include "Surpass.h"

using namespace Surpass;

int main()
{
	Window window(1920, 1080, "Surpass Engine");

	Scene scene;

	Camera camera(45.0f, window.getAspectRatio());
	camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	scene.setCamera(camera);

	ObjLoader::MeshData meshData = ObjLoader::load("res/models/cup(lp).obj");
	Mesh mesh(meshData.vertices, meshData.indices);

	std::vector<unsigned char> data = generatorCheckerBoard(512, 512, 8);
	Texture texture(512, 512, data.data());

	std::vector<Light> lights;
	
	Light keyLight;
	keyLight.pos = glm::vec3(5.0f, 5.0f, 5.0f);
	keyLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
	keyLight.intensity = 1.0f;
	lights.push_back(keyLight);

	Light fillLight;
	fillLight.pos = glm::vec3(-5.0f, 3.0f, 2.0f);
	fillLight.color = glm::vec3(0.3f, 0.4f, 0.5f);
	fillLight.intensity = 0.8f;
	lights.push_back(fillLight);

	Light rimLight;
	rimLight.pos = glm::vec3(0.0f, -3.0f, -5.0f);
	rimLight.color = glm::vec3(0.3f, 0.4f, 0.5f);
	rimLight.intensity = 0.6f;
	lights.push_back(rimLight);

	scene.addLights(lights);

	const int count = 3;
	const float spacing = 0.5;
	float offset = (count - 1) * spacing;
	std::vector<Model> models;
	models.reserve(count);
	for (int i = 0; i < count; ++i)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(offset + i * spacing, 0.0f, 0.0f));
		Model model(mesh, transform);
		models.push_back(model);
	}
	scene.addModels(models);

	Renderer::init();

	ShadowPass shadowPass;
	shadowPass.init(1024, 1024);
	SceneManager manager;
	MainPass mainPass;
	mainPass.init(window.getWidth(), window.getHeight());
	PostProcessPass postPass;
	postPass.init(window.getWidth(), window.getHeight());

	// 循环
	while (!window.shouldClose())
	{
		Input::get().update();
		window.pollEvents();

		Time::update();
		
		float speed = 3.0f * Time::getDeltaTime();
		float rotSpeed = 50.0f * Time::getDeltaTime();
		Camera& mainCamera = scene.getCamera();

		// WASD移动 目前ws是放大缩小
		if (Input::get().isKeyPressed(GLFW_KEY_W)) mainCamera.move(mainCamera.getUp() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_S)) mainCamera.move(-mainCamera.getUp() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_A)) mainCamera.move(-mainCamera.getRight() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_D)) mainCamera.move(mainCamera.getRight() * speed);
		if (Input::get().isKeyPressed(GLFW_KEY_Q)) mainCamera.rotate(0.0f, -rotSpeed);
		if (Input::get().isKeyPressed(GLFW_KEY_E)) mainCamera.rotate(0.0f, rotSpeed);
		if (Input::get().isKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			auto& mouseDelta = Input::get().getMouseDelta();
			float mouseSpeed = 0.15f;
			mainCamera.rotate(-mouseDelta.y * mouseSpeed, mouseDelta.x * mouseSpeed);
		}

		float scroll = Input::get().getScrollOffset();
		if (scroll != 0.0f)
		{
			mainCamera.move(mainCamera.getForward() * scroll * 0.25f);
			Input::get().resetScrollOffset();
		}

		// 渲染
		manager.update(scene);
		Renderer::beginFrame();

		// pass1 渲染阴影
		shadowPass.execute(scene);
		// pass2 绘制图像
		mainPass.execute(scene, texture, shadowPass.getFramebuffer().getDepthAttachment());
		// pass3 渲染到屏幕
		postPass.execute(mainPass.getFramebuffer().getColorAttachment());

		Renderer::endFrame();

		window.swapBuffers();
	}

	glfwTerminate();

	return 0;
}