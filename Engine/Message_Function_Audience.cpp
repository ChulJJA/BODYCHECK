/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Audience.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Audience
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Audience.h"
#include "Message.h"
#include "Object.h"
#include "Component_Sprite.h"
#include "Referee.h"

void Msg_Func_Audience::Init()
{
	if (m_target != nullptr)
	{
		if (msg->Get_Kind() == Message_Kind::Audience_Blue_Joy)
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Joy));
			
			kill_tag = Referee::Get_Referee()->Get_Third_Kill();
			kill_tag->Set_Need_To_Update(true);
			tag_origin_pos = kill_tag->GetTransform().GetTranslation();
			tag_turning_pos = tag_origin_pos.x + 400.f;
			tag_turn_to = tag_origin_pos.x + 100.f;
			back_speed *= -1.f;
		}
		else if (msg->Get_Kind() == Message_Kind::Audience_Red_Joy)
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Joy));

			kill_tag = Referee::Get_Referee()->Get_Second_Kill();
			kill_tag->Set_Need_To_Update(true);
			tag_origin_pos = kill_tag->GetTransform().GetTranslation();
			tag_turning_pos = tag_origin_pos.x - 400.f;
			tag_turning_pos = tag_origin_pos.x - 100.f;
			speed *= -1.f;
			is_left = false;
		}
		else if (msg->Get_Kind() == Message_Kind::Audience_Normal_Joy)
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Joy));
			
			kill_tag = Referee::Get_Referee()->Get_Fourth_Kill();
			kill_tag->Set_Need_To_Update(true);
			tag_origin_pos = kill_tag->GetTransform().GetTranslation();
			tag_turning_pos = tag_origin_pos.x + 400.f;
			tag_turn_to = tag_origin_pos.x + 100.f;
			back_speed *= -1.f;
		}
		else if (msg->Get_Kind() == Message_Kind::Audience_Green_Joy)
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Joy));

			kill_tag = Referee::Get_Referee()->Get_First_Kill();
			kill_tag->Set_Need_To_Update(true);
			tag_origin_pos = kill_tag->GetTransform().GetTranslation();
			tag_turning_pos = tag_origin_pos.x - 400.f;
			tag_turning_pos = tag_origin_pos.x - 100.f;
			speed *= -1.f;
			is_left = false;
		}

		m_from->Change_Sprite(m_from->Find_Sprite_By_Type(Sprite_Type::Audience_Sad));
	}
}

void Msg_Func_Audience::Update(float dt)
{
	if (timer > 0.f)
	{
		timer -= dt;

		if (kill_tag != nullptr)
		{
			vector2& pos = kill_tag->GetTransform().GetTranslation_Reference();

			if (tag_reach == false)
			{
				if (is_left == true)
				{
					if (pos.x < tag_turning_pos)
					{
						pos.x += dt * speed;
					}
					else
					{
						tag_reach = true;
					}
				}
				else
				{
					if (pos.x > tag_turning_pos)
					{
						pos.x += dt * speed;
					}
					else
					{
						tag_reach = true;
					}
				}
			}
			else
			{

				if(is_left == true)
				{
					if (pos.x > tag_turn_to)
					{
						pos.x += dt * back_speed;
					}
				}
				else
				{
					if (pos.x < tag_turn_to)
					{
						pos.x += dt * back_speed;
					}
				}
			}
		}
	}
	else
	{
		if (!Referee::Get_Referee()->Get_Is_CheerUp_Mode())
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Normal));
			m_from->Change_Sprite(m_from->Find_Sprite_By_Type(Sprite_Type::Audience_Normal));
		}
		else
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Cheerup));
			m_from->Change_Sprite(m_from->Find_Sprite_By_Type(Sprite_Type::Audience_Cheerup));
		}
		msg->Set_Should_Delete(true);

		if (kill_tag != nullptr)
		{
			kill_tag->Set_Need_To_Update(false);
			kill_tag->GetTransform().SetTranslation(tag_origin_pos);
		}
	}

}
