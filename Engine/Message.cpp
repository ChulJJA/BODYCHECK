/*
 * Author		:Sangmin Kim
 * File			:Message.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for implementing message system's message part.
 *				 Checking the vector which contains messages, depends on the message type,
 *				 implementing proper function.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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