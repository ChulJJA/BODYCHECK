/*
 * Author		:Minseok Sung
 * File			:Message_Function_Item_Mine.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message Function Item Mine
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Message_Function_Base.h"
class Message;

class Msg_Func_Item_Mine : public Msg_Func_Base
{
public:
	void Init() override;
	void Update(float dt) override;

	Msg_Func_Item_Mine(Object* m_from_, Object* m_target_, float timer_, Message* msg_)
	{
		m_from = m_from_;
		m_target = m_target_;
		timer = timer_;
		msg = msg_;
	}

	~Msg_Func_Item_Mine()
	{

	}

private:
	float timer;
	Message* msg;
	Object* reverse_moving_effect;
};