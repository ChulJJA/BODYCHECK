/*
 * Author		:Sangmin Kim
 * File			:Message.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <string>
#include <functional>
#include "Message_Kind.h"

class Message_Func;
class Object;

class Message
{
private:
	std::string message_name;
	Object* m_target = nullptr;
	Object* m_from = nullptr;
	bool should_delete = false;
	float timer = 1.f;
	Message_Func* func;
	Object* dash_effect = nullptr;
	Message_Kind kind = Message_Kind::None;

public:
	Message(Object* target, Object* from, std::string message_name_) :
		m_target(target), m_from(from), message_name(message_name_)
	{
		this->Init();
	}

	Message(Object* target, Object* from, std::string message_name_, float timer) :
		m_target(target), m_from(from), message_name(message_name_), timer(timer)
	{
		this->Init();
	}

	Message(Object* target, Object* from, Message_Kind kind, float timer = 1.f) :
		m_target(target), m_from(from), kind(kind), timer(timer)
	{
		this->Init();
	}

	bool Get_Should_Delete()
	{
		return should_delete;
	}
	std::pair<float, float> Damaege_Calculation(Object target, Object from);

	Object* Get_Target()
	{
		return m_target;
	}
	Object* Get_From()
	{
		return m_from;
	}
	Message_Kind Get_Kind()
	{
		return kind;
	}
	std::string Get_Message_Name()
	{
		return message_name;
	}
	void Set_Should_Delete(bool toggle)
	{
		should_delete = toggle;
	}

	float Get_Timer()
	{
		return timer;
	}

	Message_Func* Get_Func()
	{
		return func;
	}
	
    void Init();
    void Update(float dt);
    void Delete();

};