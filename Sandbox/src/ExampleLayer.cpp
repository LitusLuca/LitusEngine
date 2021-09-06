#include "ExampleLayer.h"

ExampleLayer::ExampleLayer() : Layer("Example")
{
}

void ExampleLayer::onUpdate()
{
	LT_INFO("ExampleLayer::onUpdate()");
}

void ExampleLayer::onEvent(LT::Event& ev)
{
	LT_TRACE("{0}", ev.toString());
}
