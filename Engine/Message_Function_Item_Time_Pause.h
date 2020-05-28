#pragma once
#include "Message_Function_Base.h"
#include <fmod.h>
class Message;

class Msg_Func_Item_Time_Pause : public Msg_Func_Base
{
public:
	void Init() override;
	void Update(float dt) override;

	Msg_Func_Item_Time_Pause(Object* m_from_, Object* m_target_, float timer_, Message* msg_)
	{
		m_from = m_from_;
		m_target = m_target_;
		timer = timer_;
		msg = msg_;
	}

	~Msg_Func_Item_Time_Pause()
	{

	}

private:
	float timer;
	Message* msg;
	FMOD_BOOL isBgm;
};