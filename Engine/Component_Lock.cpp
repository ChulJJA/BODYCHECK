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
	if(throwing_obj != nullptr)
	{
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE))
		{
			if (timer > 0.f)
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

				m_owner->GetTransform().SetTranslation(pos);
				timer -= dt;
			}
			else
			{
				if (locking_target != nullptr)
				{
					locking_target->Add_Pointed_By(&locking_target);
					Component* change_sprite_to = locking_target->Find_Component_By_Name("normal");
					Component* lock_sprite = locking_target->Find_Component_By_Name("lock");

					lock_sprite->Set_Need_Update(false);
					change_sprite_to->Set_Need_Update(true);

					throwing_obj->GetComponentByTemplate<Player>()->Set_Char_State(Player::Char_State::Magnatic);
				}
				else
				{
					throwing_obj->GetComponentByTemplate<Player>()->Set_Char_State(Player::Char_State::None);
				}

				throwing_obj->GetComponentByTemplate<Player>()->Set_Locking(nullptr);
				m_owner->SetDeadCondition(true);
			}
		}
		else
		{
			if (locking_target != nullptr)
			{
				locking_target->Add_Pointed_By(&locking_target);

				Component* change_sprite_to = locking_target->Find_Component_By_Name("normal");
				Component* lock_sprite = locking_target->Find_Component_By_Name("lock");

				lock_sprite->Set_Need_Update(false);
				change_sprite_to->Set_Need_Update(true);

				throwing_obj->GetComponentByTemplate<Player>()->Set_Char_State(Player::Char_State::Magnatic);
			}
			else
			{
				throwing_obj->GetComponentByTemplate<Player>()->Set_Char_State(Player::Char_State::None);
			}

			throwing_obj->GetComponentByTemplate<Player>()->Set_Locking(nullptr);
			m_owner->SetDeadCondition(true);
		}
	}
	else
	{
		m_owner->SetDeadCondition(true);
	}
}

void Lock::Set_State(Status status)
{
	state = status;
}

Lock::Status Lock::Get_State()
{
	return state;
}

void Lock::Set_Timer(float timer_)
{
	timer = timer_;
}

void Lock::Set_Speed(float speed_)
{
	speed = speed_;
}

void Lock::Set_Throwing_Obj(Object* obj)
{
	throwing_obj = obj;
	obj->Add_Pointed_By(&throwing_obj);
}

Object* Lock::Get_Throwing_Obj()
{
	return throwing_obj;
}

Object* Lock::Get_Locking_Target()
{
	return locking_target;
}

void Lock::Set_Locking_Target(Object* obj)
{
	locking_target = obj;
}
