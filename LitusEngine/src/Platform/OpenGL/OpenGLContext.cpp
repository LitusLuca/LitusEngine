#include "pch.h"

#include "GLFW\glfw3.h"
#include "OpenGLContext.h"

#include <glad\glad.h>

namespace LT {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
		m_windowHandle(windowHandle)
	{
		LT_CORE_ASSERT(m_windowHandle, "Window handle is NULL!")
	}
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LT_CORE_ASSERT(status, "Failed to initialize GLAD!");

		LT_CORE_INFO("OpenGL vendor: {0}", glGetString(GL_VENDOR));
		LT_CORE_INFO("OpenGL renderer: {0}", glGetString(GL_RENDERER));
		LT_CORE_INFO("OpenGL version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}