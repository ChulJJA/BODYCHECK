/*
 * Author		:Sangmin Kim
 * File			:Component_Player.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Basic component for player, which initialize the hpbar object and
 *				 attach to the owner object.
 *				 UI Objects are attached in here too.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Player.h"
#include "Message_Manager.h"
#include "ObjectManager.h"
#include "Input.h"
#include "Component_Enemy.h"
#include "Component_Sprite.h"
#include "Component_Hpbar.h"
#include <GLFW/glfw3.h>
#include "Component_Throwing.h"
#include "Player_Ui.h"
#include "Component_Ui.h"
#include "Physics.h"


void Player::Init(Object* obj)
{
	m_owner = obj;
	m_owner->Get_Component_Info_Reference().component_info_player = true;

	Object* hp_bar = new Object();
	vector2 hp_bar_pos = m_owner->GetTransform().GetTranslation();
	hp_bar_pos.y -= 100;
	hp_bar->SetTranslation(hp_bar_pos);
	hp_bar->SetScale({1.f, 2.5f});
	hp_bar->AddComponent(new Sprite(hp_bar, "../Sprite/HP.png", hp_bar_pos, false));
	hp_bar->AddComponent(new Hp_Bar());
	hp_bar->Set_Name(m_owner->Get_Name() + "hp_bar");
	hp_bar->Set_Tag("hp_bar");
	hp_bar->Set_This_Obj_Owner(m_owner);
	this->hp_bar = hp_bar;
	m_owner->Get_Belongs_Objects().push_back(hp_bar);
	ObjectManager::GetObjectManager()->AddObject(hp_bar);
}

void Player::Update(float dt)
{
	//Attack();

	if (curr_state == Char_State::Bulk_Up)
	{
		if (bulkup_timer > 0.f)
		{
			bulkup_timer -= dt;

			if (m_owner->GetTransform().GetScale().x <= 5.f)
			{
				m_owner->Get_Plus_Dmg() = 2.f;
				m_owner->GetTransform().GetScale_Reference().x += dt;
				m_owner->GetTransform().GetScale_Reference().y += dt;
			}
		}
		else
		{
			if (m_owner->GetTransform().GetScale().x >= 3.f)
			{
				m_owner->GetTransform().GetScale_Reference().x -= dt;
				m_owner->GetTransform().GetScale_Reference().y -= dt;
			}
			else
			{
				m_owner->Get_Plus_Dmg() = 0.f;
				curr_state = Char_State::None;
			}
		}
	}
	if (curr_state == Char_State::Throwing)
	{
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE))
		{
			curr_state = Char_State::None;

			Object* throwing = new Object();
			throwing->Set_Name("throwing");
			throwing->Set_Tag("throwing");
			throwing->AddComponent(new Sprite(throwing, "../sprite/pen_green.png", m_owner->GetTransform().GetTranslation()));
			throwing->AddComponent(new Physics());
			throwing->AddComponent(new Throwing);
			throwing->GetComponentByTemplate<Throwing>()->Set_Timer(3.f);
			throwing->GetComponentByTemplate<Throwing>()->Set_Angle(m_owner->GetTransform().GetRotation());
			throwing->GetComponentByTemplate<Throwing>()->Set_Throwing_Obj(m_owner);
			throwing->SetScale(2.f);
			ObjectManager::GetObjectManager()->AddObject(throwing);
		}
	}
	if(hp_bar != nullptr)
	{
		hp_bar->GetTransform().GetTranslation_Reference().x = m_owner->GetTransform().GetTranslation().x;
		hp_bar->GetTransform().GetTranslation_Reference().y = m_owner->GetTransform().GetTranslation().y - 100;
	}
}

void Player::Attack()
{
}

Item::Item_Kind Player::Get_Item_State()
{
	return belong_item;
}
//
//void Player::Change_Ui_Info(Ui::Ui_Status_Base base, Ui::Ui_Status_Verb verb, Ui::Ui_Status_Obj obj)
//{
//	if(base == Ui::Ui_Status_Base::Item)
//	{
//		//Object* setting_ui = this_ui->Get_Item_Info();
//		Ui* ui_info = this_ui->GetComponentByTemplate<Ui>();
//
//		ui_info->Set_Status_Base(base);
//		ui_info->Set_Status_Verb(verb);
//		ui_info->Set_Status_Obj(obj);		
//		this_ui->GetMesh().Get_Is_Moved() = true;
//	}
//}

void Player::Set_This_UI_info(PLAYER_UI* ui)
{
	this_ui = ui;
}

void Player::Set_Item_State(Item::Item_Kind state)
{
	this->belong_item = state;
}

PLAYER_UI* Player::Get_Ui()
{
	return this_ui;
}