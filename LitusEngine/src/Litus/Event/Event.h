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
#define EVENT_CLASS_TYPE(type)	static EventType getStaticType(){ return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class LAPI Event
	{
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }
		
		bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
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
			if (m_event.getEventType() == T::getStaticType())
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
		return os << e.toString();
	}
}