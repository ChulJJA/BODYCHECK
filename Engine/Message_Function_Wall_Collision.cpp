/*
 * Author		:Sangmin Kim
 * File			:Message Function Wall Collision.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Wall Collision
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Wall_Collision.h"
#include "Component_Player.h"
#include "Component_Hpbar.h"
#include "Physics.h"
#include "Component_Text.h"
#include "Message.h"
#include "Engine.hpp"

void Msg_Func_Wall_Collision::Init()
{
	
}

void Msg_Func_Wall_Collision::Update(float dt)
{
	if (m_target->GetComponentByTemplate<Player>() != nullptr)
	{
		Object* target_hp_bar = m_target->Get_Belong_Object_By_Tag("hp_bar");
		Player* find_object_state = m_target->GetComponentByTemplate<Player>();
		if (target_hp_bar != nullptr)
		{
			if (target_hp_bar->GetComponentByTemplate<Hp_Bar>() != nullptr)
			{
				float damage_to_target = 0;
				Physics* temp_physics = m_target->GetComponentByTemplate<Physics>();

				damage_to_target -= m_target->Get_Plus_Dmg();
				
				sound.Play(SOUND::WallCrack);
				target_hp_bar->GetComponentByTemplate<Hp_Bar>()->Decrease(damage_to_target / 200);

			}
		}
		
		if (find_object_state->Get_Char_State_Additional() == Player::Char_State_Additional::Get_mine)
		{
			find_object_state->Change_To_Normal_State();
		}
	}
	msg->Set_Should_Delete(true);
}
