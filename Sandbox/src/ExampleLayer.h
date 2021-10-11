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
    void RecalculateDir();

    LT::Ref<LT::PerspectiveCamera> m_camera;
    LT::Ref<LT::VertexArray> m_vertexArray;
    LT::ShaderLibrary m_shaderLibrary;
    LT::Ref<LT::Texture2D> m_texture;
    glm::vec3 m_pos = { 0.f, 0.f, 0.f };
    glm::vec3 m_dir = { 0.f, 0.f, -1.f };
    glm::vec2 m_mousePos = { 0, 0 };
    
    float m_yaw = -90.f;
    float m_pitch = 0.f;
    float m_sens = 0.1f;

    int m_frame = 0;
    float m_time  = 0.f;
    int m_fps = 0;
};

