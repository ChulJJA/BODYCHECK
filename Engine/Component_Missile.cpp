#include "Component_Missile.h"
#include "Component_Player.h"
#include "angles.hpp"

void Missile::Init(Object* obj)
{
	m_owner = obj;
	pos = m_owner->GetTransform().GetTranslation();
}

void Missile::Update(float dt)
{
	if (target != nullptr)
	{
		pos = m_owner->GetTransform().GetTranslation();

		this_pos = m_owner->GetTransform().GetTranslation();
		obj_pos = target->GetTransform().GetTranslation();
		vector2 target_ = obj_pos - pos;
		vector2 target_dir = normalize(target_);

		pos.x += (target_dir.x * 13);
		pos.y += (target_dir.y * 13);

		Rotating_Toward_Target();
		Homing_Missile_Func(target_);

		m_owner->GetTransform().SetTranslation(pos);
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

Object* Missile::Get_Target()
{
	return target;
}

Object* Missile::Get_From_Obj()
{
	return from;
}

void Missile::Rotating_Toward_Target()
{
	angle_in_radian = atan2(this_pos.y - obj_pos.y, this_pos.x - obj_pos.x);
	angle = to_degrees(angle_in_radian);
	angle += 90;
	m_owner->SetRotation(angle);

	m_owner->GetComponentByTemplate<Player>()->SetPlayerVelocity(
		{ sin(angle_in_radian) * -20, cos(angle_in_radian) * 20 }
	);
}

void Missile::Homing_Missile_Func(vector2& target_)
{
	float value = cross({ target_.x, target_.y, 0.f }, { this_pos.x, this_pos.y, 0.f }).z;
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

