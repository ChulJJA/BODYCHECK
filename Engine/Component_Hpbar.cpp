/*
 * Author		:Sangmin Kim
 * File			:Component_Hpbar.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Component HB Bar
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Hpbar.h"
#include "Object.h"
#include "Message_Manager.h"
#include "Referee.h"
#include "Component_Text.h"
#include "Component_Player.h"
#include "Message_Kind.h"
#include "ObjectManager.h"
#include "Sound_Manager.h"
#include "Engine.hpp"

void Hp_Bar::Init(Object* obj)
{
	m_owner = obj;
	offset = 0;
	hp_owner = m_owner->Get_This_Obj_Owner();
}

void Hp_Bar::Update(float dt)
{
	if (curr_state != Hp_Bar_State::None)
	{
		if (curr_state == Hp_Bar_State::Recovering)
		{
			Recovering(dt);
		}
		else if (curr_state == Hp_Bar_State::Damaging)
		{
			Damaging(dt);
		}
	}

}

void Hp_Bar::Decrease(float dmg)
{
	vector2& hp_scale = m_owner->GetTransform().GetScale_Reference();
	Object* hitting_obj = hp_owner->Get_Hitted_By();
	
	if (hp_scale.x > 0)
	{
		const float damage = dmg;
		hp_scale.x -= damage;
		
		offset -= static_cast<int>(damage * 50);

		if (hp_scale.x <= 0)
		{
			Graphic::GetGraphic()->Get_View().Active_Screen_Shake(30.f, 5);

			if (hitting_obj != nullptr)
			{
				Object* die_obj_audience = hp_owner->GetComponentByTemplate<Player>()->Get_Audience();

				if(hitting_obj->GetName() == "first")
				{
					Object* audience = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_green");

					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience, die_obj_audience, Message_Kind::Audience_Green_Joy, 3.f));
				}
				else if (hitting_obj->GetName() == "second")
				{
					Object* audience = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_red");

					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience, die_obj_audience, Message_Kind::Audience_Red_Joy, 3.f));

					Object* die_obj_audience2 = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_normal");

					Object* audience2 = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_green");

					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience2, die_obj_audience2, Message_Kind::Audience_Red_Joy, 3.f));
				}
				else if (hitting_obj->GetName() == "third")
				{
					Object* audience = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_blue");

					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience, die_obj_audience, Message_Kind::Audience_Blue_Joy, 3.f));

					Object* die_obj_audience2 = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_green");

					Object* audience2 = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_normal");

					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience2, die_obj_audience2, Message_Kind::Audience_Blue_Joy, 3.f));

				}
				else if (hitting_obj->GetName() == "fourth")
				{
					Object* audience = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_normal");

					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience, die_obj_audience, Message_Kind::Audience_Normal_Joy, 3.f));
				}
			}
			
			m_owner->SetDeadCondition(true);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(hp_owner, nullptr, Message_Kind::Die));
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(Referee::Get_Referee(), hp_owner, Message_Kind::Respawn));
		}
	}
}

void Hp_Bar::Recovering(float dt)
{
	if (timer >= 0.f)
	{
		timer -= dt;
		vector2& scale = m_owner->GetTransform().GetScale_Reference();

		if (scale.x <= 1.f)
		{
			scale.x += dt;
			offset = 0;
		}

		if (timer <= 0.f)
		{
			hp_owner->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Heal)->Set_Need_Update(false);
			curr_state = Hp_Bar_State::None;
		}
	}
}

void Hp_Bar::Damaging(float dt)
{
	if (timer > 0.f)
	{
		timer -= dt;
	}
	else
	{
		if (hp_owner->GetComponentByTemplate<Player>()->Get_Char_State() == Player::Char_State::Time_Pause)
		{
			FMOD_BOOL isBGMPlaying;
			FMOD_BOOL isClocking;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(sound.currentBGM)], &isBGMPlaying);
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::ClockTicking)], &isClocking);
			if (!isBGMPlaying)
			{
				sound.Play(sound.currentBGM);
			}
			if (isClocking)
			{
				sound.Stop(SOUND::ClockTicking);
			}
		}
		hp_owner->GetComponentByTemplate<Player>()->Change_To_Normal_State();
		curr_state = Hp_Bar_State::None;
	}
}

int& Hp_Bar::Get_Set_Offset()
{
	return offset;
}
