/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Delete_Object.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Delete Object
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

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
