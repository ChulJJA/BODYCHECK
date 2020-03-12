#include "Message.h"
#include "Object.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Player_Ui.h"
#include "Message_Function_Item_Reverse_Moving.h"
#include "ObjectManager.h"
#include "time.h"


void Msg_Func_Item_Reverse_Moving::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		srand(time(NULL));

		int random_select_character = rand() % 3;

		std::vector<Object*> another_players = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");

		another_players.erase(std::find(another_players.begin(), another_players.end(), obj));

		if (info_player != nullptr && info_ui != nullptr)
		{
			info_player->Set_Item_State(Item::Item_Kind::None);

			if (info_player->Get_Char_State() == Player::Char_State::None)
			{
				if(random_select_character > another_players.size())
				{
					random_select_character = 0;
				}
				Player* get_player = another_players[random_select_character]->GetComponentByTemplate<Player>();
				get_player->Set_Char_State(Player::Char_State::Reverse_Moving);

				another_players[random_select_character]->Change_Sprite(another_players[random_select_character]->Find_Sprite_By_Name("reverse_moving_pen"));
			}

			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Reverse_Moving);
		}
	}
}

void Msg_Func_Item_Reverse_Moving::Update(float dt)
{

	msg->Set_Should_Delete(true);

}
