#include "pch.h"
#include "Application.h"

#include "GLFW\glfw3.h"

namespace LT {

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(LT_BIND_EVENT_FN(Application::onEvent));
	}
	Application::~Application()
	{

	}

	void Application::onEvent(Event& ev)
	{
		LT_CORE_TRACE("{0}", ev.toString());
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<WindowCloseEvent>(LT_BIND_EVENT_FN(Application::onWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(LT_BIND_EVENT_FN(Application::onWindowResizeEvent));
	}

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(0.f, 1.f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->onUpdate();
		}
	}
	bool Application::onWindowCloseEvent(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
	bool Application::onWindowResizeEvent(WindowResizeEvent& e)
	{
		if (e.getWidth() == 0 || e.getHeight() == 0)
		{
			m_minimized = true;
			return false;
		}
		m_minimized = false;
		//dispatch to renderer
		return false;
	}
}