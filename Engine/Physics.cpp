/*
 * Author		:Chulseung Lee
 * File			:Physics.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Physics
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Physics.h"
#include "ObjectManager.h"
#include "vector2.hpp"
#include "Component_Sprite.h"
#include "Component_Player.h"
#include "Engine.hpp"
#include "UsefulTools.hpp"

Physics::Physics(bool is_ghost) : is_ghost(is_ghost) {}

void Physics::Init(Object* obj)
{
	m_owner = obj;
	m_owner->Get_Component_Info_Reference().component_info_physics = true;
}

void Physics::Update(float dt)
{
	SetGhostReference(dt);
	//MoveObject();
}

void Physics::KnockBack(Object* object_1, Object* object_2)
{
	if (object_1->GetComponentByTemplate<Physics>() != nullptr && object_2->GetComponentByTemplate<Physics>() != nullptr)
	{
		vector2 object_1_pos = object_1->GetTransform().GetTranslation();
		vector2 object_2_pos = object_2->GetTransform().GetTranslation();
		vector2 object_1_velocity = object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity();
		vector2 object_2_velocity = object_2->GetComponentByTemplate<Player>()->GetPlayerVelocity();
		vector2 direction_to_go;
		float object_1_speed = VectorToScalar(object_1_velocity);
		float object_2_speed = VectorToScalar(object_2_velocity);

		if (object_2_speed >= object_1_speed)
		{

			direction_to_go = normalize(object_1_pos - object_2_pos);

			object_1->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go * object_2_speed);
			object_1->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity());

			object_2->GetComponentByTemplate<Player>()->SetPlayerVelocity(-direction_to_go * object_2_speed / 4);
			object_2->GetTransform().AddTranslation(object_2->GetComponentByTemplate<Player>()->GetPlayerVelocity());
		}
		else if (object_2_speed < object_1_speed)
		{

			direction_to_go = normalize(object_2_pos - object_1_pos);

			object_2->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go * object_1_speed);
			object_2->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity());

			object_1->GetComponentByTemplate<Player>()->SetPlayerVelocity(-direction_to_go * object_1_speed / 4);
			object_1->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity());
		}
	}
}

void Physics::KnockBack_Missile(Object* player, Object* missile)
{
	if (player->GetComponentByTemplate<Physics>() != nullptr && missile->GetComponentByTemplate<Physics>() != nullptr)
	{
		const vector2 object_1_pos = player->GetTransform().GetTranslation();
		const vector2 object_2_pos = missile->GetTransform().GetTranslation();

		const vector2 object_2_velocity = missile->GetComponentByTemplate<Physics>()->GetVelocity();
		const vector2 direction_to_go = normalize(object_1_pos - object_2_pos);
		const float object_2_speed = VectorToScalar(object_2_velocity);

		player->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go * object_2_speed);
		player->GetTransform().AddTranslation(player->GetComponentByTemplate<Player>()->GetPlayerVelocity());
	}
}

void Physics::PushPlayer(Object* player, Object* object)
{
	vector2 object_velocity = object->GetComponentByTemplate<Physics>()->GetVelocity();

	Player* info_player = player->GetComponentByTemplate<Player>();

	if (info_player != nullptr)
	{
		info_player->SetPlayerVelocity(object_velocity);
	}
}

void Physics::SpeedDown(Object* object)
{
	Component* info_player = object->GetComponentByTemplate<Player>();
	if (info_player != nullptr)
	{
		if (!object->IsDead())
		{
			vector2 velocity = object->GetComponentByTemplate<Player>()->GetPlayerVelocity();

			velocity /= 5;

			object->GetComponentByTemplate<Player>()->SetPlayerVelocity(velocity);
		}
	}
}

bool& Physics::GetGhostReference()
{
	return is_ghost;
}

void Physics::SetGhostReference(float dt)
{
	if (is_ghost)
	{
		ghost_timer -= dt;

		if (ghost_timer <= 0.0f)
		{
			if (m_owner->GetComponentByTemplate<Sprite>() != nullptr)
			{
				m_owner->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1.0f,1.0f,1.0f,1.0f };
			}

			ghost_timer = 1.0f;
			is_ghost = false;
			m_owner->SetNeedCollision(true);
		}
	}
}

vector2 Physics::GetVelocity()
{
	return velocity;
}

void Physics::SetVelocity(vector2 vel)
{
	velocity.x = vel.x;
	velocity.y = vel.y;
}

void Physics::MoveObject()
{
	m_owner->GetTransform().AddTranslation(velocity);
}
