#pragma once
#include "Component.hpp"

class Component_Timer : public Component
{
public:
    void Init(Object* obj) override;
    void Update(float dt) override;

private:
    float speed = 30.f;
};