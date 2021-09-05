#include <Litus.h>
#include <pch.h>
#include <iostream>

class Sandbox : public LT::Application
{
public:
	Sandbox()
	{
		std::cout << "Sandbox app!!\n";
	}
	~Sandbox()
	{

	}
};

LT::Application* LT::createApplication()
{
	return new Sandbox();
}