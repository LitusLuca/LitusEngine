#pragma once
#include "Litus.h"
class ExampleLayer :
    public LT::Layer
{
public:
    ExampleLayer();

    void OnUpdate(LT::Time dT) override;
    void OnEvent(LT::Event& ev) override;
    void OnImGuiRender() override;

private:
    std::shared_ptr<LT::PerspectiveCamera> m_camera;
    std::shared_ptr<LT::VertexArray> m_vertexArray;
    std::shared_ptr<LT::Shader> m_shader;
    float m_pos[3] = { 0.f, 0.f, 1.f };
    float m_yaw = -90.f;
    float m_pitch = 0.f;

    int m_frame = 0;
    float m_time  = 0.f;
    int m_fps = 0;
};

