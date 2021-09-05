#pragma once
#include "Event.h"
#include <sstream>

namespace LT
{
	class LAPI MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) :
			m_mouseX(x), m_mouseY(y) {}
		float getX() const { return m_mouseX; }
		float getY() const { return m_mouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(MouseEvent | InputEvent);
		EVENT_CLASS_TYPE(MouseMoved);

	private:
		float m_mouseX, m_mouseY;
	};

	class LAPI MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) :
			m_xOffset(xOffset), m_yOffset(yOffset) {}
		float getXOffset() const { return m_xOffset; }
		float getYOffset() const { return m_yOffset; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(MouseEvent | InputEvent);

	private:
		float m_xOffset, m_yOffset;
	};

	class LAPI MouseButtonEvent : public Event
	{
	public:
		int getMouseButton() const { return m_button; }
		EVENT_CLASS_CATEGORY(MouseButtonEventCategory | MouseEvent);
	protected:
		MouseButtonEvent(int button) :
			m_button(button) {}

		int m_button;
	};

	class LAPI MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) :
			MouseButtonEvent(button) {}
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed);
	};

	class LAPI MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) :
			MouseButtonEvent(button) {}
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased);
	};
}