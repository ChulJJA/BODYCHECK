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
		sound.Play(SOUND::FingerSnap);
		sound.Play(SOUND::ClockTicking);
		FMOD_Channel_IsPlaying(sound.channel[1], &isBgm);
		if(isBgm)
		{
			sound.Stop(SOUND::BGM2);
		}
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
			msg->Set_Should_Delete(true);
		}
		else if (info_player->Get_Char_State() == Player::Char_State::None)
		{
			info_player->Change_To_Normal_State();

			msg->Set_Should_Delete(true);
		}
	}


}
