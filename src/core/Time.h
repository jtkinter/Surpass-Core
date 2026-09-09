#pragma once

class Time
{
public:
	static float getDeltaTime() { return m_DeltaTime; }
	static float getTotalTime() { return m_TotalTime; }
	static float getFPS() { return m_FPS; }
	static int getFrameCount() { return m_FrameCount; }

	static void update();

private:
	static float m_DeltaTime;
	static float m_TotalTime;
	static float m_FPS;
	static int m_FrameCount;
	static float m_FPSTimer;
	static int m_FrameCounter;
};