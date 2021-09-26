#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Litus\Event\Event.h"
#include "Litus\Event\ApplicationEvents.h"
#include "Litus\ImGui\ImGuiLayer.h"

#include "Litus\Renderer\VertexArray.h"
#include "Litus\Renderer\Shader.h"

namespace LT {
	class LAPI Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		Window& GetWindow() { return *m_window; }

		static Application& get() { return *s_Instance; }
	private:
		bool OnWindowCloseEvent(WindowCloseEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);


		Scope<Window> m_window;
		bool m_minimized = false;
		bool m_running = true;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_layerStack;
		
		float m_lastFrame = 0.f;
	private:
		static Application* s_Instance;
	};

	Application* createApplication();
}
