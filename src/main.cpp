#include "sppch.h"
#include "Surpass.h"

using namespace Surpass;

int main()
{
	Window window(800, 600, "Surpass Engine");

	Camera camera(45.0f, window.getAspectRatio());
	camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

	Framebuffer scenebuf(window.getWidth(), window.getHeight());

	ObjLoader::MeshData meshData = ObjLoader::load("res/models/cup(lp).obj");
	Mesh mesh(meshData.vertices, meshData.indices);

	//Texture texture("res/textures/logo.png");

	std::vector<unsigned char> data = generatorCheckerBoard(512, 512, 8);
	Texture texture(512, 512, data.data());
	Shader sceneShader("res/shader/vertex.vert", "res/shader/fragment.frag");
	Shader postShader("res/shader/postprocess.vert", "res/shader/postprocess.frag");

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

	Renderer::init();
	FullScreenQuad quad;

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

		// 渲染
		Renderer::beginFrame(camera);
		
		// 绘制图像
		Renderer::beginPass({ &scenebuf });
		sceneShader.use();
		texture.bind(0);
		sceneShader.setUniform1i("uTexture", 0);
		
		for (int i = 0; i < lights.size(); ++i)
			lights[i].apply(sceneShader, i);
		sceneShader.setUniform3f("uViewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		
		//float time = Time::getTotalTime();
		//glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.5f, 1.0f, 0.0f));
		for (auto& m : models)
			m.draw(sceneShader);
		sceneShader.setUniform1i("uLightCount", lights.size());
		Renderer::endPass();

		Renderer::beginPass({ nullptr, {0.0f, 0.0f, 0.0f, 1.0f}, true, true, window.getWidth(), window.getHeight()});
		postShader.use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scenebuf.getColorAttachment());
		postShader.setUniform1i("uScreenTexture", 0);
		quad.draw();
		Renderer::endPass();

		Renderer::endFrame();

		window.swapBuffers();
	}

	glfwTerminate();

	return 0;
}