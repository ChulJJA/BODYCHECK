#include "Message_Function_Item_Throwing.h"

#include "Message.h"
#include "Object.h"
#include "Component_Player.h"
#include "Player_Ui.h"

void Msg_Func_Item_Throwing::Init()
{
	if(msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();

		if(info_player != nullptr)
		{
			PLAYER_UI* info_ui = info_player->Get_Ui();

			info_player->Set_Item_State(Item::Item_Kind::None);
			info_player->Set_Char_State(Player::Char_State::Throwing);

			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Throwing);
		}
	}
}

void Msg_Func_Item_Throwing::Update(float dt)
{
	msg->Set_Should_Delete(true);
}
