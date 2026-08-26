#pragma once

enum KeyState
{
	Pressed,
	Released,
	Repeat
};

enum class EventType
{
	KeyEvent
};

struct Event
{
	EventType type;
};

struct KeyEvent : public Event
{
	int KeyCode;
	KeyState state;

	KeyEvent(int code, KeyState ks)
		: Event{EventType::KeyEvent}, KeyCode(code), state(ks)
	{
	}
};

using EventCallback = std::function<void(const Event&)>;