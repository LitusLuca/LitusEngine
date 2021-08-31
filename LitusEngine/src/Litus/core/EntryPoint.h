#pragma once

#ifdef LT_PLATFORM_WINDOWS

extern LT::Application* LT::createApplication();

int main(int argc, char** charv)
{
	auto app = LT::createApplication();
	app->run();
	delete app;
}

#endif // LT_PLATFORM_WINDOWS
