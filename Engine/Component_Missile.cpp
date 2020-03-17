#include "Component_Missile.h"
#include "Component_Player.h"
#include "angles.hpp"
#include "Physics.h"

void Missile::Init(Object* obj)
{
	m_owner = obj;
	physics = m_owner->GetComponentByTemplate<Physics>();
}

void Missile::Update(float dt)
{
	vector2& pos = m_owner->GetTransform().GetTranslation_Reference();
	
	if (target != nullptr)
	{
		obj_pos = target->GetTransform().GetTranslation();
		vector2 target_dir = obj_pos - pos;
		
		const vector2 target_dir_normalized = normalize(target_dir);
		pos.x += (target_dir_normalized.x * 13);
		pos.y += (target_dir_normalized.y * 13);

		Rotating_Toward_Target(pos);
		Homing(target_dir, pos);
	}
	else
	{
		m_owner->SetDeadCondition(true);
	}
}

void Missile::Set_Target(Object* obj)
{
	if (obj != nullptr)
	{
		target = obj;
		obj->Add_Pointed_By(&target);
	}
}

void Missile::Set_From_Obj(Object* obj)
{
	if (obj != nullptr)
	{
		from = obj;
		obj->Add_Pointed_By(&from);
	}
}

Object* Missile::Get_Target() const
{
	return target;
}

Object* Missile::Get_From_Obj() const
{
	return from;
}

void Missile::Rotating_Toward_Target(vector2& pos)
{
	angle_in_radian = atan2(pos.y - obj_pos.y, pos.x - obj_pos.x);
	angle = to_degrees(angle_in_radian);
	angle += 90;
	m_owner->SetRotation(angle);

	physics->SetVelocity(
		{ sin(angle_in_radian) * -20, cos(angle_in_radian) * 20 }
	);
}

void Missile::Homing(vector2& target_, vector2& pos) const
{
	float value = cross({ target_.x, target_.y, 0.f }, { pos.x, pos.y, 0.f }).z;
	
	if (value > 0)
	{
		vector3 convert_pos(pos.x, pos.y, 1.f);

		convert_pos = minus_rotation * convert_pos;

		pos.x = convert_pos.x;
		pos.y = convert_pos.y;
	}
	else if (value < 0)
	{
		vector3 convert_pos(pos.x, pos.y, 1.f);

		convert_pos = plus_rotation * convert_pos;

		pos.x = convert_pos.x;
		pos.y = convert_pos.y;
	}
}

