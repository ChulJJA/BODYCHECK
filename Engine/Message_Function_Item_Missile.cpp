#include "Component_Item.h"
#include "Player_Ui.h"
#include "Component_Player.h"
#include "Message.h"
#include "Message_Function_Item_Missile.h"
#include "ObjectManager.h"
#include "Referee.h"
#include "Component_Missile.h"

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
			obj->Change_Sprite(obj->Find_Sprite_By_Name("ready"));
			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Missile);
		}
		
	}
}

void Msg_Func_Item_Missile::Update(float dt)
{
	Player* info_player = m_target->GetComponentByTemplate<Player>();

	if(info_player != nullptr)
	{
		if (info_player->Get_Char_State() == Player::Char_State::Prepared)
		{
			std::vector<Object*> another_players = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");
			another_players.erase(std::find(another_players.begin(), another_players.end(), m_target));
			int player_count = another_players.size();

			for (int i = 0; i < player_count; i++)
			{
				int index = Referee::Get_Referee()->Get_Missile_Count();
				Object* missiles = Referee::Get_Referee()->Get_Missile_From_Saving(index);
				missiles->GetTransform().SetTranslation(m_target->GetTransform().GetTranslation());
				missiles->GetComponentByTemplate<Missile>()->Set_Target(another_players[i]);
				missiles->GetComponentByTemplate<Missile>()->Set_From_Obj(m_target);
				ObjectManager::GetObjectManager()->AddObject(missiles);
			}
			
			info_player->Change_To_Normal_State();
			msg->Set_Should_Delete(true);
		}
		else if(info_player->Get_Char_State() == Player::Char_State::None)
		{
			msg->Set_Should_Delete(true);
		}
	}
	
	
}
