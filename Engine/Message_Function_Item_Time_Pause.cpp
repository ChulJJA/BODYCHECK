/*
 * Author		:Minseok Sung
 * File			:Message_Function_Item_Time_Pause.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Item Time Pause
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Item_Time_Pause.h"
#include "Message.h"
#include "vector2.hpp"
#include "Physics.h"
#include "Object.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Player_Ui.h"
#include "Message_Function_Item_Time_Pause.h"
#include "ObjectManager.h"
#include "Component_Sprite.h"
#include "Engine.hpp"


void Msg_Func_Item_Time_Pause::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		info_player->Set_Prepare_Timer(1.f);
		info_player->Set_Char_State(Player::Char_State::Prepare);
		info_player->Set_Item_State(Item::Item_Kind::None);
		obj->Change_Sprite(obj->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Timestop));
		sound.Play(SOUND::ClockTicking);

		info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Time_Pause);

	}
}

void Msg_Func_Item_Time_Pause::Update(float dt)
{
	if (m_target != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();

		if (info_player->Get_Char_State() == Player::Char_State::Prepared)
		{
			std::vector<Object*> another_players = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");

			another_players.erase(std::find(another_players.begin(), another_players.end(), obj));

			if (info_player != nullptr)
			{
				info_player->Change_To_Normal_State();

				for (auto player : another_players)
				{
					if (player->Get_Current_Sprite() != player->Find_Sprite_By_Type(Sprite_Type::Player_Spawn))
					{
						FMOD_BOOL isBGMPlaying;
						FMOD_BOOL isMatchBGMPlaying;
						FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &isBGMPlaying);
						FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::MatchBGM)], &isMatchBGMPlaying);

						if (isBGMPlaying)
						{
							sound.Stop(SOUND::BGM2);
						}
						if (isMatchBGMPlaying)
						{
							sound.Stop(SOUND::MatchBGM);
						}

						Player* get_player = player->GetComponentByTemplate<Player>();
						get_player->Change_To_Normal_State();
						if (get_player != nullptr)
						{
							player->Change_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Paused));
							get_player->Set_Char_State(Player::Char_State::Time_Pause);
							get_player->Set_Stop_Timer(4.0f);
						}
					}
				}

			}
			msg->Set_Should_Delete(true);
		}
		else if (info_player->Get_Char_State() == Player::Char_State::None)
		{
			info_player->Change_To_Normal_State();
			FMOD_BOOL isBGMPlaying;
			FMOD_BOOL isClocking;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(sound.currentBGM)], &isBGMPlaying);
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::ClockTicking)], &isClocking);
			if(!isBGMPlaying)
			{
				sound.Play(sound.currentBGM);
			}
			if(isClocking)
			{
				sound.Stop(SOUND::ClockTicking);
			}
			msg->Set_Should_Delete(true);
		}
	}
}
