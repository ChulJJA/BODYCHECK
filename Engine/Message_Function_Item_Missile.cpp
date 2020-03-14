#include "Component_Item.h"
#include "Player_Ui.h"
#include "Component_Player.h"
#include "Message.h"
#include "Message_Function_Item_Missile.h"

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

			info_player->Sprite_After_Preparation(obj->Find_Sprite_By_Name("chase"));
			info_player->State_After_Preparation(Player::Char_State::Missile_Shoot);
			
			obj->Change_Sprite(obj->Find_Sprite_By_Name("ready"));
			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Missile);
		}
		
	}
}

void Msg_Func_Item_Missile::Update(float dt)
{
	msg->Set_Should_Delete(true);
}
