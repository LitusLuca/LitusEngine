#pragma once

#include "Core.h"

namespace LT {
	class LAPI Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* createApplication();
}
