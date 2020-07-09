/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Item_BulkUp.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Item Bulk Up
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Item_Bulkup.h"
#include "Component_Player.h"
#include "Object.h"
#include "Message.h"
#include "Component_Ui.h"
#include "Player_Ui.h"
#include "Component_Sprite.h"

void Msg_Func_Item_Bulkup::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		if (info_player != nullptr && info_ui != nullptr)
		{
			info_player->Set_Item_State(Item::Item_Kind::None);

			if (info_player->Get_Char_State() == Player::Char_State::None)
			{
				//time for prepare
				info_player->Set_Prepare_Timer(3.f);
				info_player->Set_Char_State(Player::Char_State::Prepare);

				//bulkup item setting.
				info_player->Set_Bulkup_Timer(5.f);
				info_player->Sprite_After_Preparation(obj->Find_Sprite_By_Type(Sprite_Type::Player_Bulkup_Used));

				//info_player->Set_Item_Used_Status(Player::Item_Use_Status::Bulkup);
				
				obj->Change_Sprite(obj->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Bulkp));
			}

			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Bulkup);
		}
	}
}

void Msg_Func_Item_Bulkup::Update(float dt)
{
	Player* info_player = m_target->GetComponentByTemplate<Player>();

	if (info_player != nullptr)
	{
		if (info_player->Get_Char_State() == Player::Char_State::Prepared || 
			info_player->Get_Item_Used_Status() == Player::Item_Use_Status::Bulkup)
		{
			info_player->Set_Item_Used_Status(Player::Item_Use_Status::Bulkup);
			
			if (timer > 0.f)
			{
				if (m_target->GetTransform().GetScale().x <= 5.f)
				{
					m_target->Get_Plus_Dmg() = 2.f;
					m_target->GetTransform().GetScale_Reference().x += dt;
					m_target->GetTransform().GetScale_Reference().y += dt;
				}

				timer -= dt;
			}
			else
			{
				if (m_target->GetTransform().GetScale().x >= 2.f)
				{
					m_target->GetTransform().GetScale_Reference().x -= dt;
					m_target->GetTransform().GetScale_Reference().y -= dt;
				}
				else
				{
					m_target->Get_Plus_Dmg() = 0.f;
					info_player->Set_Char_State(Player::Char_State::None);
					info_player->Change_To_Normal_State();
					info_player->Set_Item_Used_Status(Player::Item_Use_Status::None);
					msg->Set_Should_Delete(true);
				}

			}
		}
		else if (info_player->Get_Char_State() == Player::Char_State::None)
		{
			info_player->Change_To_Normal_State();
			msg->Set_Should_Delete(true);
		}
	}
}
