#include "sppch.h"
#include "Camera.h"

Camera::Camera(float fov, float aspectRadio, float nearPlane, float farPlane)
	: m_Fov(fov), m_AspectRadio(aspectRadio), m_NearPlane(nearPlane), m_FarPlane(farPlane)
{
	updateProjectMatrix();
	updateViewMatrix();
}

void Camera::updateProjectMatrix()
{
	m_ProjectMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRadio, m_NearPlane, m_FarPlane);
}

void Camera::updateViewMatrix()
{
	glm::vec3 CameraFront = getForward();
	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
	if (glm::abs(glm::dot(cameraUp, CameraFront)) > 0.999f)
		cameraUp = glm::vec3(1.0f, 0.0f, 0.0f);
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + CameraFront, cameraUp);
}

glm::vec3 Camera::getForward() const
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
	front.y = sin(glm::radians(m_Pitch));
	front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
	return glm::normalize(front);
}

glm::vec3 Camera::getRight() const
{
	return glm::normalize(glm::cross(getForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
}