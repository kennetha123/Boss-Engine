#pragma once

#include "bepch.h"
#include "Engine/Core.h"

namespace BossEngine
{
	enum class EventType
	{
		None = 0,

		// window
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		
		// engine
		EngineTick,
		EngineUpdate,
		EngineRender,
		
		// key
		KeyPressed,
		KeyReleased,
		
		// mouse
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	// register the EventCategory with bit shift.
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};

// every time this macro gets called, it'll define those three functions for a specific event type.
#define EVENT_CLASS_TYPE(type)			static EventType GetStaticType() {return EventType::##type; }\
										virtual EventType GetEventType() const override { return GetStaticType(); }\
										virtual const char* GetName() const override { return #type; }

// return the category event.
#define EVENT_CLASS_CATEGORY(category)  virtual int GetCategoryFlags() const override { return category;  }

	class BE_API Event
	{
	public:
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>; //set EventFunc as function pointer to template type.
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFunc<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType()) // if the event dispatched match with EventFunc.
			{
				m_Event.Handled = func(*(T*)&m_Event); // event handler to run the function.
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}