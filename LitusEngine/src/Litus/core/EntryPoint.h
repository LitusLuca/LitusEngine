#pragma once

#ifdef LT_PLATFORM_WINDOWS

extern LT::Application* LT::createApplication();

int main(int argc, char** charv)
{
	LT::Log::init();
	auto app = LT::createApplication();
	app->Run();
	delete app;
}

#endif // LT_PLATFORM_WINDOWS
