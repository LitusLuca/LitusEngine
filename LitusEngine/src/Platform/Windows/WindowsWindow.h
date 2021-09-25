#pragma once
#include "Litus\core\Window.h"
#include "Litus\Renderer\GraphicsContext.h"
#include "GLFW\glfw3.h"

namespace LT {
    class WindowsWindow :
        public Window
    {
    public:
        WindowsWindow(const WindowProps& l_props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const { return m_data.Width; }
        unsigned int GetHeight() const { return m_data.Height; }

        void SetEventCallback(const EventCallBackFn& callback) override { m_data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void* GetNativeWindow() const override { return m_window; }
        float GetTime() const override { return (float)glfwGetTime(); }

    private:
        virtual void Init(const WindowProps& l_props);
        virtual void Shutdown();
    private:
        GLFWwindow* m_window;
        GraphicsContext* m_context;
        
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallBackFn EventCallback;
        };

        WindowData m_data;
    };
}
