#pragma once
#include "Litus\Renderer\GraphicsContext.h"

struct GLFWwindow;

namespace LT {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void init() override;
		void swapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}