/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Item_Missile.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Item Missile
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Item.h"
#include "Player_Ui.h"
#include "Component_Player.h"
#include "Message.h"
#include "Message_Function_Item_Missile.h"
#include "ObjectManager.h"
#include "Referee.h"
#include "Component_Missile.h"
#include "Component_Sprite.h"
#include "Sound_Manager.h"
#include "Engine.hpp"

void Msg_Func_Item_Missile::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		if(info_player != nullptr && info_ui != nullptr && obj != nullptr)
		{
			obj->GetMesh().Get_Is_Moved() = true;
			
			info_player->Set_Item_State(Item::Item_Kind::None);
			info_player->Set_Char_State(Player::Char_State::Prepare);
			info_player->Set_Prepare_Timer(3.f);
			sound.Play(SOUND::MissilePrepare);
			obj->Change_Sprite(obj->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Missile));
			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Missile);
		}		
	}
}

void Msg_Func_Item_Missile::Update(float dt)
{
	Player* info_player = m_target->GetComponentByTemplate<Player>();

	if(info_player != nullptr)
	{
		if (info_player->Get_Char_State() == Player::Char_State::Prepared)
		{
			std::vector<Object*> another_players = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");
			another_players.erase(std::find(another_players.begin(), another_players.end(), m_target));
			int player_count = another_players.size();
			sound.Play(SOUND::MissileShoot);

			for (int i = 0; i < player_count; i++)
			{
				const int index = Referee::Get_Referee()->Get_Missile_Count();
				Object* missiles = Referee::Get_Referee()->Get_Missile_From_Saving(index);
				missiles->GetTransform().SetTranslation(m_target->GetTransform().GetTranslation());
				missiles->GetComponentByTemplate<Missile>()->Set_Target(another_players[i]);
				missiles->GetComponentByTemplate<Missile>()->Set_From_Obj(m_target);
				
				ObjectManager::GetObjectManager()->AddObject(missiles);
			}
			
			info_player->Change_To_Normal_State();
			msg->Set_Should_Delete(true);
		}
		else if(info_player->Get_Char_State() == Player::Char_State::None)
		{
			info_player->Change_To_Normal_State();
			msg->Set_Should_Delete(true);
		}
	}
	
	
}
