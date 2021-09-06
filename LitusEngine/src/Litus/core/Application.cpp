#include "pch.h"
#include "Application.h"

#include <glad\glad.h>

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
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<WindowCloseEvent>(LT_BIND_EVENT_FN(Application::onWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(LT_BIND_EVENT_FN(Application::onWindowResizeEvent));

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if (ev.Handled)
				break;
			(*it)->onEvent(ev);
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
	}

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(0.f, 1.f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_layerStack)
			{
				layer->onUpdate();
			}

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