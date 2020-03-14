/*
 * Author		:Chulseung Lee
 * File			:Component_Collision.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Component_Collision.cpp.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include "Component.hpp"
#include "Physics.h"

class Collision : public Component
{
public:
    void Init(Object *obj) override;
    void Update(float dt) override;
    bool CircleToCircleCollision();
    void SquareArenaCollision();

	bool Check_Need_To_Check_Collision(Object* obj_i, Object* obj_j);
	bool ObjectFilter(Object* obj);
	void Collision_Off_Lock_And_Player(Object* obj_i, Object* obj_j);
private:
    Physics physics;
    float timer = 0;
};