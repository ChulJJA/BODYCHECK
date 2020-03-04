#include "Component_Throwing.h"
#include "Object.h"
#include "angles.hpp"
#include <iostream>

void Throwing::Init(Object* obj)
{
	m_owner = obj;
	owner_pos = m_owner->GetTransform().GetTranslation();
}

void Throwing::Update(float dt)
{
	
	if(timer > 0.f)
	{
		timer -= dt;
		
		//Remain : Set formula which enables the object moving toward position or vector
		//with constant speed.
		
	}
	
}

void Throwing::Set_Target_Dir(vector2 dir)
{
	target_dir = dir;

	dir_vec_length = sqrt(target_dir.x * target_dir.x + target_dir.y * target_dir.y);

	dx = target_dir.x / dir_vec_length;
	dy = target_dir.y / dir_vec_length;

	angle = atan2(m_owner->GetTransform().GetTranslation().y - target_pos.y,
		m_owner->GetTransform().GetTranslation().x - target_pos.x);

	angle = to_degrees(angle);
	std::cout << "angle : " << angle << std::endl;
	
}

void Throwing::Set_Timer(float timer_)
{
	timer = timer_;
}

void Throwing::Set_Target_Pos(vector2 pos)
{
	target_pos = pos;
}
