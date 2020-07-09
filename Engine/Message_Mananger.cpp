/*
 * Author		:Sangmin Kim
 * File			:Message_Manager.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Manager.h"
#include "Message_Function.h"

Message_Manager* Message_Manager::msg_manager = nullptr;

Message_Manager* Message_Manager::Get_Message_Manager()
{
	if (msg_manager == nullptr)
		msg_manager = new Message_Manager();

	return msg_manager;
}
void Message_Manager::Save_Message(Message* msg)
{
	messages.push_back(msg);
}

void Message_Manager::Init()
{
}
void Message_Manager::Update(float dt)
{
	if (!messages.empty())
	{
		delete_msg.clear();

		for (int i = 0; i < messages.size(); i++)
		{
			messages[i]->Update(dt);

			if (messages[i]->Get_Should_Delete())
			{
				delete_msg.push_back(messages[i]);
			}
		}
		if (!delete_msg.empty())
		{
			for (auto& delete_msg : this->delete_msg)
			{
				delete_msg->Delete();
				messages.erase(std::find(messages.begin(), messages.end(), delete_msg));
			}
		}
	}
}
void Message_Manager::Delete()
{
}