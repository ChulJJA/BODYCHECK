/*
 * Author		:Sangmin Kim
 * File			:Message_Function)Item_Throwing.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message Function Item Throwing
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include "Message_Function_Base.h"
#include "Particle.h"

class Message;

class Msg_Func_Item_Throwing : public Msg_Func_Base
{
public:
	void Init() override;
	void Update(float dt) override;

	Msg_Func_Item_Throwing(Object* m_from_, Object* m_target_, float timer_, Message* msg_)
	{
		m_from = m_from_;
		m_target = m_target_;
		timer = timer_;
		msg = msg_;
	}

	~Msg_Func_Item_Throwing()
	{

	}

private:
	float timer;
	Message* msg;
	Object* throwing;
	ParticleGenerator* particle;
};