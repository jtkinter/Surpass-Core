#pragma once

class Camera
{
public:
	Camera(float fov = 45.0f, float aspectRatio = 16.0f / 9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

	glm::vec3 getForward() const { return m_ForwardVector; }
	glm::vec3 getRight() const { return m_RightVector; }
	glm::vec3 getUp() const { return m_UpVector; }
	glm::mat4 getViewMatrix() const { return m_ViewMatrix; }
	glm::mat4 getProjectionMatrix() const { return m_ProjectMatrix; }

	void setPosition(const glm::vec3& position);
	void setRotation(float pitch, float yaw);
	void setAspectRatio(float aspectRatio);
	void setFov(float fov);

	void move(const glm::vec3& offset);
	void rotate(float pitchDelta, float yawDelta);

private:
	void updateProjectMatrix();
	void updateVectors();
	void updateViewMatrix();

	float m_Fov;			// 视场角
	float m_AspectRatio;	// 宽高比
	float m_NearPlane;		// 近裁切面
	float m_FarPlane;		// 远裁切面
	float m_Yaw = -90.0f;	// 偏航角
	float m_Pitch = 0.0f;	// 俯仰角

	glm::mat4 m_ProjectMatrix{ 1.0f };	// 投影矩阵
	glm::mat4 m_ViewMatrix{ 1.0f };		// 视图矩阵
	glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };

	// 方向向量
	glm::vec3 m_ForwardVector{ 0.0f, 0.0f, -1.0f };
	glm::vec3 m_RightVector{ 1.0f, 0.0f, 0.0f };
	glm::vec3 m_UpVector{ 0.0f, 1.0f, 0.0f };
};