/*
 * Author		:Minseok Sung
 * File			:Message_Function_Item_Mine.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Item Mine
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message.h"
#include "vector2.hpp"
#include "Physics.h"
#include "Object.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Player_Ui.h"
#include "Message_Function_Item_Mine.h"
#include "ObjectManager.h"
#include "Component_Sprite.h"
#include "time.h"
#include "Engine.hpp"


void Msg_Func_Item_Mine::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		sound.Play(SOUND::Mine);
		if (info_player != nullptr)
		{
			PLAYER_UI* info_ui = info_player->Get_Ui();

			info_player->Set_Item_State(Item::Item_Kind::None);
			info_player->Set_Char_State(Player::Char_State::Mine);
			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Mine);
		}
	}
}

void Msg_Func_Item_Mine::Update(float dt)
{

	msg->Set_Should_Delete(true);

}
