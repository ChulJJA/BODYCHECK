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
#include "Component_Lock.h"
#include "angles.hpp"

void Player::Init(Object* obj)
{
	m_owner = obj;
	m_owner->Get_Component_Info_Reference().component_info_player = true;
	SetHPBar();
}

void Player::Update(float dt)
{
	if (curr_state == Char_State::Bulk_Up)
	{
		Func_Bulk_Up(dt);
	}
	if (curr_state == Char_State::Throwing)
	{
		Func_Bulk_Throwing(dt);
	}
	if(curr_state == Char_State::Lock_Ready)
	{
		Func_Lock_Ready(dt);
	}
	if(curr_state == Char_State::Lock_Ing)
	{
		/*vector2 this_pos = m_owner->GetTransform().GetTranslation();
		vector2 obj_pos = locking_pointer->GetTransform().GetTranslation();
		
		float angle_in_radian = atan2(this_pos.y - obj_pos.y, this_pos.x - obj_pos.x);
		float angle = to_degrees(angle_in_radian);
		angle += 90;

		m_owner->SetRotation(angle);*/
	}
	if(curr_state == Char_State::Magnatic)
	{
		Func_Magnatic(dt);
	}
	if(hp_bar != nullptr)
	{
		hp_bar->GetTransform().GetTranslation_Reference().x = m_owner->GetTransform().GetTranslation().x;
		hp_bar->GetTransform().GetTranslation_Reference().y = m_owner->GetTransform().GetTranslation().y - 100;
	}
	
	PlayerMovement(0.6f, 0.12f);
	m_owner->GetTransform().AddTranslation(velocity);
}

void Player::SetHPBar()
{
	Object* hp_bar = new Object();
	vector2 hp_bar_pos = m_owner->GetTransform().GetTranslation();
	hp_bar_pos.y -= 100;
	hp_bar->SetTranslation(hp_bar_pos);
	hp_bar->SetScale({ 1.f, 2.5f });
	hp_bar->AddComponent(new Sprite(hp_bar, "../Sprite/HP.png", hp_bar_pos, false), "sprite_hp_bar", need_update_hp_bar);
	hp_bar->AddComponent(new Hp_Bar());
	hp_bar->Set_Name(m_owner->Get_Name() + "hp_bar");
	hp_bar->Set_Tag("hp_bar");
	hp_bar->Set_This_Obj_Owner(m_owner);
	this->hp_bar = hp_bar;
	m_owner->Get_Belongs_Objects().push_back(hp_bar);

	if (m_owner->Get_Tag() != "save")
	{
		ObjectManager::GetObjectManager()->AddObject(hp_bar);
	}
}

Item::Item_Kind Player::Get_Item_State()
{
	return belong_item;
}

void Player::PlayerMovement(float max_velocity, float min_velocity)
{
	if (input.Is_Key_Pressed(GLFW_KEY_W))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_W) && input.Is_Key_Pressed(GLFW_KEY_A))
		{
			if (velocity.x >= 0 && velocity.y >= 0)
			{
				velocity += {-max_velocity, min_velocity};
			}
			else if (velocity.x >= 0 && velocity.y < 0)
			{
				velocity += {-max_velocity, max_velocity};
			}
			else if (velocity.x < 0 && velocity.y >= 0)
			{
				velocity += {-min_velocity, min_velocity};
			}
			else if(velocity.x < 0 && velocity.y < 0)
			{
				velocity += {-min_velocity, max_velocity};
			}
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_W) && input.Is_Key_Pressed(GLFW_KEY_D))
		{
			if (velocity.x >= 0 && velocity.y >= 0)
			{
				velocity += {min_velocity, min_velocity};
			}
			else if (velocity.x >= 0 && velocity.y < 0)
			{
				velocity += {min_velocity, max_velocity};
			}
			else if (velocity.x < 0 && velocity.y >= 0)
			{
				velocity += {max_velocity, min_velocity};
			}
			else if (velocity.x < 0 && velocity.y < 0)
			{
				velocity += {max_velocity, max_velocity};
			}
		}
		else
		{
			if (abs(velocity.x) >= 0)
			{
				velocity.x -= velocity.x / 100;
			}
			if (velocity.y >= 0)
			{
				velocity += {0.00, min_velocity};
			}
			else if (velocity.y < 0)
			{
				velocity += {0.00, max_velocity};
			}
		}
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_A))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_A) && input.Is_Key_Pressed(GLFW_KEY_S))
		{
			if (velocity.x >= 0 && velocity.y >= 0)
			{
				velocity += {-max_velocity, -max_velocity};
			}
			else if (velocity.x >= 0 && velocity.y < 0)
			{
				velocity += {-max_velocity, -min_velocity};
			}
			else if (velocity.x < 0 && velocity.y >= 0)
			{
				velocity += {-min_velocity, -max_velocity};
			}
			else if (velocity.x < 0 && velocity.y < 0)
			{
				velocity += {-min_velocity, -min_velocity};
			}
		}
		else
		{
			if (velocity.x >= 0)
			{
				velocity.x += -max_velocity;
			}
			else
			{
				velocity.x += -min_velocity;
			}
			if (abs(velocity.y) >= 0)
			{
				velocity.y -= velocity.y / 100;
			}
		}
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_S))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_S) && input.Is_Key_Pressed(GLFW_KEY_D))
		{
			if (velocity.x >= 0 && velocity.y >= 0)
			{
				velocity += {min_velocity, -max_velocity};
			}
			else if (velocity.x >= 0 && velocity.y < 0)
			{
				velocity += {min_velocity, -min_velocity};
			}
			else if (velocity.x < 0 && velocity.y >= 0)
			{
				velocity += {max_velocity, -max_velocity};
			}
			else if (velocity.x < 0 && velocity.y < 0)
			{
				velocity += {max_velocity, -min_velocity};
			}
		}
		else
		{
			if (abs(velocity.x) >= 0)
			{
				velocity.x -= velocity.x / 100;
			}
			if (velocity.y >= 0)
			{
				velocity.y += -max_velocity;
			}
			else
			{
				velocity.y += -min_velocity;
			}
		}
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_D))
	{
		if (velocity.x >= 0)
		{
			velocity.x += min_velocity;
		}
		else
		{
			velocity.x += max_velocity;
		}
		if (abs(velocity.y) >= 0)
		{
			velocity.y -= velocity.y / 100;
		}
	}
	else
	{
		velocity += {-velocity.x / 100, -velocity.y / 100};
	}
}

void Player::SetPlayerVelocity(vector2 current_velocity)
{
	velocity = current_velocity;
}

vector2 Player::GetPlayerVelocity()
{
	return velocity;
}

void Player::Set_Locking_By(Object* obj)
{
	if(obj != nullptr)
	{
		locking_by = obj;
		obj->Add_Pointed_By(&locking_by);
	}
	
}

void Player::Set_Locking_Result(Object* obj)
{
	if(obj != nullptr)
	{
		locking_result = obj;
		obj->Add_Pointed_By(&locking_result);
	}
	
}

Object* Player::Get_Locking_Result()
{
	return locking_result;
}

void Player::Func_Bulk_Up(float dt)
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

void Player::Func_Bulk_Throwing(float dt)
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

void Player::Func_Lock_Ready(float dt)
{
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE))
	{
		curr_state = Char_State::Lock_Ing;

		Object* lock = new Object();
		lock->Set_Name("lock");
		lock->Set_Tag("lock");
		lock->AddComponent(new Sprite(lock, "../sprite/zoom.png", m_owner->GetTransform().GetTranslation()));
		lock->AddComponent(new Physics());
		lock->AddComponent(new Lock());
		lock->GetComponentByTemplate<Lock>()->Set_Speed(1000.f);
		lock->GetComponentByTemplate<Lock>()->Set_Locking_Obj(m_owner);
		lock->SetScale(2.f);
		locking_pointer = lock;
		ObjectManager::GetObjectManager()->AddObject(lock);

		m_owner->Change_Sprite(m_owner->Find_Sprite_By_Name("thinking"));
	}
}

void Player::Func_Magnatic(float dt)
{
	if (locking_result != nullptr)
	{
		curr_state_additional = Char_State_Additional::Chasing;

		vector2 target = locking_result->GetTransform().GetTranslation() - m_owner->GetTransform().GetTranslation();

		vector2 target_dir = normalize(target);
		vector2 own_pos = m_owner->GetTransform().GetTranslation();

		own_pos.x += (target_dir.x * 13);
		own_pos.y += (target_dir.y * 13);

		vector2 this_pos = m_owner->GetTransform().GetTranslation();
		vector2 obj_pos = locking_result->GetTransform().GetTranslation();
		float value = cross({ target.x, target.y, 0.f }, { this_pos.x, this_pos.y, 0.f }).z;

		float angle_in_radian = atan2(this_pos.y - obj_pos.y, this_pos.x - obj_pos.x);
		float angle = to_degrees(angle_in_radian);
		angle += 90;
		mag_angle = angle;

		m_owner->GetComponentByTemplate<Player>()->SetPlayerVelocity(
			{ sin(angle_in_radian) * -20, cos(angle_in_radian) * 20 }
		);

		m_owner->SetRotation(angle);

		if (value > 0)
		{
			vector3 convert_pos(own_pos.x, own_pos.y, 1.f);

			convert_pos = MATRIX3::build_rotation(to_radians(10)) * convert_pos;

			own_pos.x = convert_pos.x;
			own_pos.y = convert_pos.y;
		}
		else if (value < 0)
		{
			vector3 convert_pos(own_pos.x, own_pos.y, 1.f);

			convert_pos = MATRIX3::build_rotation(to_radians(-10)) * convert_pos;

			own_pos.x = convert_pos.x;
			own_pos.y = convert_pos.y;
		}
		m_owner->GetTransform().SetTranslation(own_pos);
	}
	else
	{
		curr_state = Char_State::None;
		m_owner->Change_Sprite(m_owner->Find_Sprite_By_Name("normal"));
	}
}

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