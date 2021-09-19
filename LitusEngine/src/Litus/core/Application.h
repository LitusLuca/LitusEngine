#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Litus\Event\Event.h"
#include "Litus\Event\ApplicationEvents.h"
#include "Litus\ImGui\ImGuiLayer.h"

#include "Litus\Renderer\Buffer.h"

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


		std::unique_ptr<Window> m_window;
		bool m_minimized = false;
		bool m_running = true;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_layerStack;
		

	private:
		static Application* s_Instance;

		unsigned int VAO;

		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<Shader> m_shader;
	};

	Application* createApplication();
}
