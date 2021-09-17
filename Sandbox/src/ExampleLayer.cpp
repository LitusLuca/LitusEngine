#include "ExampleLayer.h"

#include "ImGui\imgui.h"

ExampleLayer::ExampleLayer() : Layer("Example")
{
}

void ExampleLayer::OnUpdate()
{
}

void ExampleLayer::OnEvent(LT::Event& ev)
{
	
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::Text("Hello");
	ImGui::End();
}