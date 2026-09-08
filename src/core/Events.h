#pragma once

enum KeyState
{
	None,
	Pressed,
	Released,
	Repeat
};

enum class EventType
{
	KeyEvent,
	ScrollEvent
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

struct ScrollEvent : public Event
{
	double xOffset;
	double yOffset;

	ScrollEvent(double x, double y)
		: Event{ EventType::ScrollEvent }, xOffset(x), yOffset(y)
	{
	}
};

using EventCallback = std::function<void(const Event&)>;