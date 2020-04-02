#include "Message_Function_Audience.h"
#include "Message.h"
#include "Object.h"
#include "Component_Sprite.h"

void Msg_Func_Audience::Init()
{
	if(m_target != nullptr)
	{
		if(msg->Get_Kind() == Message_Kind::Audience_Blue_Joy)
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Blue_Good));
		}
		else if (msg->Get_Kind() == Message_Kind::Audience_Red_Joy)
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Red_Good));
		}
		else if (msg->Get_Kind() == Message_Kind::Audience_Normal_Joy)
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Normal_Good));
		}
		else if (msg->Get_Kind() == Message_Kind::Audience_Green_Joy)
		{
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Green_Good));
		}
	}
}

void Msg_Func_Audience::Update(float dt)
{
	if(timer > 0.f)
	{
		timer -= dt;
	}
	else
	{
		m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Audience_Normal));
		msg->Set_Should_Delete(true);
	}
	
}
