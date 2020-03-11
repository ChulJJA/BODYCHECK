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


void Msg_Func_Item_Time_Pause::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		std::vector<Object*> another_players = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");

		another_players.erase(std::find(another_players.begin(), another_players.end(), obj));

		if (info_player != nullptr && info_ui != nullptr)
		{
			info_player->Set_Item_State(Item::Item_Kind::None);

			if (info_player->Get_Char_State() == Player::Char_State::None)
			{
				//info_player->Set_Char_State(Player::Char_State::Shield);
				//
				for (auto player : another_players)
				{
					Player* get_player = player->GetComponentByTemplate<Player>();
					if (get_player != nullptr)
					{
						get_player->Set_Char_State(Player::Char_State::Time_Pause);
						get_player->Set_Stop_Timer(3.0f);
					}
				}
				//
				//info_player->Set_Shield_Timer(3.f);
				//obj->DeleteComponent(obj->GetComponentByTemplate<Physics>());
			}

			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Time_Pause);
		}
	}
}

void Msg_Func_Item_Time_Pause::Update(float dt)
{

	msg->Set_Should_Delete(true);

}
