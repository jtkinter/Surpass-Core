#pragma once

#include "EventDispatcher.h"

struct KeyData
{
	KeyState currentState{ KeyState::None };
	KeyState previousState{ KeyState::None };
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

private:
	void onKeyEvent(const KeyEvent& e);
	void onScrollEvent(const ScrollEvent& e);

	std::unordered_map<int, KeyData> m_KeyStates;

	float m_ScrollOffset = 0.0f;
};