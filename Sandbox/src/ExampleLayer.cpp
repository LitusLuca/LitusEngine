#include "ExampleLayer.h"

#include "ImGui\imgui.h"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>
ExampleLayer::ExampleLayer() : Layer("Example")
{
	m_vertexArray = LT::VertexArray::Create();

	float vertices[7 * 16] =
	{   //pos						//Color						//TexCoord
		-1.f,	-1.f,	-1.f,	0.f, 0.f,
		-1.f,	-1.f,	1.f,	0.f, 1.f,
		-1.f,	1.f,	1.f,	1.f, 1.f,
		-1.f,	1.f,	-1.f,	1.f, 0.f,
		-1.f,	1.f,	-1.f,	0.f, 0.f,
		-1.f,	1.f,	1.f,	0.f, 1.f,
		1.f,	1.f,	1.f,	1.f, 1.f,
		1.f,	1.f,	-1.f,	1.f, 0.f,
		1.f,	-1.f,	1.f,	0.f, 1.f,
		1.f,	-1.f,	-1.f,	0.f, 0.f,
		1.f,	-1.f,	-1.f,	1.f, 0.f,
		1.f,	-1.f,	1.f,	1.f, 1.f,
		-1.f,	1.f,	-1.f,	0.f, 1.f,
		1.f,	1.f,	-1.f,	1.f, 1.f,
		-1.f,	-1.f,	1.f,	0.f, 0.f,
		1.f,	-1.f,	1.f,	1.f, 0.f
	};
	LT::Ref<LT::VertexBuffer> vertexBuffer = LT::VertexBuffer::Create(vertices, sizeof(vertices));

	LT::BufferLayout layout = {
		{LT::ShaderDataType::Float3, "a_Pos"},
		{LT::ShaderDataType::Float2, "a_TexCoord"}
	};
	vertexBuffer->SetLayout(layout);
	m_vertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[12 * 3] =
	{
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		7, 6, 8,
		7, 8, 9,
		10, 11, 1,
		10, 1, 0,
		12, 13, 10,
		12, 10, 0,
		6, 5, 14,
		6, 14, 15,
	};
	LT::Ref<LT::IndexBuffer> indexBuffer = LT::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_vertexArray->SetIndexBuffer(indexBuffer);

	m_shader = LT::Shader::Create("assets/shaders/textureShader.glsl");
	m_camera = LT::CreateRef<LT::PerspectiveCamera>(45.f, (float)LT::Application::get().GetWindow().GetWidth() / (float)LT::Application::get().GetWindow().GetHeight(), 0.1f, 100.f);

	m_texture = LT::Texture2D::Create("assets/textures/container2.png");

	LT::Application::get().GetWindow().SetCursorMode(LT::Window::CursorMode::Disabled);
}

void ExampleLayer::OnUpdate(LT::Time dT)
{
	if (floor(m_time)
		== 1)
	{
		m_fps = m_frame;
		m_frame = 0;
		m_time = 0;
	}
	else
	{
		m_time += (float)dT;
		m_frame++;
	}

	if (LT::Input::IsKeyPressed(LT_KEY_W))
		m_pos += m_dir * dT.GetSeconds();
	if (LT::Input::IsKeyPressed(LT_KEY_S))
		m_pos -= m_dir * dT.GetSeconds();
	if (LT::Input::IsKeyPressed(LT_KEY_A))
		m_pos -= glm::normalize(glm::cross(m_dir, glm::vec3(0.f, 1.f, 0.f))) * dT.GetSeconds();
	if (LT::Input::IsKeyPressed(LT_KEY_D))
		m_pos += glm::normalize(glm::cross(m_dir, glm::vec3(0.f, 1.f, 0.f))) * dT.GetSeconds();
		
	LT::RenderCommand::SetClearColor({ 0.f, 0.6f, 0.4f, 1.f });
	LT::RenderCommand::Clear();

	m_camera->SetPosition(m_pos);
	//m_camera->SetRotation(m_yaw, m_pitch);
	LT::Renderer::BeginScene(m_camera->GetViewProjectionMatrix());
	m_texture->Bind();
	LT::Renderer::Submit(m_shader, m_vertexArray, glm::translate(glm::mat4(1.f), { 1.f, 1.f, 1.f }));
	LT::Renderer::EndScene();
}

void ExampleLayer::OnEvent(LT::Event& ev)
{
	LT::EventDispatcher dispatcher(ev);
	auto onMouse = [this](LT::MouseMovedEvent& ev) {
		float xOffset = ev.GetX() - m_mousePos.x;
		float yOffset = m_mousePos.y - ev.GetY();
		m_yaw += m_sens * xOffset;
		m_pitch += m_sens * yOffset;
		m_camera->SetRotation(m_yaw, m_pitch);
		RecalculateDir();
		m_mousePos.x = ev.GetX();
		m_mousePos.y = ev.GetY();
		return true;
	};
	dispatcher.Dispatch<LT::MouseMovedEvent>(onMouse);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::SetNextWindowBgAlpha(0.35f);
	ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoMove);
	ImGui::Text(" Hi!\n Fps: %i", m_fps);
	ImGui::Text("yaw: %.1f pitch: %.1f", m_yaw, m_pitch);
	ImGui::End();
}

void ExampleLayer::RecalculateDir()
{
	m_dir.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_dir.y = sin(glm::radians(m_pitch));
	m_dir.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
}