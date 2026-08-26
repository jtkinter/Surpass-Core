#pragma once

#include "Events.h"

class EventDispatcher
{
public:
	// 注册
	void subscribe(EventType type, EventCallback callback)
	{
		m_Listeners[type].push_back(callback);
	}

	// 触发所有回调
	void dispatch(const Event& event)
	{
		auto it = m_Listeners.find(event.type);
		if (it != m_Listeners.end())
			for (auto callback : it->second)
				callback(event);
	}

	// 单例访问
	static EventDispatcher& get()
	{
		static EventDispatcher instance;
		return instance;
	}

private:
	std::unordered_map<EventType, std::vector<EventCallback>> m_Listeners;
};