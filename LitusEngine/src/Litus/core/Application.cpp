#include "pch.h"
#include "Application.h"

#include "Litus\Renderer\Renderer.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace LT {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		LT_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
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

			for (Layer* layer : m_layerStack)
			{
				layer->OnUpdate();
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
			return false;
		}
		m_minimized = false;
		//dispatch to renderer
		return false;
	}
}