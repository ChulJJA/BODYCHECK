/*
 * Author		:Sangmin Kim
 * File			:Message.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message.h"
#include "Message_Manager.h"
#include "Message_Function.h"
#include "Object.h"

void Message::Init()
{
	func = new Message_Func(this);
}

void Message::Update(float dt)
{
	func->Functioning(dt);

	if (m_from != nullptr && m_target != nullptr)
	{
		std::string log = m_from->Get_Name() + " " + message_name + " " + m_target->Get_Name();

		Message_Manager::Get_Message_Manager()->Get_Log().push_back(log);
	}
}

void Message::Delete()
{
	delete func;
}