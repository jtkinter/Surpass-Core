#include "sppch.h"
#include "Camera.h"

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
	: m_Fov(fov), m_AspectRatio(aspectRatio), m_NearPlane(nearPlane), m_FarPlane(farPlane)
{
	updateProjectMatrix();
	updateViewMatrix();
}

void Camera::updateProjectMatrix()
{
	m_ProjectMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);
}

void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
	front.y = sin(glm::radians(m_Pitch));
	front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
	m_ForwardVector = glm::normalize(front);
	m_RightVector = glm::normalize(glm::cross(m_ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_UpVector = glm::normalize(glm::cross(m_RightVector, m_ForwardVector));
}

void Camera::updateViewMatrix()
{
	updateVectors();
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_ForwardVector, m_UpVector);
}

void Camera::setPosition(const glm::vec3& position)
{
	m_Position = position;
	updateViewMatrix();
}

void Camera::setRotation(float pitch, float yaw)
{
	m_Pitch = pitch;
	m_Yaw = yaw;
	updateViewMatrix();
}

void Camera::setAspectRatio(float aspectRatio)
{
	m_AspectRatio = aspectRatio;
	updateProjectMatrix();
}

void Camera::setFov(float fov)
{
	m_Fov = fov;
	updateProjectMatrix();
}

void Camera::move(const glm::vec3& offset)
{
	m_Position += offset;
	updateViewMatrix();
}

void Camera::rotate(float pitchDelta, float yawDelta)
{
	m_Pitch += pitchDelta;
	m_Yaw += yawDelta;
	m_Pitch = glm::clamp(m_Pitch, -89.9f, 89.9f);
	updateViewMatrix();
}