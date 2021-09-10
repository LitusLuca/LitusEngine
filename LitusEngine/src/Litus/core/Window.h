#pragma once
#include "Core.h"
#include "Litus\Event\Event.h"

namespace LT {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Litus Engine",
			unsigned int width = 1600,
			unsigned int height = 900)
			: Title(title), Width(width), Height(height) {}
	};

	class LAPI Window
	{
	public:
		using EventCallBackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallback(const EventCallBackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		static Window* create(const WindowProps& props = WindowProps());
	};
}