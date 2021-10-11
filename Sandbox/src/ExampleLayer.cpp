#include "ExampleLayer.h"

#include "ImGui\imgui.h"
#include "glm\gtc\matrix_transform.hpp"
#include "Litus\Utils\BinaryLoader.h"
#include <iostream>
ExampleLayer::ExampleLayer() : Layer("Example")
{
	m_vertexArray = LT::VertexArray::Create();

	std::vector<float> binVertices;
	LT::BinaryLoader::ReadBinary("assets/meshes/PuppyVertex.bin", binVertices);
	LT::Ref<LT::VertexBuffer> vertexBuffer = LT::VertexBuffer::Create(binVertices.data(), (uint32_t)(binVertices.size() * sizeof(binVertices[0])));

	LT::BufferLayout layout = {
		{LT::ShaderDataType::Float3, "a_Pos"},
		{LT::ShaderDataType::Float3, "a_Normal"},
		{LT::ShaderDataType::Float2, "a_TexCoord"}
	};
	vertexBuffer->SetLayout(layout);
	m_vertexArray->AddVertexBuffer(vertexBuffer);

	
	std::vector<unsigned int> binIndices;
	LT::BinaryLoader::ReadBinary("assets/meshes/PuppyIndex.bin", binIndices);
	LT::Ref<LT::IndexBuffer> indexBuffer = LT::IndexBuffer::Create(binIndices.data(), (uint32_t)binIndices.size());
	m_vertexArray->SetIndexBuffer(indexBuffer);

	m_shaderLibrary.Load("assets/shaders/texCoordShader.glsl");
	m_shaderLibrary.Load("assets/shaders/textureShader.glsl");
	m_camera = LT::CreateRef<LT::PerspectiveCamera>(45.f, (float)LT::Application::get().GetWindow().GetWidth() / (float)LT::Application::get().GetWindow().GetHeight(), 0.1f, 100.f);

	m_texture = LT::Texture2D::Create("assets/textures/Puppy.png");

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
		m_pos += m_dir * dT.GetSeconds() * 10.f;
	if (LT::Input::IsKeyPressed(LT_KEY_S))
		m_pos -= m_dir * dT.GetSeconds() * 10.f;
	if (LT::Input::IsKeyPressed(LT_KEY_A))
		m_pos -= glm::normalize(glm::cross(m_dir, glm::vec3(0.f, 1.f, 0.f))) * dT.GetSeconds() * 10.f;
	if (LT::Input::IsKeyPressed(LT_KEY_D))
		m_pos += glm::normalize(glm::cross(m_dir, glm::vec3(0.f, 1.f, 0.f))) * dT.GetSeconds() * 10.f;
		
	LT::RenderCommand::SetClearColor({ 0.f, 0.6f, 0.4f, 1.f });
	LT::RenderCommand::Clear();

	m_camera->SetPosition(m_pos);
	//m_camera->SetRotation(m_yaw, m_pitch);
	LT::Renderer::BeginScene(m_camera->GetViewProjectionMatrix());
	m_texture->Bind();
	LT::Renderer::Submit(m_shaderLibrary.Get("texCoordShader"), m_vertexArray, glm::rotate(glm::mat4(1.f), glm::radians(90.f), {-1.f, 0.f, 0.f}));
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