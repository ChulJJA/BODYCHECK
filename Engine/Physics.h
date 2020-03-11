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
#include "Mesh.hpp"

class Physics : public Component
{
public:
    Physics(bool ghost_collision_mode = false);
    void Init(Object* obj) override;
    void KnockBack(Object* object_1, Object* object_2);
    void Dash(Object* object);
    void SpeedDown(Object* object);
    void Update(float dt) override;
    bool& Get_Ghost_Collision_Reference()
    {
        return ghost_collision_mode;
    }
    bool is_collided = false;
    bool is_dashed = false;

private:
    vector2 acceleration{};
    mutable float timer = 0;

    bool ghost_collision_mode;
    float ghost_collision_timer = 5.0f;
};