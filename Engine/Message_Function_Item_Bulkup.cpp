#include "Message_Function_Item_Bulkup.h"
#include "Component_Player.h"
#include "Object.h"
#include "Message.h"
#include "Component_Ui.h"
#include "Player_Ui.h"

void Msg_Func_Item_Bulkup::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		if (info_player != nullptr && info_ui != nullptr)
		{
			info_player->Set_Item_State(Item::Item_Kind::None);

			if (info_player->Get_Char_State() == Player::Char_State::None)
			{
				//time for prepare
				info_player->Set_Prepare_Timer(3.f);
				info_player->Set_Char_State(Player::Char_State::Prepare);

				//bulkup item setting.
				info_player->Set_Bulkup_Timer(5.f);
				info_player->Sprite_After_Preparation(obj->Find_Sprite_By_Name("chase"));

				obj->Change_Sprite(obj->Find_Sprite_By_Name("effect_bulkup"));
			}

			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Bulkup);
		}
	}
}

void Msg_Func_Item_Bulkup::Update(float dt)
{
	Player* info_player = m_target->GetComponentByTemplate<Player>();

	if (info_player != nullptr)
	{
		if (info_player->Get_Char_State() == Player::Char_State::Prepared)
		{
			if (timer > 0.f)
			{
				if (m_target->GetTransform().GetScale().x <= 5.f)
				{
					m_target->Get_Plus_Dmg() = 2.f;
					m_target->GetTransform().GetScale_Reference().x += dt;
					m_target->GetTransform().GetScale_Reference().y += dt;
				}

				timer -= dt;
			}
			else
			{
				if (m_target->GetTransform().GetScale().x >= 3.f)
				{
					m_target->GetTransform().GetScale_Reference().x -= dt;
					m_target->GetTransform().GetScale_Reference().y -= dt;
				}
				else
				{
					m_target->Get_Plus_Dmg() = 0.f;
					info_player->Set_Char_State(Player::Char_State::None);
					info_player->Change_To_Normal_State();
					msg->Set_Should_Delete(true);
				}

			}
		}
		else if (info_player->Get_Char_State() == Player::Char_State::None)
		{
			info_player->Change_To_Normal_State();
			msg->Set_Should_Delete(true);
		}
	}
}
