/*
 * Author		:Chulseung Lee
 * File			:Physics.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Physics.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include "Component.hpp"

class Physics : public Component
{
public:
    Physics(bool ghost_collision_mode = false);//
    void Init(Object* obj) override;
    void Update(float dt) override;
    void KnockBack(Object* object_1, Object* object_2);
    void KnockBack_Missile(Object* player, Object* missile);
    void PushPlayer(Object* player, Object* object);
    void SpeedDown(Object* object);
    bool& GetGhostReference();
    void SetGhostReference(float dt);
    vector2 GetVelocity();
    void SetVelocity(vector2 vel);
    void MoveObject();

private:
	bool is_ghost;
	float ghost_timer = 5.0f;
    vector2 velocity{};
    float sound_timer = 1.0f;
};