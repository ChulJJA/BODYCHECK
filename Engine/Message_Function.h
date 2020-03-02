#pragma once
#include <string>


class Message;
class Object;
class Msg_Func_Base;
class Message_Func
{
public:
	Message_Func(Message* msg);
	void Functioning(float dt);

private:
	void Func_Wall_Collision();

	
	Message* msg_;
	Object* m_from;
	Object* m_target;
	std::string message_name;
	Msg_Func_Base* function = nullptr;
};