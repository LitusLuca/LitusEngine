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
    LT::Ref<LT::PerspectiveCamera> m_camera;
    LT::Ref<LT::VertexArray> m_vertexArray;
    LT::Ref<LT::Shader> m_shader;
    float m_pos[3] = { 0.f, 0.f, 1.f };
    float m_yaw = -90.f;
    float m_pitch = 0.f;

    int m_frame = 0;
    float m_time  = 0.f;
    int m_fps = 0;
};

