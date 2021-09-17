#pragma once
#include "Litus\Renderer\GraphicsContext.h"

struct GLFWwindow;

namespace LT {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}