/*
 * Author		:Sangmin Kim
 * File			:Component_Enemy.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Component Enemy
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */


#pragma once
#include "Component.hpp"

class Component_Enemy : public Component
{
public:
    void Init(Object* obj) override;
    void Update(float dt) override;
    void Decrease_HP(int dmg = 1);

private:
    int hp = 20;
};