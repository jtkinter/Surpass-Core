#include "sppch.h"
#include "Surpass.h"

using namespace Surpass;

void buildDemoScene(Scene& scene, ResourceManager& rm, float aspectRatio)
{
	Camera camera(45.0f, aspectRatio);
	camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	scene.setCamera(camera);

	Mesh& mesh = rm.loadMesh("Cup", "res/models/cup(lp).obj", true);
	Log::info(
		"(", mesh.getBoundbox().min_point.x, ",", mesh.getBoundbox().min_point.y, ",", mesh.getBoundbox().min_point.z, "), ",
		"(", mesh.getBoundbox().max_point.x, ",", mesh.getBoundbox().max_point.y, ",", mesh.getBoundbox().max_point.z, ")"
		);

	std::vector<unsigned char> data = generatorCheckerBoard(512, 512, 8);
	rm.addTexture("CheckerBoard", 512, 512, data.data());

	std::vector<unsigned char> normalMap = generatorNormalMap(512, 512, 8);
	auto& normalTexture = rm.addTexture("NormalCross", 512, 512, normalMap.data());

	Material material;
	material.baseColor = glm::vec3(1.0f);
	material.shininess = 32.0f;
	material.diffuseMap = rm.findTexture("CheckerBoard");
	//material.normalMap = &normalTexture;

	auto& mat = rm.addMaterial("ChecherBoard", material);

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
	rimLight.pos = glm::vec3(0.0f, 0.5f, -5.0f);
	rimLight.color = glm::vec3(0.3f, 0.4f, 0.5f);
	rimLight.intensity = 0.6f;
	lights.push_back(rimLight);

	scene.addLights(lights);
	//scene.setLightCast(1, false);
	scene.setLightCast(2, false);

	const int count = 3;
	const float spacing = 1.5f;
	std::vector<Model> models;
	models.reserve(count);
	for (int i = 0; i < count; ++i)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3((i - 1) * spacing, 1.5f, 0.0f));
		Model model(&mesh, &mat, transform);
		models.push_back(model);
	}
	scene.addModels(models);

	MeshData planeData = Primitive::plane(10.0f, 10.0f);
	planeData.computeTangents();
	rm.addMesh("Plane", planeData);

	Material baseMat;
	baseMat.normalMap = &normalTexture;
	rm.addMaterial("Base", baseMat);

	Model plane(rm.findMesh("Plane"), rm.findMaterial("Base"), glm::mat4(1.0f));
	scene.addModel(plane);
}

int main()
{
	Window window(1920, 1080, "Surpass Engine");

	ResourceManager rm;
	Scene scene;
	buildDemoScene(scene, rm, window.getAspectRatio());

	Renderer::init();

	SceneManager manager;
	ForwardPipeline pipeline;
	pipeline.init(window.getWidth(), window.getHeight());

	int fbW, fbH;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &fbW, &fbH);

	// 检查重置
	EventDispatcher::get().subscribe(EventType::WindowResizeEvent, [&](const Event& e)
	{
		const WindowResizeEvent& event = static_cast<const WindowResizeEvent&>(e);
		int width = event.width;
		int height = event.height;

		if (width <= 0 || height <= 0)
		{
			Log::warn("无效窗口！！！");
			return;
		}
		scene.getCamera().setAspectRatio((float)width / height);
		pipeline.resize(width, height);
	});

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

		pipeline.render(scene);

		Renderer::endFrame();

		window.swapBuffers();
	}

	return 0;
}