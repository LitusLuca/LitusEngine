#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Litus\Event\Event.h"
#include "Litus\Event\ApplicationEvents.h"
#include "Litus\ImGui\ImGuiLayer.h"


namespace LT {
	class LAPI Application
	{
	public:
		Application();
		virtual ~Application();

		void onEvent(Event& e);

		void run();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		
		Window& getWindow() { return *m_window; }

		static Application& get() { return *s_Instance; }
	private:
		bool onWindowCloseEvent(WindowCloseEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);


		std::unique_ptr<Window> m_window;
		bool m_minimized = false;
		bool m_running = true;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_layerStack;
		

	private:
		static Application* s_Instance;
	};

	Application* createApplication();
}
