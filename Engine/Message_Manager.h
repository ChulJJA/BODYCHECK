/*
 * Author		:Sangmin Kim
 * File			:Message_Manager.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Header file for Message_Manger.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
};