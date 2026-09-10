#include "sppch.h"
#include "Input.h"

Input::Input()
{
	EventDispatcher::get().subscribe(EventType::KeyEvent, [this](const Event& e){ onKeyEvent(static_cast<const KeyEvent&>(e)); });
	EventDispatcher::get().subscribe(EventType::ScrollEvent, [this](const Event& e){ onScrollEvent(static_cast<const ScrollEvent&>(e)); });
}

void Input::update()
{
	for (auto& [keyCode, data] : m_KeyStates)
	{
		data.previousState = data.currentState;
	}
}

bool Input::isKeyPressed(int keyCode) const
{
	auto it = m_KeyStates.find(keyCode);
	if (it != m_KeyStates.end())
		return it->second.currentState == KeyState::Pressed;
	return false;
}

bool Input::isKeyJustPressed(int keyCode) const
{
	auto it = m_KeyStates.find(keyCode);
	if (it != m_KeyStates.end())
	{
		const auto& data = it->second;
		return data.currentState == KeyState::Pressed && data.previousState != KeyState::Pressed;
	}
	return false;
}

bool Input::isKeyJustReleased(int keyCode) const
{
	auto it = m_KeyStates.find(keyCode);
	if (it != m_KeyStates.end())
	{
		const auto& data = it->second;
		return data.currentState == KeyState::Released && data.previousState != KeyState::Released;
	}
	return false;
}

void Input::onKeyEvent(const KeyEvent& e)
{
	// 主动去掉Repeate
	if (e.state == KeyState::Repeat)
		return;
	m_KeyStates[e.KeyCode].currentState = e.state;
}

void Input::onScrollEvent(const ScrollEvent& e)
{
	//Log::info("滚轮水平移动：", e.xOffset, "，竖直移动：", e.yOffset);
	m_ScrollOffset += e.yOffset;
}