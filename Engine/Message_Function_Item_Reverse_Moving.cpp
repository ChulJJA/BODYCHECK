/*
 * Author		:Minseok Sung
 * File			:Message_Function_Item_Reverse_Moving.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Item Reverse Moving
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

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
#include "Component_Missile.h"

void Msg_Func_Item_Reverse_Moving::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		srand(time(NULL));

		sound.Play(SOUND::DemonLaugh);

		info_player->Set_Item_State(Item::Item_Kind::None);
		info_player->Set_Char_State(Player::Char_State::Prepare);
		info_player->Set_Prepare_Timer(1.f);
		obj->Change_Sprite(obj->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Reverse));
		info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Reverse_Moving);
	}
}

void Msg_Func_Item_Reverse_Moving::Update(float dt)
{
	Object* obj = msg->Get_Target();
	Player* info_player = obj->GetComponentByTemplate<Player>();

	if (info_player != nullptr)
	{

		if (info_player->Get_Char_State() == Player::Char_State::Prepared)
		{
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

			if (info_player != nullptr)
			{
				info_player->Set_Item_State(Item::Item_Kind::None);

				info_player->Change_To_Normal_State();
				if (info_player->Get_Char_State() == Player::Char_State::None)
				{
					for (auto player : another_players)
					{
						Player* get_player = player->GetComponentByTemplate<Player>();
						get_player->Set_Stop_Timer(3.f);

						Object* missile = new Object();;
						missile->Set_Name("plask");
						missile->Set_Tag("throwing");
						missile->SetNeedCollision(true);
						missile->AddComponent(new Sprite(missile, "../sprite/Item/plask.png", true, 2, 4, { 0.f,0.f },
							{ 200.f,200.f }, { 255,255,255,255 }), "plask");
						missile->AddComponent(new Physics);
						missile->AddComponent(new Missile);
						missile->Set_Current_Sprite(missile->Find_Sprite_By_Name("plask"));
						missile->SetScale(1.f);
						missile->GetTransform().SetTranslation(m_target->GetTransform().GetTranslation());
						missile->GetComponentByTemplate<Missile>()->Set_Target(player);
						missile->GetComponentByTemplate<Missile>()->Set_From_Obj(m_target);

						ObjectManager::GetObjectManager()->AddObject(missile);
					}
				}
				info_player->Change_To_Normal_State();

				msg->Set_Should_Delete(true);
			}
		}
	}

}
