#include "Message_Function_Dead.h"
#include "Object.h"
#include "Message.h"
#include "Component_Sprite.h"
#include "Component_Player.h"

void Msg_Func_Dead::Init()
{
	if(m_target != nullptr)
	{
		m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Die));
		m_target->GetComponentByTemplate<Player>()->Change_Weapon_Sprite(nullptr);
		m_target->SetNeedCollision(false);
		//m_target->Delete_All_Components_But_Sprite();
	}
}

void Msg_Func_Dead::Update(float dt)
{
	if(m_target != nullptr)
	{
		if(timer > 0.f)
		{
			timer -= dt;
		}
		else
		{
			//m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
			m_target->SetDeadCondition(true);
			msg->Set_Should_Delete(true);
		}
	}
}
