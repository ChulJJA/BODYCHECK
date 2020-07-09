/*
 * Author		:Sangmin Kim
 * File			:Message_Manager.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Message.h"
#include <vector>
#include <string>

class Message_Manager
{
private:
    Message_Manager() {}
    static Message_Manager* msg_manager;
    std::vector<Message*> messages;
    std::vector<std::string> msg_log;
    std::vector<Message*> delete_msg;

public:
    static Message_Manager* Get_Message_Manager();
    void Save_Message(Message* msg);
    void Init();
    void Update(float dt);
    void Delete();
    std::vector<std::string>& Get_Log()
    {
        return msg_log;
    }
    std::vector<Message*>& Get_Messages()
    {
        return messages;
    }
};