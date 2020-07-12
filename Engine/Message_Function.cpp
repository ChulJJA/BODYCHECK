/*
 * Author		:Sangmin Kim
 * File			:Message_Function.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

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
#include "Message_Function_Audience.h"
#include "Message_Function_Dead.h"
#include "Message_Function_Item_Mine.h"
#include "Message_Function_Delete_Object.h"
#include "Message_Function_Spawn.h"
#include "Message_Function_ParticleCollision.h"

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
		else if(kind == Message_Kind::Audience_Blue_Joy || kind == Message_Kind::Audience_Red_Joy || 
			kind == Message_Kind::Audience_Normal_Joy || kind == Message_Kind::Audience_Green_Joy)
		{
			function = new Msg_Func_Audience(m_from, m_target, 3.f, msg_);
		}
		else if (kind == Message_Kind::Die)
		{
			function = new Msg_Func_Dead(m_from, m_target, 3.f, msg_);
		}
		else if (kind == Message_Kind::Item_Mine)
		{
			function = new Msg_Func_Item_Mine(m_from, m_target, 1.f, msg_);
		}
		else if(kind == Message_Kind::Delete_Object)
		{
			function = new Msg_Func_Delete_Object(m_from, m_target, msg_->Get_Timer(), msg_);
		}
		else if (kind == Message_Kind::Spawn_Object)
		{
			function = new Msg_Func_spawn(m_from, m_target, msg_->Get_Timer(), msg_);
		}
		else if (kind == Message_Kind::Particle_Collision)
		{
			function = new Msg_Func_ParticleCollision(m_from, m_target, msg_->Get_Timer(), msg_);
		}

		function->Init();
	}
	function->Update(dt);

	if (msg_->Get_Should_Delete() == true)
	{
		delete function;
	}
}