/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Bulkup.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message Function Bulk Up
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include "Message_Function_Base.h"
class Message;

class Msg_Func_Item_Bulkup : public Msg_Func_Base
{
public:
	void Init() override;
	void Update(float dt) override;

	Msg_Func_Item_Bulkup(Object* m_from_, Object* m_target_, float timer_, Message* msg_)
	{
		m_from = m_from_;
		m_target = m_target_;
		timer = timer_;
		msg = msg_;
	}

	~Msg_Func_Item_Bulkup()
	{

	}

private:
	float timer;
	Message* msg;
	float bulkup_ready_timer = 1.f;
	float bulkup_ready_offset = 0.1f;
	bool is_ready_end = false;
	bool ready_big_mode = true;
	float big_rate = 2.5f;

	bool is_end = false;
	float bulkup_end_timer = 2.f;
	float bulkup_end_offset = 0.1f;
	bool end_big_mode = true;

	bool isPlayed = false;
};