#include "pch.h"
#include "Application.h"

#include "Litus\Renderer\Renderer.h"
#include "Time.h"
#include "Litus\Event\KeyEvents.h"
#include "KeyCodes.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace LT {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		LT_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_window = Scope<Window>(Window::Create());
		m_window->SetEventCallback(LT_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<WindowCloseEvent>(LT_BIND_EVENT_FN(Application::OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(LT_BIND_EVENT_FN(Application::OnWindowResizeEvent));

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if (ev.Handled)
				break;
			(*it)->OnEvent(ev);
		}

		dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& ev) {
			if (ev.getKeyCode() == LT_KEY_ESCAPE && !ev.Handled)
			{
				m_running = false;
				return true;
			}
			return false;
			});
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run()
	{
		while (m_running)
		{
			float time = m_window->GetTime();
			Time dT = time - m_lastFrame;
			m_lastFrame = time;
			
			if (!m_minimized)
			{
				for (Layer* layer : m_layerStack)
				{
					layer->OnUpdate(dT);
				}
			}
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			m_window->OnUpdate();
		}
	}
	bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
	bool Application::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_minimized = true;
			return true;
		}
		m_minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}