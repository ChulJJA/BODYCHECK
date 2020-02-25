/*
 * Author		:Sangmin Kim
 * File			:Component_Hpbar.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Component_Hpbar.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Component.hpp"

class Hp_Bar : public Component
{
public:
    void Init(Object* obj) override;
    void Update(float dt) override;
    void Decrease(float dmg);

    int& Get_Set_Offset();

private:
    int offset;
    int hp;
};