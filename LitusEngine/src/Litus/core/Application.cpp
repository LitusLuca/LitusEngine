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

		m_vertexArray.reset(VertexArray::Create());

		float vertices[7 * 4] =
		{
			-0.5f, -0.5f, 0.f, 0.5f, 0.1f, 0.4f, 1.f,
			0.5f, -0.5f, 0.f,  0.2f, 0.5f, 0.4f, 1.f,
			-0.5f, 0.5f, 0.f,  0.3f, 0.7f, 0.2f, 1.f,
			0.5f, 0.5f, 0.5f,  0.6f, 0.2f, 0.2f, 1.f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Pos"},
			{ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3*2] =
		{
			0,1,2,
			2,1,3
		};
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Color;

uniform float u_Offset;

out vec4 v_Color;

void main() 
{
	v_Color = a_Color;
	gl_Position = vec4(a_Pos + u_Offset, 1.0);
}

)";
		std::string fragmentSrc = R"(
#version 330 core
layout(location = 0) out vec4 color;

in vec4 v_Color;

void main() 
{
	color = v_Color;
}

)";
		m_shader.reset(Shader::Create("TestShader", vertexSrc, fragmentSrc));
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
			RenderCommand::SetClearColor({ 0.f, 0.6f, 0.4f, 1.f });
			RenderCommand::Clear();

			m_shader->Bind();
			m_shader->SetFloat("u_Offset", (float)sin(glfwGetTime()));
			Renderer::Submit(m_shader, m_vertexArray);

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