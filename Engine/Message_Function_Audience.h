#pragma once

#include "Message_Function_Base.h"
#include "vector2.hpp"

class Message;

class Msg_Func_Audience : public Msg_Func_Base
{
public:
	void Init() override;
	void Update(float dt) override;

	Msg_Func_Audience(Object* m_from_, Object* m_target_, float timer_, Message* msg_)
	{
		m_from = m_from_;
		m_target = m_target_;
		timer = timer_;
		msg = msg_;
	}

	~Msg_Func_Audience()
	{

	}

private:
	float timer;
	Message* msg;
	Object* kill_tag;
	bool tag_reach = false;

	float tag_turning_pos;
	float tag_turn_to;
	vector2 tag_origin_pos;

	float speed = 1500.f;
	float back_speed = 1000.f;

	bool is_left = true;
	
};