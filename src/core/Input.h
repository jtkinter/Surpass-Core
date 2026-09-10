#pragma once

#include "EventDispatcher.h"

struct ButtonData
{
	ButtonState currentState{ ButtonState::None };
	ButtonState previousState{ ButtonState::None };
};

class Input
{
public:
	Input();
	~Input() = default;

	static Input& get()
	{
		static Input instance;
		return instance;
	}

	void update();

	bool isKeyPressed(int KeyCode) const;
	bool isKeyJustPressed(int KeyCode) const;
	bool isKeyJustReleased(int keyCode) const;

	float getScrollOffset() const { return m_ScrollOffset; }
	void resetScrollOffset() { m_ScrollOffset = 0.0f; }

	glm::vec2 getMouseDelta() const { return m_MouseDelta; }

private:
	void onKeyEvent(const KeyEvent& e);
	void onScrollEvent(const ScrollEvent& e);
	void onMouseMoveEvent(const MouseMoveEvent& e);
	void onMouseKeyEvent(const MouseKeyEvent& e);

	std::unordered_map<int, ButtonData> m_KeyStates;

	float m_ScrollOffset = 0.0f;

	glm::vec2 m_MousePos{ 0.0f };
	glm::vec2 m_LastMousePos{ 0.0f };
	glm::vec2 m_MouseDelta{ 0.0f };
	bool m_FirstPressed = true;
};