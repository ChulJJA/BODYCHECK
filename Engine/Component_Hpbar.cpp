/*
 * Author		:Sangmin Kim
 * File			:Component_Hpbar.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Component for hpbar objects for each player.
 *				 Check the enemy's current health, decrease the scale,
 *				 manipulate the translation offset.
 *				 If the player is dead, send message for respawn to referee.
 *
 *	copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Hpbar.h"
#include "Object.h"
#include "Message_Manager.h"
#include "Referee.h"
#include "Component_Text.h"
#include "Component_Player.h"
#include "Message_Kind.h"
#include "ObjectManager.h"

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
			if (hitting_obj != nullptr)
			{
				hitting_obj->GetTransform().GetScale_Reference() += {0.7f, 0.7f};
				hitting_obj->Get_Plus_Dmg() += 0.1f;
				Object* audience = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience");

				if(hitting_obj->GetName() == "first")
				{
					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience, nullptr, Message_Kind::Audience_Green_Joy, 3.f));
				}
				else if (hitting_obj->GetName() == "second")
				{
					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience, nullptr, Message_Kind::Audience_Red_Joy, 3.f));
				}
				else if (hitting_obj->GetName() == "third")
				{
					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience, nullptr, Message_Kind::Audience_Blue_Joy, 3.f));
				}
				else if (hitting_obj->GetName() == "forth")
				{
					Message_Manager::Get_Message_Manager()->Save_Message(new Message(
						audience, nullptr, Message_Kind::Audience_Normal_Joy, 3.f));
				}
			}
			
			m_owner->SetDeadCondition(true);
			//hp_owner->SetDeadCondition(true);
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
		hp_owner->GetComponentByTemplate<Player>()->Change_To_Normal_State();
		curr_state = Hp_Bar_State::None;
	}
}

int& Hp_Bar::Get_Set_Offset()
{
	return offset;
}
