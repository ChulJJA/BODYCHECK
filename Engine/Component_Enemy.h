/*
 * Author		:Sangmin Kim
 * File			:Component_Enemy.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Header file for component_enemy.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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