/*
 * Author		:Sangmin Kim
 * File			:Component_Enemy.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Component Enemy
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Enemy.h"
#include "Object.h"

void Component_Enemy::Init(Object* obj)
{
    m_owner = obj;
}

void Component_Enemy::Update(float dt)
{
    if (hp <= 0)
    {
        m_owner->SetDeadCondition(true);
    }
}

void Component_Enemy::Decrease_HP(int dmg)
{
    hp -= dmg;
}