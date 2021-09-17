#pragma once
#include "Litus\core\Core.h"
#include <string>
#include <functional>

namespace LT {
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, 
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCategory
	{
		None = 0,
		ApplicationEvent	= BIT(0),
		InputEvent			= BIT(1),
		KeyboardEvent		= BIT(2),
		MouseEvent			= BIT(3),
		MouseButtonEventCategory	= BIT(4)
	};
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType(){ return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class LAPI Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		
		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		bool Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& ev) :
			m_event(ev)
		{
		}

		template<typename T, typename F>
		bool Dispatch(F& func)
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				m_event.Handled = func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}