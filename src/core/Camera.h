#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(float fov = 45.0f, float aspectRadio = 16.0f / 9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

	glm::vec3 getForward() const;
	glm::vec3 getRight() const;
	glm::mat4 getViewMatrix() const { return m_ViewMatrix; }
	glm::mat4 getProjectionMatrix() const { return m_ProjectMatrix; }

	void setPosition(const glm::vec3& position)
	{
		m_Position = position;
		updateViewMatrix();
	}

	void move(const glm::vec3& offset)
	{
		m_Position += offset;
		updateViewMatrix();
	}

private:
	void updateProjectMatrix();
	void updateViewMatrix();

	float m_Fov;			// 视场角
	float m_AspectRadio;	// 宽高比
	float m_NearPlane;		// 近裁切面
	float m_FarPlane;		// 远裁切面
	float m_Yaw = -90.0f;	// 偏航角
	float m_Pitch = 0.0f;	// 俯仰角

	glm::mat4 m_ProjectMatrix{ 1.0f };	// 投影矩阵
	glm::mat4 m_ViewMatrix{ 1.0f };		// 视图矩阵
	glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
};