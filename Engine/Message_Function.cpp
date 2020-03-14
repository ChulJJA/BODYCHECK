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
#include "Message_Function_Item_Missile.h"

Message_Func::Message_Func(Message* msg)
{
	//
	msg_ = msg;
	m_from = msg->Get_From();
	m_target = msg->Get_Target();
	message_name = msg->Get_Message_Name();
	kind = msg->Get_Kind();
	function = nullptr;
}

void Message_Func::Functioning(float dt)
{
	if(function == nullptr)
	{
		if (kind == Message_Kind::Collision_Wall)
		{
			function = new Msg_Func_Wall_Collision(m_from, m_target, msg_);
		}
		else if (kind == Message_Kind::Collision)
		{
			function = new Msg_Func_Collision(m_from, m_target, msg_);
		}
		else if (kind == Message_Kind::Respawn)
		{
			function = new Msg_Func_Respawn(m_from, m_target, msg_);
		}
		else if (kind == Message_Kind::Item_Bulkup)
		{
			function = new Msg_Func_Item_Bulkup(m_from, m_target, 5.f, msg_);
		}
		else if (kind == Message_Kind::Item_Recover)
		{
			function = new Msg_Func_Item_Recover(m_from, m_target, 3.f, msg_);
		}
		else if(kind == Message_Kind::Item_Dash)
		{
			function = new Msg_Func_Item_Dash(m_from, m_target, 0.5f, msg_);
		}
		else if(kind == Message_Kind::Item_Throwing)
		{
			function = new Msg_Func_Item_Throwing(m_from, m_target, 1.f, msg_);
		}
		else if (kind == Message_Kind::Item_Magnetic)
		{
			function = new Msg_Func_Item_Magnatic(m_from, m_target, 1.f, msg_);
		}
		else if (kind == Message_Kind::Item_Timepause)
		{
			function = new Msg_Func_Item_Time_Pause(m_from, m_target, 1.f, msg_);
		}
		else if (kind == Message_Kind::Item_Reverse)
		{
			function = new Msg_Func_Item_Reverse_Moving(m_from, m_target, 1.f, msg_);
		}
		else if (kind == Message_Kind::Item_Missile)
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