#include "Message_Function_Collision.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Engine.hpp"
#include "Object.h"
#include "Player_Ui.h"
#include "Component_Hpbar.h"
#include "Component_Text.h"
#include "Message.h"
#include "Damage_Calculator.h"
#include "Component_Ui.h"
#include "Component_Lock.h"

void Msg_Func_Collision::Init()
{
}



void Msg_Func_Collision::Update(float dt)
{
	if (m_target->Get_Tag() == "item" && m_from->Get_Tag() == "player")
	{
		Player_Get_Item(m_from, m_target);
	}
	else if (m_from->Get_Tag() == "item" && m_target->Get_Tag() == "player")
	{
		Player_Get_Item(m_target, m_from);
	}
	else if (m_target->Get_Tag() == "throwing" && m_from->Get_Tag() == "player")
	{
		physics.PushPlayer(m_from, m_target);
		m_target->SetDeadCondition(true);
	}
	else if (m_from->Get_Tag() == "throwing" && m_target->Get_Tag() == "player")
	{
		physics.PushPlayer(m_target, m_from);
		m_from->SetDeadCondition(true);
	}
	else if (m_from->Get_Tag() == "throwing" && m_target->Get_Tag() == "throwing")
	{
	}
	else if (m_from->Get_Tag() == "lock" && m_target->Get_Tag() == "player")
	{
		Player_And_Lock_Collision(m_target, m_from);
	}
	else if (m_target->Get_Tag() == "lock" && m_from->Get_Tag() == "player")
	{
		Player_And_Lock_Collision(m_from, m_target);
	}
	else if (m_from->Get_Tag() == "player" && m_target->Get_Tag() == "player")
	{
		physics.KnockBack(m_from, m_target);
		Player_And_Player_Collision();
		Player* player_from_info = m_from->GetComponentByTemplate<Player>();
		Player* player_target_info = m_target->GetComponentByTemplate<Player>();

		if (player_from_info->Get_Char_State() == Player::Char_State::Lock_Ing)
		{
			Object* pointer = player_from_info->Get_Locking();

			if (pointer != nullptr)
			{
				pointer->SetDeadCondition(true);
				Object* pointer_target = pointer->GetComponentByTemplate<Lock>()->Get_Locking_Target();
				if (pointer_target != nullptr)
				{
					pointer_target->Change_Sprite(pointer_target->Find_Sprite_By_Name("normal"));
				}

				player_from_info->Change_To_Normal_State();
			}
		}
		else if (player_target_info->Get_Char_State() == Player::Char_State::Lock_Ing)
		{
			Object* pointer = player_target_info->Get_Locking();
			if (pointer != nullptr)
			{
				pointer->SetDeadCondition(true);
				Object* pointer_target = pointer->GetComponentByTemplate<Lock>()->Get_Locking_Target();
				if (pointer_target != nullptr)
				{
					pointer_target->Change_Sprite(pointer_target->Find_Sprite_By_Name("normal"));
				}

				player_target_info->Change_To_Normal_State();
			}
		}

		if (player_from_info->Get_Char_State_Additional() == Player::Char_State_Additional::Chasing)
		{
			if (player_from_info->Get_Locking_Result() == m_target)
			{
				player_from_info->Change_To_Normal_State();
			}
		}
		else if (player_target_info->Get_Char_State_Additional() == Player::Char_State_Additional::Chasing)
		{
			if (player_target_info->Get_Locking_Result() == m_from)
			{
				player_target_info->Change_To_Normal_State();
			}
		}

		if (player_target_info->Get_Char_State() == Player::Char_State::Missile_Ready)
		{
			player_target_info->Change_To_Normal_State();
		}
		else if (player_from_info->Get_Char_State() == Player::Char_State::Missile_Ready)
		{
			player_from_info->Change_To_Normal_State();
		}


		if (player_from_info->Get_Char_State() == Player::Char_State::Time_Pause)
		{
			player_from_info->Change_To_Normal_State();
		}
		else if (player_target_info->Get_Char_State() == Player::Char_State::Time_Pause)
		{
			player_target_info->Change_To_Normal_State();
		}

	}

	msg->Set_Should_Delete(true);
}

void Msg_Func_Collision::Player_Get_Item(Object* player, Object* item)
{
	sound.Play(SOUND::Item);
	item->SetDeadCondition(true);

	Player* player_info = player->GetComponentByTemplate<Player>();
	PLAYER_UI* ui_info = player_info->Get_Ui();

	if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Dash)
	{
		player_info->Set_Item_State(Item::Item_Kind::Dash);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Dash);
	}
	else if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::HP)
	{
		player_info->Set_Item_State(Item::Item_Kind::HP);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Hp);
	}
	else if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Bulkup)
	{
		player_info->Set_Item_State(Item::Item_Kind::Bulkup);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Bulkup);
	}
	else if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Throwing)
	{
		player_info->Set_Item_State(Item::Item_Kind::Throwing);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Throwing);
	}

	else if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Magnatic)
	{
		player_info->Set_Item_State(Item::Item_Kind::Magnatic);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Magnatic);
	}

	else if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Time_Pause)
	{
		player_info->Set_Item_State(Item::Item_Kind::Time_Pause);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Time_Pause);
	}

	else if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Reverse_Moving)
	{
		player_info->Set_Item_State(Item::Item_Kind::Reverse_Moving);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Reverse_Moving);
	}
	
	else if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Missile)
	{
		player_info->Set_Item_State(Item::Item_Kind::Missile);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Missile);
	}
}

void Msg_Func_Collision::Player_And_Player_Collision()
{
	std::pair<float, float> dmg_set = DamageCalculator(m_target, m_from);

	Player* info_player_target = m_target->GetComponentByTemplate<Player>();
	Player* info_player_from = m_from->GetComponentByTemplate<Player>();

	if (info_player_from != nullptr && info_player_target != nullptr)
	{
		info_player_target->Get_Regeneration_Timer() = 0.f;
		info_player_from->Get_Regeneration_Timer() = 0.f;

		TextComp* target_text_comp = m_target->Get_Dmg_Text()->GetComponentByTemplate<TextComp>();
		TextComp* from_text_comp = m_target->Get_Dmg_Text()->GetComponentByTemplate<TextComp>();

		if (from_text_comp != nullptr && target_text_comp != nullptr)
		{
			target_text_comp->GetText().SetString(L"-" + std::to_wstring(static_cast<int>(dmg_set.first)));
			target_text_comp->Get_Timer() = 1.f;
			from_text_comp->GetText().SetString(L"-" + std::to_wstring(static_cast<int>(dmg_set.second)));
			from_text_comp->Get_Timer() = 1.f;

			Object* target_text = m_target->Get_Dmg_Text();
			Object* from_text = m_from->Get_Dmg_Text();
			target_text->GetTransform().GetTranslation_Reference().x = m_target->GetTransform().GetTranslation().x;
			target_text->GetTransform().GetTranslation_Reference().y = m_target->GetTransform().GetTranslation().y;
			from_text->GetTransform().GetTranslation_Reference().x = m_from->GetTransform().GetTranslation().x;
			from_text->GetTransform().GetTranslation_Reference().y = m_from->GetTransform().GetTranslation().y;

			if (m_from->GetComponentByTemplate<Player>() != nullptr)
			{
				m_target->Set_Hitted_By(m_from);
			}

			if (m_target->GetComponentByTemplate<Player>() != nullptr)
			{
				m_from->Set_Hitted_By(m_target);
			}

			Object* target_hp_bar = m_target->Get_Belong_Object_By_Tag("hp_bar");
			Object* from_hp_bar = m_from->Get_Belong_Object_By_Tag("hp_bar");

			if (target_hp_bar != nullptr || from_hp_bar != nullptr)
			{
				Hp_Bar* hp_bar_info_target = target_hp_bar->GetComponentByTemplate<Hp_Bar>();
				Hp_Bar* hp_bar_info_from = from_hp_bar->GetComponentByTemplate<Hp_Bar>();

				if(hp_bar_info_from != nullptr && hp_bar_info_target != nullptr)
				{
					hp_bar_info_target->Decrease(dmg_set.first / 50);
					hp_bar_info_from->Decrease(dmg_set.second / 50);

					if(hp_bar_info_target->Get_Hp_Bard_State() != Hp_Bar::Hp_Bar_State::Recovering && 
						hp_bar_info_from->Get_Hp_Bard_State() != Hp_Bar::Hp_Bar_State::Recovering)
					{
						hp_bar_info_target->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);
						hp_bar_info_from->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);

						hp_bar_info_target->Set_Timer(1.f);
						hp_bar_info_from->Set_Timer(1.f);
						
						m_from->Change_Sprite(m_from->Find_Sprite_By_Name("crying"));
						m_target->Change_Sprite(m_target->Find_Sprite_By_Name("crying"));
					}
				}
				
			}
		}
	}
}

void Msg_Func_Collision::Player_And_Lock_Collision(Object* player, Object* lock)
{
	Lock* info_lock = lock->GetComponentByTemplate<Lock>();

	if (lock->IsDead() == false)
	{
		player->Change_Sprite(player->Find_Sprite_By_Name("lock"));

		if (info_lock->Get_Locking_Target() != nullptr)
		{
			if (info_lock->Get_Locking_Target() != player)
			{
				info_lock->Get_Locking_Target()->Change_Sprite(
					info_lock->Get_Locking_Target()->Find_Sprite_By_Name("normal")
				);
			}
		}
		info_lock->Set_Locking_Target(player);
	}
}
