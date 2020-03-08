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
		m_target->SetDeadCondition(true);
		m_from->Set_Is_It_Collided(false);
	}
	else if (m_from->Get_Tag() == "throwing" && m_target->Get_Tag() == "player")
	{
		m_from->SetDeadCondition(true);
		m_target->Set_Is_It_Collided(false);
	}
	else if (m_from->Get_Tag() == "throwing" && m_target->Get_Tag() == "throwing")
	{
		m_from->Set_Is_It_Collided(false);
		m_target->Set_Is_It_Collided(false);
	}
	else if (m_from->Get_Tag() == "lock" && m_target->Get_Tag() == "player")
	{
		if (m_from->IsDead() == false)
		{
			m_target->Change_Sprite(m_target->Find_Component_By_Name("lock"));

			if(m_from->GetComponentByTemplate<Lock>()->Get_Locking_Target() != nullptr)
			{
				if(m_from->GetComponentByTemplate<Lock>()->Get_Locking_Target() != m_target)
				{
					m_from->GetComponentByTemplate<Lock>()->Get_Locking_Target()->Change_Sprite(
						m_from->GetComponentByTemplate<Lock>()->Get_Locking_Target()->Find_Component_By_Name("normal")
					);
				}
			}
			
			m_from->GetComponentByTemplate<Lock>()->Set_Locking_Target(m_target);
		}
		m_from->Set_Is_It_Collided(false);
		m_target->Set_Is_It_Collided(false);
	}
	else if (m_target->Get_Tag() == "lock" && m_from->Get_Tag() == "player")
	{
		if (m_target->IsDead() == false)
		{
			m_from->Change_Sprite(m_from->Find_Component_By_Name("lock"));

			if (m_target->GetComponentByTemplate<Lock>()->Get_Locking_Target() != nullptr)
			{
				if (m_target->GetComponentByTemplate<Lock>()->Get_Locking_Target() != m_from)
				{
					m_target->GetComponentByTemplate<Lock>()->Get_Locking_Target()->Change_Sprite(
						m_target->GetComponentByTemplate<Lock>()->Get_Locking_Target()->Find_Component_By_Name("normal")
					);
				}
			}
			
			m_target->GetComponentByTemplate<Lock>()->Set_Locking_Target(m_from);
		}
		
		m_from->Set_Is_It_Collided(false);
		m_target->Set_Is_It_Collided(false);
	}
	else if (m_from->Get_Tag() == "player" && m_target->Get_Tag() == "player")
	{
		Player_And_Player_Collision();
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
	if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::HP)
	{
		player_info->Set_Item_State(Item::Item_Kind::HP);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Hp);
	}
	if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Bulkup)
	{
		player_info->Set_Item_State(Item::Item_Kind::Bulkup);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Bulkup);
	}
	if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Throwing)
	{
		player_info->Set_Item_State(Item::Item_Kind::Throwing);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Hp);
	}

	if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Magnatic)
	{
		player_info->Set_Item_State(Item::Item_Kind::Magnatic);
		ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Magnatic);
	}

	player->Set_Is_It_Collided(false);
}

void Msg_Func_Collision::Player_And_Player_Collision()
{
	std::pair<float, float> dmg_set = Damaege_Calculation(m_target, m_from);

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
				//target_hp_bar->GetComponentByTemplate<Hp_Bar>()->Decrease(dmg_set.first / 50);
				//from_hp_bar->GetComponentByTemplate<Hp_Bar>()->Decrease(dmg_set.second / 50);

				target_hp_bar->GetComponentByTemplate<Hp_Bar>()->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);
				from_hp_bar->GetComponentByTemplate<Hp_Bar>()->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);
			}

			m_from->Set_Is_It_Collided(false);
			m_target->Set_Is_It_Collided(false);
		}
	}
}
