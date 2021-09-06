#include <Litus.h>
#include <Litus\core\EntryPoint.h>

#include <pch.h>
#include <iostream>
#include "ExampleLayer.h"

class Sandbox : public LT::Application
{
public:
	Sandbox()
	{
		std::cout << "Sandbox app!!\n";
		pushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

LT::Application* LT::createApplication()
{
	return new Sandbox();
}