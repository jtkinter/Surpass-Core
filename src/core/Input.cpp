#include "sppch.h"
#include "Input.h"

Input::Input()
{
	EventDispatcher::get().subscribe(EventType::KeyEvent, [this](const Event& e){ onKeyEvent(static_cast<const KeyEvent&>(e)); });
	EventDispatcher::get().subscribe(EventType::ScrollEvent, [this](const Event& e){ onScrollEvent(static_cast<const ScrollEvent&>(e)); });
	EventDispatcher::get().subscribe(EventType::MouseMoveEvent, [this](const Event& e){ onMouseMoveEvent(static_cast<const MouseMoveEvent&>(e)); });
	EventDispatcher::get().subscribe(EventType::MouseKeyEvent, [this](const Event& e){ onMouseKeyEvent(static_cast<const MouseKeyEvent&>(e)); });
}

void Input::update()
{
	for (auto& [keyCode, data] : m_KeyStates)
		data.previousState = data.currentState;

	m_MouseDelta = glm::vec2(0.0f, 0.0f);
}

bool Input::isKeyPressed(int keyCode) const
{
	auto it = m_KeyStates.find(keyCode);
	if (it != m_KeyStates.end())
		return it->second.currentState == ButtonState::Pressed;
	return false;
}

bool Input::isKeyJustPressed(int keyCode) const
{
	auto it = m_KeyStates.find(keyCode);
	if (it != m_KeyStates.end())
	{
		const auto& data = it->second;
		return data.currentState == ButtonState::Pressed && data.previousState != ButtonState::Pressed;
	}
	return false;
}

bool Input::isKeyJustReleased(int keyCode) const
{
	auto it = m_KeyStates.find(keyCode);
	if (it != m_KeyStates.end())
	{
		const auto& data = it->second;
		return data.currentState == ButtonState::Released && data.previousState != ButtonState::Released;
	}
	return false;
}

void Input::onKeyEvent(const KeyEvent& e)
{
	if (e.state == ButtonState::Repeat)
		return;
	m_KeyStates[e.keyCode].currentState = e.state;
}

void Input::onScrollEvent(const ScrollEvent& e)
{
	//Log::info("滚轮水平移动：", e.xOffset, "，竖直移动：", e.yOffset);
	m_ScrollOffset += e.yOffset;
}

void Input::onMouseMoveEvent(const MouseMoveEvent& e)
{
	m_MousePos = glm::vec2((float)e.xPos, (float)e.yPos);
	if (isKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		m_MouseDelta += m_MousePos - m_LastMousePos;
		m_LastMousePos = m_MousePos;
	}
}

void Input::onMouseKeyEvent(const MouseKeyEvent& e)
{
	if (e.state == ButtonState::Repeat)
		return;
	m_KeyStates[e.keyCode].currentState = e.state;
	m_LastMousePos = m_MousePos;
}