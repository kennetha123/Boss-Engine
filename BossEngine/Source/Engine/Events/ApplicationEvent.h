#pragma once

#include "Event.h"

#include <sstream>

namespace BossEngine
{
	class BE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class BE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class BE_API EngineTickEvent : public Event
	{
	public:
		EngineTickEvent() {}

		EVENT_CLASS_TYPE(EngineTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class BE_API EngineUpdateEvent : public Event
	{
	public:
		EngineUpdateEvent() {}

		EVENT_CLASS_TYPE(EngineUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class BE_API EngineRenderEvent : public Event
	{
	public:
		EngineRenderEvent() {}

		EVENT_CLASS_TYPE(EngineRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}