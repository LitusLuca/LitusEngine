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

        void onUpdate() override;

        unsigned int getWidth() const { return m_data.Width; }
        unsigned int getHeight() const { return m_data.Height; }

        void setEventCallback(const EventCallBackFn& callback) override { m_data.EventCallback = callback; }
        void setVSync(bool enabled) override;
        bool isVSync() const override;

        void* getNativeWindow() const override { return m_window; }

    private:
        virtual void init(const WindowProps& l_props);
        virtual void shutdown();
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
