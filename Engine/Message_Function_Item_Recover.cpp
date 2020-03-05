#include "Message_Function_Item_Recover.h"
#include "Component_Hpbar.h"
#include "Object.h"
#include "Message.h"
#include "Component_Player.h"
#include "Player_Ui.h"

void Msg_Func_Item_Recover::Init()
{
	if(msg->Get_From() != nullptr && msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_From();
		Object* hp_bar = msg->Get_Target();

		if(obj != nullptr && hp_bar != nullptr)
		{
			Player* info_player = obj->GetComponentByTemplate<Player>();
			PLAYER_UI* info_ui = info_player->Get_Ui();
			Hp_Bar* info_hp_bar = hp_bar->GetComponentByTemplate<Hp_Bar>();

			if(info_player != nullptr && info_hp_bar != nullptr)
			{
				info_player->Set_Item_State(Item::Item_Kind::None);

				hp_bar->GetTransform().GetTranslation_Reference().x = 0.f;
				info_hp_bar->Get_Set_Offset() = 0;

				hp_bar->GetMesh().Get_Is_Moved() = true;
				info_hp_bar->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Recovering);
				info_hp_bar->Set_Timer(3.f);

				info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Hp);
			}
		}
	}
}

void Msg_Func_Item_Recover::Update(float dt)
{
	msg->Set_Should_Delete(true);
}
