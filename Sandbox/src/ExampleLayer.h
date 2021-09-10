#pragma once
#include "Litus.h"
class ExampleLayer :
    public LT::Layer
{
public:
    ExampleLayer();

    void onUpdate() override;
    void onEvent(LT::Event& ev) override;
    void onImGuiRender() override;
};

