/*
 * Author		:Sangmin Kim
 * File			:Component_Throwing.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Component Throwing
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Throwing.h"
#include "Object.h"
#include "angles.hpp"
#include "Physics.h"


void Throwing::Init(Object* obj)
{
	m_owner = obj;
	pos = m_owner->GetTransform().GetTranslation();
}

void Throwing::Update(float dt)
{
	if(timer > 0.f)
	{
		timer -= dt;
		
		pos.x -= (sin(angle_in_radian) * 50);
		pos.y += (cos(angle_in_radian) * 50);

		m_owner->GetTransform().SetTranslation(pos);
	}
	else
	{
		m_owner->SetDeadCondition(true);
	}
}

void Throwing::Set_Timer(float timer_)
{
	timer = timer_;
}

void Throwing::Set_Angle(float angle)
{
	this->angle = angle;
	angle_in_radian = to_radians(angle);
	m_owner->GetComponentByTemplate<Physics>()->SetVelocity(
	{
		sin(angle_in_radian) * -30, cos(angle_in_radian) * 30
	});
	m_owner->SetRotation(angle);
}

void Throwing::Set_Throwing_Obj(Object* obj)
{
	if(obj != nullptr)
	{
		throwing_obj = obj;
		obj->Add_Pointed_By(&throwing_obj);
	}
}

Object* Throwing::Get_Throwing_Obj() const
{
	return throwing_obj;
}
