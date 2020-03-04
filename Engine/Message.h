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
#include <functional>
#include "thread"
#include <mutex>


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
	std::mutex guard;

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
	std::string Get_Message_Name()
	{
		return message_name;
	}
	void Set_Should_Delete(bool toggle)
	{
		should_delete = toggle;
	}

	Message_Func* Get_Func()
	{
		return func;
	}
	
    void Init();
    void Update(float dt);
    void Delete();

};