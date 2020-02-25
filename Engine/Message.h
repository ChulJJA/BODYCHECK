/*
 * Author		:Sangmin Kim
 * File			:Message.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Header file for Message.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <string>
#include "Object.h"
#include <functional>

class Message
{
private:
    std::string message_name;
    Object* m_target = nullptr;
    Object* m_from = nullptr;
    bool should_delete = false;
    float timer = 1.f;

    Object* dash_effect = nullptr;

public:
    Message(Object* target, Object* from, std::string message_name_) :
        m_target(target), m_from(from), message_name(message_name_) {}

    Message(Object* target, Object* from, std::string message_name_, float timer) :
        m_target(target), m_from(from), message_name(message_name_), timer(timer)
    {
    }

    bool Get_Should_Delete()
    {
        return should_delete;
    }
    std::pair<float, float> Damaege_Calculation(Object target, Object from);
    void Init();
    void Update(float dt);
    void Delete();
};