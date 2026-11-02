#pragma once

#include <vector>

#include "Model.h"
#include "Light.h"
#include "Camera.h"

namespace Surpass {

	class Scene
	{
	public:
		void setCamera(const Camera& camera) { m_Camera = camera; }
		Camera& getCamera() { return m_Camera; }
		const Camera& getCamera() const { return m_Camera; }

		void addModel(const Model& model) { m_Models.push_back(model); }
		void addModels(const std::vector<Model>& models);
		const std::vector<Model>& getModels() const { return m_Models; }
		Model& getModel(size_t idx) { return m_Models[idx]; }
		const Model& getModel(size_t idx) const { return m_Models[idx]; }

		void addLight(const Light& light);
		void addLights(const std::vector<Light>& lights);
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
		int getSelectIndex() const { return m_SelectedIndex; }
		void selectModel(int index) { m_SelectedIndex = index; }

	private:
		Camera m_Camera;
		std::vector<Model> m_Models;
		std::vector<Light> m_Lights;

		std::vector<glm::mat4> m_LightSpaceMatrices;
		glm::vec3 m_SceneCenter{ 0.0f };

		std::vector<int> m_LightToShadowMap;

		uint32_t m_LightVersion = 0;
		int m_SelectedIndex = -1;
	};

}