#pragma once
#include "Event.h"
#include <sstream>

namespace LT {
	class LAPI WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int l_width, unsigned int l_height)
			: m_width(l_width), m_height(l_height)
		{
		}

		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(ApplicationEvent);

	private:
		unsigned int m_width;
		unsigned int m_height;
	};
	class LAPI WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(ApplicationEvent);
	};

	class LAPI AppTickEvent : public Event
	{
		AppTickEvent() {}
		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY(ApplicationEvent);
	};

	class LAPI AppUpdateEvent : public Event
	{
		AppUpdateEvent() {}
		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CATEGORY(ApplicationEvent);
	};

	class LAPI AppRenderEvent : public Event
	{
		AppRenderEvent() {}
		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CATEGORY(ApplicationEvent);
	};
}