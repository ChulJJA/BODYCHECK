/*
 * Author		:Sangmin Kim
 * File			:Message_Function.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message Function
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <string>
#include "Message_Kind.h"

class Message;
class Object;
class Msg_Func_Base;
class Message_Func
{
public:
	Message_Func(Message* msg);
	void Functioning(float dt);

private:
	Message* msg_;
	Object* m_from;
	Object* m_target;
	std::string message_name;
	Msg_Func_Base* function;
	Message_Kind kind;
};