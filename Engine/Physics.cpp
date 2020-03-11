/*
 * Author		:Chulseung Lee
 * File			:Physics.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Acceleration / Knockback / user input by controller is implemented.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Physics.h"
#include "ObjectManager.h"
#include <cmath>
#include "vector2.hpp"
#include "Input.h"
#include "Component_Sprite.h"
#include "Component_Player.h"
#include "Player_Ui.h"
#include "Message_Manager.h"
#include "Engine.hpp"
#include "Message.h"
#include "Application.hpp"
#include "UsefulTools.hpp"

Physics::Physics(bool ghost_collision_mode) : ghost_collision_mode(ghost_collision_mode) {}

void Physics::Init(Object* obj)
{
	m_owner = obj;
	m_owner->Get_Component_Info_Reference().component_info_physics = true;
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
			sound.Play(SOUND::Crack);

			direction_to_go = normalize(object_1_pos - object_2_pos);

			object_1->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go * object_2_speed);
			object_1->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity());

			object_2->GetComponentByTemplate<Player>()->SetPlayerVelocity(-direction_to_go * object_2_speed / 4);
			object_2->GetTransform().AddTranslation(object_2->GetComponentByTemplate<Player>()->GetPlayerVelocity());
		}
		else if (object_2_speed < object_1_speed)
		{
			sound.Play(SOUND::Crack);

			direction_to_go = normalize(object_2_pos - object_1_pos);

			object_2->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go * object_1_speed);
			object_2->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity());

			object_1->GetComponentByTemplate<Player>()->SetPlayerVelocity(-direction_to_go * object_1_speed / 4);
			object_1->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity());
		}
	}
}

void Physics::SpeedDown(Object* object)
{
	if(!object->IsDead())
	{
		vector2 velocity = object->GetComponentByTemplate<Player>()->GetPlayerVelocity();

		velocity /= 5;

		object->GetComponentByTemplate<Player>()->SetPlayerVelocity(velocity);
	}
}

void Physics::Update(float dt)
{
	if (ghost_collision_mode)
	{
		ghost_collision_timer -= dt;

		if (ghost_collision_timer <= 0.0f)
		{
			ghost_collision_mode = false;
			if (m_owner->GetComponentByTemplate<Sprite>() != nullptr)
			{
				m_owner->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1.0f,1.0f,1.0f,1.0f };
			}
			ghost_collision_timer = 1.0f;
		}
	}
}