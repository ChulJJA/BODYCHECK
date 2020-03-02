/*
 * Author		:Chulseung Lee
 * File			:Component_Collision.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Collision check of objects in engine.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Collision.h"
#include "Physics.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Engine.hpp"
#include "Message_Manager.h"
#include "Component_Sprite.h"
#include "Message.h"

#define  PI  3.14159265359

float RadianToDegree(float radian)
{
    float degree = static_cast<float>(radian * (180 / PI));

    return degree;
}

float DegreeToRadian(float degree)
{
    float radian = static_cast<float>(degree * (PI / 180));

    return radian;
}

void Collision::Init(Object* obj)
{
    m_owner = obj;
}

bool Collision::BoxToBoxCollision(Mesh mesh) const
{
    if (m_owner->GetMesh().GetPoint(0).x > mesh.GetPoint(2).x || m_owner->GetMesh().GetPoint(0).y > mesh.GetPoint(2).y)
    {
        return false;
    }
    else if (m_owner->GetMesh().GetPoint(1).x > mesh.GetPoint(3).x || m_owner->GetMesh().GetPoint(1).y < mesh.GetPoint(3).y)
    {
        return false;
    }
    else if (m_owner->GetMesh().GetPoint(2).x < mesh.GetPoint(0).x || m_owner->GetMesh().GetPoint(2).y < mesh.GetPoint(0).y)
    {
        return false;
    }
    else if (m_owner->GetMesh().GetPoint(3).x < mesh.GetPoint(1).x || m_owner->GetMesh().GetPoint(3).y > mesh.GetPoint(1).y)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Collision::CircleToCircleCollision()
{
    bool if_it_is_collide = false;
    unsigned int object_position_size = static_cast<unsigned int>(ObjectManager::GetObjectManager()->GetObjectManagerContainer().size());

    for (unsigned int i = 0; i < object_position_size; ++i)
    {
        Object* obj_i = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[i].get();

        if (obj_i->Get_Tag() == "player" || obj_i->Get_Tag() == "item")
        {
            if (obj_i->Get_Need_To_Update())
            {
                vector2 obj_i_trans = obj_i->GetTransform().GetTranslation();
                float obj_i_radius = obj_i->GetTransform().GetScale().x * 30.f;

                for (unsigned int j = 0; j < object_position_size; ++j)
                {
                    Object* obj_j = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[j].get();
                    if (obj_j->GetName() == "arena" || obj_i->GetName() == "arena")
                    {
                        continue;
                    }
                    if (obj_j->Get_Tag() == "item" && obj_i->Get_Tag() == "item")
                    {
                        continue;
                    }
                    if (obj_j->Get_Tag() == "player" || obj_j->Get_Tag() == "item")
                    {
                        if (obj_j->Get_Need_To_Update())
                        {
                            vector2 obj_j_trans = obj_j->GetTransform().GetTranslation();
                            float obj_j_radius = obj_j->GetTransform().GetScale().x * 30.f;
                            if (i != j)
                            {

                                const float distance = sqrt((obj_i_trans.x - obj_j_trans.x) * (obj_i_trans.x - obj_j_trans.x) + (obj_i_trans.y - obj_j_trans.y) * (obj_i_trans.y - obj_j_trans.y));
                                if (distance < obj_i_radius + obj_j_radius)
                                {

                                    if (obj_i->GetComponentByTemplate<Physics>() != nullptr && obj_j->GetComponentByTemplate<Physics>() != nullptr)
                                    {
                                        if (!obj_i->GetComponentByTemplate<Physics>()->Get_Ghost_Collision_Reference() && !obj_j->GetComponentByTemplate<Physics>()->Get_Ghost_Collision_Reference())
                                        {
                                            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().x;
                                            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().y;
                                            obj_j->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_j->GetComponentByTemplate<Physics>()->GetAcceleration().x;
                                            obj_j->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_j->GetComponentByTemplate<Physics>()->GetAcceleration().y;
                                            Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_j, obj_i, "collision"));

                                            if (obj_i->Get_Tag() != "item" && obj_j->Get_Tag() != "item")
                                            {
                                                physics.KnockBack(obj_i, obj_j);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                    }

                }
            }
        }
    }
    return if_it_is_collide;
}

void Collision::CircleArenaCollision()
{
    const unsigned int object_position_size = static_cast<unsigned int>(ObjectManager::GetObjectManager()->GetObjectManagerContainer().size());

    for (unsigned int i = 0; i < object_position_size; ++i)
    {
        Object* obj_i = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[i].get();
        vector2 obj_i_trans = obj_i->GetTransform().GetTranslation();

        const float distance = sqrt((obj_i_trans.x * obj_i_trans.x) + (obj_i_trans.y * obj_i_trans.y));

        if (distance >= 10000)
        {

            const vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();
            obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(-direction_to_go);
        }
    }
}

void Collision::SquareArenaCollision()
{
    const unsigned int object_position_size = static_cast<unsigned int>(ObjectManager::GetObjectManager()->GetObjectManagerContainer().size());
    const float line_max_point = 980;
    const float line_min_point = -980;
    float angle = 0;
    float angle2 = 0;
    for (unsigned int i = 0; i < object_position_size; ++i)
    {
        Object* obj_i = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[i].get();
        vector2 obj_i_trans = obj_i->GetTransform().GetTranslation();
        vector2 obj_i_scale = obj_i->GetTransform().GetScale();

        const double max_x = obj_i_trans.x + (30.0 * obj_i_scale.x);
        const double min_x = obj_i_trans.x - (30.0 * obj_i_scale.x);
        const double max_y = obj_i_trans.y + (30.0 * obj_i_scale.y);
        const double min_y = obj_i_trans.y - (30.0 * obj_i_scale.y);

        if (line_max_point - max_x < 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr)
        {
            sound.Play(SOUND::Crack);

            vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();

            angle = RadianToDegree(angle_between({ 0,1 }, direction_to_go));
            angle2 = 2 * (180 - angle);
            angle = 360 - angle2;
            direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
            obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go);

            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().x;
            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().y;

            Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, "wall_collision"));
        }
        else if (line_max_point - max_y < 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr)
        {
            sound.Play(SOUND::Crack);

            vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();
            angle = RadianToDegree(angle_between({ -1,0 }, direction_to_go));

            angle2 = 2 * (180 - angle);
            angle = 360 - angle2;
            direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
            obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go);

            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().x;
            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().y;

            Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, "wall_collision"));
        }
        else if (line_min_point - min_x > 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr)
        {
            sound.Play(SOUND::Crack);

            vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();
            angle = RadianToDegree(angle_between({ 0,-1 }, direction_to_go));

            angle2 = 2 * (180 - angle);
            angle = 360 - angle2;
            direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
            obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go);

            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().x;
            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().y;

            Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, "wall_collision"));
        }
        else if (line_min_point - min_y > 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr)
        {
            sound.Play(SOUND::Crack);

            vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();
            angle = RadianToDegree(angle_between({ 1,0 }, direction_to_go));

            angle2 = 2 * (180 - angle);
            angle = 360 - angle2;
            direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
            obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go);

            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().x;
            obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().y;

            Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, "wall_collision"));
        }
    }
}

void Collision::Update(float dt)
{
    sound_timer += dt;
    CircleToCircleCollision();
    SquareArenaCollision();
}