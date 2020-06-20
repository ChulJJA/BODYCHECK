#include "Message.h"
#include "vector2.hpp"
#include "Physics.h"
#include "Object.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Player_Ui.h"
#include "Message_Function_Item_Reverse_Moving.h"
#include "ObjectManager.h"
#include "Component_Sprite.h"
#include "time.h"
#include "Engine.hpp"


void Msg_Func_Item_Reverse_Moving::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		srand(time(NULL));

		FMOD_BOOL isBGM;
		FMOD_BOOL isBGMReverse;
		FMOD_Channel_IsPlaying(sound.channel[1], &isBGM);
		FMOD_Channel_IsPlaying(sound.channel[26], &isBGMReverse);
		if (isBGM)
		{
			sound.Stop(SOUND::BGM2);
			sound.Play(SOUND::BGM2Reverse);

		}
		std::vector<Object*> another_players = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");

		int random_select_character;

		if (another_players.size() > 1)
		{
			random_select_character = rand() % (another_players.size());
		}
		else
		{
			random_select_character = 0;
		}
		
		another_players.erase(std::find(another_players.begin(), another_players.end(), obj));

		if (info_player != nullptr && info_ui != nullptr)
		{
			info_player->Set_Item_State(Item::Item_Kind::None);

			if (info_player->Get_Char_State() == Player::Char_State::None)
			{
				//Player* get_player = another_players[random_select_character]->GetComponentByTemplate<Player>();
				//another_players.GetComponentByTemplate();
				for (auto player : another_players)
				{
					Player* get_player = player->GetComponentByTemplate<Player>();
					get_player->Set_Char_State(Player::Char_State::Reverse_Moving);
					player->Change_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Reverse_Moving));
					//another_players[random_select_character]->Change_Sprite(another_players[random_select_character]->Find_Sprite_By_Type(Sprite_Type::Player_Reverse_Moving));
				}
				

				
			}
			info_player->Change_To_Normal_State();

			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Reverse_Moving);
		}
	}
}

void Msg_Func_Item_Reverse_Moving::Update(float dt)
{

	msg->Set_Should_Delete(true);

}
