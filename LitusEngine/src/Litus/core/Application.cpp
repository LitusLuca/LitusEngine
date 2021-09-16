#include "pch.h"
#include "Application.h"

#include <glad\glad.h>

namespace LT {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(LT_BIND_EVENT_FN(Application::onEvent));

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);

		float vertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.f, 
			0.5f, -0.5f, 0.f,
			-0.5f, 0.5f, 0.f,
			0.5f, 0.5f, 0.5f
		};

		unsigned int indices[3*2] =
		{
			0,1,2,
			2,1,3
		};

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
		overlay->onAttach();
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

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, 0);

			m_ImGuiLayer->begin();
			for (Layer* layer : m_layerStack)
			{
				layer->onImGuiRender();
			}
			m_ImGuiLayer->end();
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