/*
 * Author		:Sangmin Kim
 * File			:Component_Enemy.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Enemy component which is not used at now.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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