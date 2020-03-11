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
#include "angles.hpp"
#include "UsefulTools.hpp"

Physics::Physics(bool ghost_collision_mode) : ghost_collision_mode(ghost_collision_mode)
{
}

void Physics::Init(Object* obj)
{
	m_owner = obj;
	m_owner->Get_Component_Info_Reference().component_info_physics = true;
}

void Physics::Acceleration(float max_accel, float min_accel)
{
	if (input.Is_Key_Pressed(GLFW_KEY_RIGHT) || input.Is_Key_Pressed(GLFW_KEY_LEFT) ||
		input.Is_Key_Pressed(GLFW_KEY_DOWN) || input.Is_Key_Pressed(GLFW_KEY_UP))
	{
		vector2 obj_pos = { 0, 0 };

		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
		{
			obj_pos.x += 10.f;

			if (input.Is_Key_Pressed(GLFW_KEY_UP))
			{
				obj_pos.y += 10.f;
			}
			if (input.Is_Key_Pressed(GLFW_KEY_DOWN))
			{
				obj_pos.y -= 10.f;
			}
		}
		if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
		{
			obj_pos.x -= 10.f;

			if (input.Is_Key_Pressed(GLFW_KEY_DOWN))
			{
				obj_pos.y -= 10.f;
			}
			if (input.Is_Key_Pressed(GLFW_KEY_UP))
			{
				obj_pos.y += 10.f;
			}
		}

		if (input.Is_Key_Pressed(GLFW_KEY_DOWN))
		{
			obj_pos.y -= 10.f;

			if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
			{
				obj_pos.x += 10.f;
			}
			if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
			{
				obj_pos.x -= 10.f;
			}
		}

		if (input.Is_Key_Pressed(GLFW_KEY_UP))
		{
			obj_pos.y += 10.f;

			if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
			{
				obj_pos.x += 10.f;
			}
			if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
			{
				obj_pos.x -= 10.f;
			}
		}

		float angle = RadianToDegree(angle_between({ 0,1 }, obj_pos));
		if (obj_pos.x >= 0)
		{
			angle *= -1;
		}
		m_owner->SetRotation(angle);
		object_angle = normalize(obj_pos);
	}
	return;
}


void Physics::JustMove()
{
	acceleration += {-acceleration.x / 100, -acceleration.y / 100};
}

void Physics::KnockBack(Object* object_1, Object* object_2)
{
	if (object_1->GetComponentByTemplate<Physics>() != nullptr && object_2->GetComponentByTemplate<Physics>() != nullptr)
	{
		vector2 object_1_pos = object_1->GetTransform().GetTranslation();
		vector2 object_2_pos = object_2->GetTransform().GetTranslation();
		vector2 object_1_acceleration = object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity();
		vector2 object_2_acceleration = object_2->GetComponentByTemplate<Player>()->GetPlayerVelocity();
		vector2 direction_to_go;

		float object_1_speed = sqrt((object_1_acceleration.x * object_1_acceleration.x) + (object_1_acceleration.y * object_1_acceleration.y));
		float object_2_speed = sqrt((object_2_acceleration.x * object_2_acceleration.x) + (object_2_acceleration.y * object_2_acceleration.y));

		if (object_2_speed >= object_1_speed)
		{
			sound.Play(SOUND::Crack);
			direction_to_go = normalize(object_1_pos - object_2_pos);

			object_1->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go * object_2_speed);
			object_1->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity());

			object_2->GetComponentByTemplate<Player>()->SetPlayerVelocity(-direction_to_go * object_2_speed / 2);
			object_2->GetTransform().AddTranslation(object_2->GetComponentByTemplate<Player>()->GetPlayerVelocity());
		}
		else if (object_2_speed < object_1_speed)
		{
			sound.Play(SOUND::Crack);

			direction_to_go = normalize(object_2_pos - object_1_pos);

			object_2->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go * object_1_speed);
			object_2->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity());

			object_1->GetComponentByTemplate<Player>()->SetPlayerVelocity(-direction_to_go * object_1_speed / 2);
			object_1->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Player>()->GetPlayerVelocity());
		}
	}
}

void Physics::Dash(Object* object)
{
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::Dash)
	{
		sound.Play(SOUND::Dash);
		timer = 0;
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, "dash", 1.f));
		is_dashed = true;
	}
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::HP)
	{
		sound.Play(SOUND::HP);
		Object* hp_bar = object->Get_Belong_Object_By_Tag("hp_bar");
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(hp_bar, object, "recover", 1.f));
	}

	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::Bulkup)
	{
		sound.Play(SOUND::BulkUp);
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, "bulkup", 3.f));
	}

	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::Throwing)
	{
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, "throwing", 0.f));
	}
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::Magnatic)
	{
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, "magnatic", 0.f));
	}

	return;
}

void Physics::SpeedDown(Object* object)
{
	vector2 acceleration = object->GetComponentByTemplate<Player>()->GetPlayerVelocity();

	acceleration /= 5;

	object->GetComponentByTemplate<Player>()->SetPlayerVelocity(acceleration);
}

void Physics::Update(float dt)
{
	timer += dt;
	
	if (m_owner->GetName() == "first")
	{
		Player* info_player = m_owner->GetComponentByTemplate<Player>();

		if (info_player->Get_Char_State() == Player::Char_State::None)
		{
			Acceleration(0.6f, 0.12f);
			m_owner->GetTransform().AddTranslation(acceleration);
			if (is_dashed == false && timer >= 0.3)
			{
				Dash(m_owner);
			}
			else if (is_dashed == true && timer >= 0.5)
			{
				SpeedDown(m_owner);
				is_dashed = false;
			}
		}
	}
	else if (m_owner->GetName() == "second")
	{
		Player* info_player = m_owner->GetComponentByTemplate<Player>();

		if (info_player->Get_Char_State() == Player::Char_State::None)
		{
			//Acceleration(0.6f, 0.12f);
			m_owner->GetTransform().AddTranslation(acceleration);

			if (is_dashed == false && timer >= 0.3)
			{
				Dash(m_owner);
			}
			else if (is_dashed == true && timer >= 0.5)
			{
				SpeedDown(m_owner);
				is_dashed = false;
			}
		}
	}
	else if (m_owner->GetName() == "third")
	{
		Player* info_player = m_owner->GetComponentByTemplate<Player>();

		if (info_player->Get_Char_State() == Player::Char_State::None)
		{
			//Acceleration(0.6f, 0.12f);
			m_owner->GetTransform().AddTranslation(acceleration);

			if (is_dashed == false && timer >= 0.3)
			{
				Dash(m_owner);
			}
			else if (is_dashed == true && timer >= 0.5)
			{
				SpeedDown(m_owner);
				is_dashed = false;
			}
		}
	}
	else if (m_owner->GetName() == "forth")
	{
		Player* info_player = m_owner->GetComponentByTemplate<Player>();

		if (info_player->Get_Char_State() == Player::Char_State::None)
		{
			//Acceleration(0.6f, 0.12f);
			m_owner->GetTransform().AddTranslation(acceleration);

			if (is_dashed == false && timer >= 0.3)
			{
				Dash(m_owner);
			}
			else if (is_dashed == true && timer >= 0.5)
			{
				SpeedDown(m_owner);
				is_dashed = false;
			}
		}
	}
	else
	{
		if (m_owner->Get_Tag() != "throwing")
		{
			JustMove();
		}
	}

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