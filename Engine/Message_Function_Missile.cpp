#include "Message_Function_Missile.h"
#include "Component_Item.h"
#include "Player_Ui.h"
#include "Component_Player.h"
#include "Message.h"

void Msg_Func_Item_Missile::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		obj->GetMesh().Get_Is_Moved() = true;
		info_player->Set_Item_State(Item::Item_Kind::None);
		info_player->Set_Char_State(Player::Char_State::Missile_Ready);
		info_player->Set_Missile_Timer(5.f);
		info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Missile);
	}
}

void Msg_Func_Item_Missile::Update(float dt)
{
	msg->Set_Should_Delete(true);
}
