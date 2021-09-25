#include "ExampleLayer.h"

#include "ImGui\imgui.h"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>
ExampleLayer::ExampleLayer() : Layer("Example")
{
	m_vertexArray.reset(LT::VertexArray::Create());

	float vertices[7 * 8] =
	{
		-0.5f,	-0.5f,	0.5f,	0.5f, 0.1f, 0.4f, 1.f,
		0.5f,	-0.5f,	0.5f,	0.2f, 0.5f, 0.4f, 1.f,
		-0.5f,	0.5f,	0.5f,	0.3f, 0.7f, 0.2f, 1.f,
		0.5f,	0.5f,	0.5f,	0.6f, 0.2f, 0.2f, 1.f,
		-0.5f,	-0.5f,	-0.5f,	0.5f, 0.1f, 0.4f, 1.f,
		0.5f,	-0.5f,	-0.5f,  0.2f, 0.5f, 0.4f, 1.f,
		-0.5f,	0.5f,	-0.5f,  0.3f, 0.7f, 0.2f, 1.f,
		0.5f,	0.5f,	-0.5f,  0.6f, 0.2f, 0.2f, 1.f
	};
	std::shared_ptr<LT::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(LT::VertexBuffer::Create(vertices, sizeof(vertices)));

	LT::BufferLayout layout = {
		{LT::ShaderDataType::Float3, "a_Pos"},
		{LT::ShaderDataType::Float4, "a_Color"}
	};
	vertexBuffer->SetLayout(layout);
	m_vertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[6 * 6] =
	{
		0,1,2, //Front
		2,1,3,
		4,5,6, //Back
		6,5,7, 
		2,3,6, //Top
		3,7,6,
		4,5,0, //Botton
		0,5,1,
		4,0,6, //Left
		6,0,2,
		1,5,3, //Right
		5,3,7
	};
	std::shared_ptr<LT::IndexBuffer> indexBuffer;
	indexBuffer.reset(LT::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_vertexArray->SetIndexBuffer(indexBuffer);

	std::string vertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_viewProjection;
uniform mat4 u_modelMatrix;

out vec4 v_Color;

void main() 
{
	v_Color = a_Color;
	gl_Position = u_viewProjection * u_modelMatrix * vec4(a_Pos, 1.0);
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
	m_shader.reset(LT::Shader::Create("TestShader", vertexSrc, fragmentSrc));
	m_camera.reset(new LT::PerspectiveCamera(45.f, (float)LT::Application::get().GetWindow().GetWidth() / (float)LT::Application::get().GetWindow().GetHeight(), 0.1f, 100.f));
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
		
	LT::RenderCommand::SetClearColor({ 0.f, 0.6f, 0.4f, 1.f });
	LT::RenderCommand::Clear();

	m_camera->SetPosition({ m_pos[0], m_pos[1], m_pos[2] });
	m_camera->SetRotation(m_yaw, m_pitch);
	LT::Renderer::BeginScene(m_camera->GetViewProjectionMatrix());
	LT::Renderer::Submit(m_shader, m_vertexArray, glm::translate(glm::mat4(1.f), { 1.f, 1.f, 1.f }));
	LT::Renderer::EndScene();
}

void ExampleLayer::OnEvent(LT::Event& ev)
{
	
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Camera Props");
	ImGui::DragFloat3("Camera Position", m_pos, 0.01f);
	ImGui::DragFloat("Yaw", &m_yaw);
	ImGui::DragFloat("Pitch", &m_pitch);
	ImGui::End();

	ImGui::SetNextWindowBgAlpha(0.35f);
	ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoMove);
	ImGui::Text(" Hi!\n Fps: %i", m_fps);
	ImGui::End();
}