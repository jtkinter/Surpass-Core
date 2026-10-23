#pragma once

#include <vector>

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
		void setAllLightsCastShadow(bool cast);
		void setShadowLightLimit(int count);
		void setLightCast(int index, bool cast);
		const Light& getLight(int index) const { return m_Lights[index]; }
		const std::vector<Light>& getLights() const { return m_Lights; }

		void setLightSpaceMatrix(const glm::mat4& m) { m_LightSpaceMatrices[0] =  m; }
		const glm::mat4& getLightSpaceMatrix() const { return m_LightSpaceMatrices[0]; }
		const std::vector<glm::mat4>& getLightSpaceMatrices() const { return m_LightSpaceMatrices; }
		void setLightSpaceMatrices(const std::vector<glm::mat4>& m) { m_LightSpaceMatrices = m; }

		void setSceneCenter(const glm::vec3& center);
		const glm::vec3& getSceneCenter() const { return m_SceneCenter; }

		void setLightToShadowMap(const std::vector<int>& map) { m_LightToShadowMap = map; }
		const std::vector<int>& getLightToShadowMap() const { return m_LightToShadowMap; }

		uint32_t getLightVersion() const { return m_LightVersion; }

	private:
		Camera m_Camera;
		std::vector<Surpass::Model> m_Models;
		std::vector<Surpass::Light> m_Lights;

		std::vector<glm::mat4> m_LightSpaceMatrices;
		glm::vec3 m_SceneCenter{ 0.0f };

		std::vector<int> m_LightToShadowMap;

		uint32_t m_LightVersion = 0;
	};

}