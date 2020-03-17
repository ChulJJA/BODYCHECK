#include "Component_Lock.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include "Component_Player.h"

void Lock::Init(Object* obj)
{
	m_owner = obj;
	pos = obj->GetTransform().GetTranslation();
}

void Lock::Update(float dt)
{
	if (locking_obj != nullptr)
	{
		Control_Input(dt);
		m_owner->GetTransform().SetTranslation(pos);

		if (input.Is_Key_Triggered(GLFW_KEY_SPACE))
		{
			if (locking_target != nullptr)
			{
				locking_target->Add_Pointed_By(&locking_target);
				Func_Set_Magnatic();
			}
			else
			{
				locking_obj->Change_Sprite(locking_obj->Find_Sprite_By_Name("normal"));
				info_player_locking_obj->Set_Char_State(Player::Char_State::None);
			}
			info_player_locking_obj->Set_Locking(nullptr);
			m_owner->SetDeadCondition(true);
		}
	}
	else
	{
		m_owner->SetDeadCondition(true);
	}
}


void Lock::Set_Timer(float timer_)
{
	timer = timer_;
}

void Lock::Set_Speed(float speed_)
{
	speed = speed_;
}

void Lock::Set_Locking_Obj(Object* obj)
{
	if (obj != nullptr)
	{
		locking_obj = obj;
		info_player_locking_obj = locking_obj->GetComponentByTemplate<Player>();
		obj->Add_Pointed_By(&locking_obj);
	}
}

Object* Lock::Get_Locking_Obj() const
{
	return locking_obj;
}

Object* Lock::Get_Locking_Target()
{
	return locking_target;
}

void Lock::Set_Locking_Target(Object* obj)
{
	if (obj != nullptr)
	{
		locking_target = obj;
		obj->Add_Pointed_By(&locking_target);
	}
}

void Lock::Control_Input(float dt)
{
	if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
	{
		pos.x += (dt * speed);
	}
	if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
	{
		pos.x -= (dt * speed);
	}
	if (input.Is_Key_Pressed(GLFW_KEY_UP))
	{
		pos.y += (dt * speed);
	}
	if (input.Is_Key_Pressed(GLFW_KEY_DOWN))
	{
		pos.y -= (dt * speed);
	}
}

void Lock::Func_Set_Magnatic() const
{
	locking_target->Change_Sprite(locking_target->Find_Sprite_By_Name("normal"));
	
	info_player_locking_obj->Set_Char_State(Player::Char_State::Magnatic);
	info_player_locking_obj->Set_Locking_Result(locking_target);
	locking_obj->Change_Sprite(locking_obj->Find_Sprite_By_Name("chase"));
}
