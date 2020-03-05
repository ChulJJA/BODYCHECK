#include "Message_Function_Item_Bulkup.h"
#include "Component_Player.h"
#include "Object.h"
#include "Message.h"
#include "Component_Ui.h"
#include "Player_Ui.h"

void Msg_Func_Item_Bulkup::Init()
{
	if(msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		if(info_player != nullptr && info_ui != nullptr)
		{
			info_player->Set_Item_State(Item::Item_Kind::None);

			if(info_player->Get_Char_State() == Player::Char_State::None)
			{
				info_player->Set_Char_State(Player::Char_State::Bulk_Up);
				info_player->Set_Bulkup_Timer(5.f);
			}

			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Bulkup);
		}
	}
}

void Msg_Func_Item_Bulkup::Update(float dt)
{
	msg->Set_Should_Delete(true);
}
