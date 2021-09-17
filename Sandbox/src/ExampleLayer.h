#pragma once
#include "Litus.h"
class ExampleLayer :
    public LT::Layer
{
public:
    ExampleLayer();

    void OnUpdate() override;
    void OnEvent(LT::Event& ev) override;
    void OnImGuiRender() override;
};

