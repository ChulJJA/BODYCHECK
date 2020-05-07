#include "Message_Function_Delete_Object.h"
#include "Object.h"
#include "Message.h"

void Msg_Func_Delete_Object::Init()
{
	m_target->SetNeedCollision(false);
}

void Msg_Func_Delete_Object::Update(float dt)
{
	if(timer > 0.f)
	{
		timer -= dt;
	}
	else
	{
		m_target->SetDeadCondition(true);
		msg->Set_Should_Delete(true);
	}
}
