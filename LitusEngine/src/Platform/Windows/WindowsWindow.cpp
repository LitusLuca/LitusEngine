#include "pch.h"
#include "WindowsWindow.h"

#include "Litus\Event\ApplicationEvents.h"
#include "Litus\Event\KeyEvents.h"
#include "Litus\Event\MouseEvents.h"

#include <glad\glad.h>

namespace LT {

	static bool s_GLFW_INITIALIZED = false;

	static void GLFWErrorCallback(int error_code, const char* description)
	{
		LT_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	Window* Window::create(const WindowProps& l_props)
	{
		return new WindowsWindow(l_props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& l_props)
	{
		init(l_props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::init(const WindowProps& l_props)
	{
		m_data.Title = l_props.Title;
		m_data.Width = l_props.Width;
		m_data.Height = l_props.Height;

		LT_CORE_INFO("Creating a window {0} {1}, {2}", l_props.Title, l_props.Width, l_props.Height);

		if (!s_GLFW_INITIALIZED)
		{
			int succes = glfwInit();
			LT_CORE_INFO("GLFW Init: {0}", succes);
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFW_INITIALIZED = true;
		}
		m_window = glfwCreateWindow((int)m_data.Width, (int)m_data.Height, m_data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LT_CORE_INFO("Glad initialized with: ({0})", status);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		//setting event callbacks:

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent ev(width, height);
			data.EventCallback(ev);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent ev;
			data.EventCallback(ev);
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent ev(key, 0);
					data.EventCallback(ev);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent ev(key);
					data.EventCallback(ev);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent ev(key, 1);
					data.EventCallback(ev);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent ev(button);
					data.EventCallback(ev);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent ev(button);
					data.EventCallback(ev);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent ev((float)xOffset, (float)yOffset);
				data.EventCallback(ev);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent ev((float)xPos, (float)yPos);
				data.EventCallback(ev);
			});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}
	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = enabled;
	}
	bool WindowsWindow::isVSync() const
	{
		return m_data.VSync;
	}
}