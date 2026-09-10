#pragma once

enum ButtonState
{
	None,
	Pressed,
	Released,
	Repeat
};

enum class EventType
{
	KeyEvent,
	ScrollEvent,
	MouseMoveEvent,
	MouseKeyEvent
};

struct Event
{
	EventType type;
};

struct KeyEvent : public Event
{
	int keyCode;
	ButtonState state;

	KeyEvent(int code, ButtonState ks)
		: Event{EventType::KeyEvent}, keyCode(code), state(ks)
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

struct MouseMoveEvent : public Event
{
	double xPos;
	double yPos;

	MouseMoveEvent(double x, double y)
		: Event{ EventType::MouseMoveEvent }, xPos(x), yPos(y)
	{
	}
};

struct MouseKeyEvent : public Event
{
	int keyCode;
	ButtonState state;

	MouseKeyEvent(int code, ButtonState ks)
		: Event{ EventType::MouseKeyEvent }, keyCode(code), state(ks)
	{
	}
};

using EventCallback = std::function<void(const Event&)>;