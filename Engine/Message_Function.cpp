#include "Message_Function.h"
#include "Message.h"
#include "Component_Text.h"
#include "Message_Function_Wall_Collision.h"
#include "Message_Function_Collision.h"
#include "Message_Function_Respawn.h"
#include "Message_Function_Item_Bulkup.h"
#include "Message_Function_Item_Recover.h"
#include "Message_Function_Item_Dash.h"
#include "Message_Function_Item_Throwing.h"
#include "Message_Function_Item_Magnatic.h"
#include "Message_Function_Item_Time_Pause.h"
#include "Message_Function_Item_Reverse_Moving.h"
#include "Message_Function_Missile.h"
std::mutex guard;

Message_Func::Message_Func(Message* msg)
{
	//
	msg_ = msg;
	m_from = msg->Get_From();
	m_target = msg->Get_Target();
	message_name = msg->Get_Message_Name();
	function = nullptr;
}

void Message_Func::Functioning(float dt)
{
	if(function == nullptr)
	{
		if (message_name == "wall_collision")
		{
			function = new Msg_Func_Wall_Collision(m_from, m_target, msg_);
		}
		else if (message_name == "collision")
		{
			function = new Msg_Func_Collision(m_from, m_target, msg_);
		}
		else if (message_name == "respawn")
		{
			function = new Msg_Func_Respawn(m_from, m_target, msg_);
		}
		else if (message_name == "bulkup")
		{
			function = new Msg_Func_Item_Bulkup(m_from, m_target, 5.f, msg_);
		}
		else if (message_name == "recover")
		{
			function = new Msg_Func_Item_Recover(m_from, m_target, 3.f, msg_);
		}
		else if(message_name == "dash")
		{
			function = new Msg_Func_Item_Dash(m_from, m_target, 0.5f, msg_);
		}
		else if(message_name == "throwing")
		{
			function = new Msg_Func_Item_Throwing(m_from, m_target, 1.f, msg_);
		}
		else if (message_name == "magnatic")
		{
			function = new Msg_Func_Item_Magnatic(m_from, m_target, 1.f, msg_);
		}
		else if (message_name == "time_pause")
		{
			function = new Msg_Func_Item_Time_Pause(m_from, m_target, 1.f, msg_);
		}
		else if (message_name == "reverse_moving")
		{
			function = new Msg_Func_Item_Reverse_Moving(m_from, m_target, 1.f, msg_);
		}
		else if (message_name == "missile")
		{
			function = new Msg_Func_Item_Missile(m_from, m_target, 1.f, msg_);
		}

		function->Init();
	}
	
	function->Update(dt);
	
	if (msg_->Get_Should_Delete() == true)
	{
		delete function;
	}
}