/*
 * Author		:Sangmin Kim
 * File			:Component_Timer.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Component Timer
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

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