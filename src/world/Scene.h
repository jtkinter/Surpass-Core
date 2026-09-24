#pragma once

#include "Model.h"
#include "Light.h"
#include "Camera.h"

namespace Surpass {

	class Scene
	{
	public:
		void setCamera(const Surpass::Camera& camera) { m_Camera = camera; }
		Surpass::Camera& getCamera() { return m_Camera; }
		const Surpass::Camera& getCamera() const { return m_Camera; }

		void addModel(const Surpass::Model& model) { m_Models.push_back(model); }
		void addModels(const std::vector<Surpass::Model>& models);
		const std::vector<Surpass::Model>& getModels() const { return m_Models; }

		void addLight(const Surpass::Light& light);
		void addLights(const std::vector<Surpass::Light>& lights);
		const std::vector<Surpass::Light>& getLights() const { return m_Lights; }

		void setLightSpaceMatrix(const glm::mat4& m) { m_LightSpaceMatrix = m; }
		void setLightDir(const glm::vec3& dir) { m_LightDir = dir; }

		void setSceneCenter(const glm::vec3& center);
		const glm::vec3& getSceneCenter() const { return m_SceneCenter; }

		const glm::mat4& getLightSpaceMatrix() const { return m_LightSpaceMatrix; }
		const glm::vec3& getLightDir() const { return m_LightDir; }
		uint32_t getLightVersion() const { return m_LightVersion; }

	private:
		std::vector<Surpass::Model> m_Models;
		std::vector<Surpass::Light> m_Lights;
		Surpass::Camera m_Camera;

		size_t MAX_LIGHTS = 8;

		glm::mat4 m_LightSpaceMatrix{ 1.0f };
		glm::vec3 m_LightDir{ 0.0f, -1.0f, 0.0f };
		glm::vec3 m_SceneCenter{ 0.0f };

		uint32_t m_LightVersion = 0;
	};

}