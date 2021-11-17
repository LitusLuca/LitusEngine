#include "ExampleLayer.h"

#include "ImGui\imgui.h"
#include "glm\gtc\matrix_transform.hpp"
#include "Litus\Utils\BinaryLoader.h"
#include <iostream>
ExampleLayer::ExampleLayer() : Layer("Example"), m_cameraController(45.f, (float)LT::Application::get().GetWindow().GetWidth() / (float)LT::Application::get().GetWindow().GetHeight(), 1.f, 50.f, 4.f, 0.2f)
{
	m_cameraController.GetCamera().SetPosition({ 0.f, 1.5f, 0.f });
	m_puppy = LT::VertexArray::Create();

	std::vector<float> binVertices;
	LT::BinaryLoader::ReadBinary("assets/meshes/PuppyVertex.bin", binVertices);
	LT::Ref<LT::VertexBuffer> vertexBuffer = LT::VertexBuffer::Create(binVertices.data(), (uint32_t)(binVertices.size() * sizeof(binVertices[0])));

	LT::BufferLayout layout = {
		{LT::ShaderDataType::Float3, "a_Pos"},
		{LT::ShaderDataType::Float3, "a_Normal"},
		{LT::ShaderDataType::Float2, "a_TexCoord"}
	};
	vertexBuffer->SetLayout(layout);
	m_puppy->AddVertexBuffer(vertexBuffer);

	
	std::vector<unsigned int> binIndices;
	LT::BinaryLoader::ReadBinary("assets/meshes/PuppyIndex.bin", binIndices);
	LT::Ref<LT::IndexBuffer> indexBuffer = LT::IndexBuffer::Create(binIndices.data(), (uint32_t)binIndices.size());
	m_puppy->SetIndexBuffer(indexBuffer);

	m_plane = LT::VertexArray::Create();
	std::vector<float> planeV;
	LT::BinaryLoader::ReadBinary("assets/meshes/planeVertex.bin", planeV);
	LT::Ref<LT::VertexBuffer> planeVB = LT::VertexBuffer::Create(planeV.data(), (uint32_t)(planeV.size() * sizeof(binVertices[0])));
	planeVB->SetLayout(layout);
	m_plane->AddVertexBuffer(planeVB);
	std::vector<unsigned int> planeI;
	LT::BinaryLoader::ReadBinary("assets/meshes/planeIndex.bin", planeI);
	LT::Ref<LT::IndexBuffer> planeIB = LT::IndexBuffer::Create(planeI.data(), (uint32_t)planeI.size());
	m_plane->SetIndexBuffer(planeIB);

	m_shaderLibrary.Load("assets/shaders/texCoordShader.glsl");
	m_shaderLibrary.Load("assets/shaders/textureShader.glsl");

	m_texture = LT::Texture2D::Create("assets/textures/Puppy.png");
	m_planeTexture = LT::Texture2D::Create("assets/textures/floor.png");

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
	m_totalTime += (float)dT;
	LT::RenderCommand::SetClearColor({ 0.f, 0.6f, 0.4f, 1.f });
	LT::RenderCommand::Clear();

	m_cameraController.OnUpdate(dT);
	LT::Renderer::BeginScene(m_cameraController.GetCamera().GetViewProjectionMatrix());
	m_texture->Bind();
	LT::Renderer::Submit(m_shaderLibrary.Get("textureShader"), m_puppy, glm::rotate(glm::mat4(1.f), glm::radians(90.f), {-1.f, 0.f, 0.f}));
	m_planeTexture->Bind();
	LT::Renderer::Submit(m_shaderLibrary.Get("textureShader"), m_plane, glm::mat4(1.f));
	LT::Renderer::EndScene();
}

void ExampleLayer::OnEvent(LT::Event& ev)
{
	m_cameraController.OnEvent(ev);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::SetNextWindowBgAlpha(0.35f);
	ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoMove);
	ImGui::Text(" Hi!\n Fps: %i", m_fps);
	ImGui::End();
}