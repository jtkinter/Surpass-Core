#include "sppch.h"
#include "Time.h"

float Time::m_DeltaTime = 0.0f;
float Time::m_TotalTime = 0.0f;
float Time::m_FPS = 0.0f;
int Time::m_FrameCount = 0;
float Time::m_FPSTimer = 0.0f;
int Time::m_FrameCounter = 0;

void Time::update()
{
	float currentTime = (float)glfwGetTime();
	m_DeltaTime = currentTime - m_TotalTime;
	m_TotalTime = currentTime;

	m_FrameCounter++;
	m_FPSTimer += m_DeltaTime;
	if (m_FPSTimer >= 0.5f)
	{
		m_FPS = (float)(m_FrameCounter / m_FPSTimer);
		m_FPSTimer = 0.0f;
		m_FrameCounter = 0;
	}
	m_FrameCount++;
}