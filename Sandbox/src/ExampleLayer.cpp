#include "ExampleLayer.h"

#include "ImGui\imgui.h"

ExampleLayer::ExampleLayer() : Layer("Example")
{
}

void ExampleLayer::onUpdate()
{
	LT_INFO("ExampleLayer::onUpdate()");
	auto [x, y] = LT::Input::getMousePos();
	LT_TRACE("{0}, {1}", x, y);
}

void ExampleLayer::onEvent(LT::Event& ev)
{
	LT_TRACE("{0}", ev.toString());
}

void ExampleLayer::onImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::Text("Hello");
	ImGui::End();
}