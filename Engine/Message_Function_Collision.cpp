#include "Message_Function_Collision.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Engine.hpp"
#include "Object.h"
#include "Player_Ui.h"
#include "Component_Hpbar.h"
#include "Component_Text.h"
#include "Message.h"
#include "Physics.h"
#include "Component_Ui.h"

std::pair<float, float> Damaege_Calculation(Object target, Object from);

void Msg_Func_Collision::Init()
{
}

std::pair<float, float> Damaege_Calculation(Object target, Object from)
{
	Physics* target_physics = target.GetComponentByTemplate<Physics>();
	Physics* from_physics = from.GetComponentByTemplate<Physics>();


	return std::pair<float, float>(1.f, 1.f);
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

	player->Set_Is_It_Collided(false);
}

void Msg_Func_Collision::Player_And_Player_Collision()
{
	std::pair<float, float> dmg_set{ 1.f, 1.f };

	m_target->GetComponentByTemplate<Player>()->Get_Regeneration_Timer() = 0.f;
	m_from->GetComponentByTemplate<Player>()->Get_Regeneration_Timer() = 0.f;

	m_target->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->GetText().SetString(L"-" + std::to_wstring(static_cast<int>(dmg_set.first)));
	m_target->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->Get_Timer() = 1.f;
	m_from->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->GetText().SetString(L"-" + std::to_wstring(static_cast<int>(dmg_set.second)));
	m_from->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->Get_Timer() = 1.f;

	m_target->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().x = m_target->GetTransform().GetTranslation().x;
	m_target->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().y = m_target->GetTransform().GetTranslation().y;

	m_from->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().x = m_from->GetTransform().GetTranslation().x;
	m_from->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().y = m_from->GetTransform().GetTranslation().y;

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
