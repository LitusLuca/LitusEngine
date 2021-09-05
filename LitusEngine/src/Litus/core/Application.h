#pragma once

#include "Core.h"
#include "Window.h"
#include "Litus\Event\ApplicationEvents.h"

namespace LT {
	class LAPI Application
	{
	public:
		Application();
		virtual ~Application();

		void onEvent(Event& e);

		void run();
	private:
		bool onWindowCloseEvent(WindowCloseEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);


		std::unique_ptr<Window> m_window;
		bool m_minimized = false;
		bool m_running = true;
	};

	Application* createApplication();
}
