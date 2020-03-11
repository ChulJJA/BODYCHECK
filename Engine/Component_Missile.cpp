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
		vector2 target_ = target->GetTransform().GetTranslation() - m_owner->GetTransform().GetTranslation();
		vector2 target_dir = normalize(target_);

		pos.x += (target_dir.x * 13);
		pos.y += (target_dir.y * 13);

		vector2 this_pos = m_owner->GetTransform().GetTranslation();
		vector2 obj_pos = target->GetTransform().GetTranslation();
		float value = cross({ target_.x, target_.y, 0.f }, { this_pos.x, this_pos.y, 0.f }).z;

		float angle_in_radian = atan2(this_pos.y - obj_pos.y, this_pos.x - obj_pos.x);
		float angle = to_degrees(angle_in_radian);
		angle += 90;

		m_owner->GetComponentByTemplate<Player>()->SetPlayerVelocity(
			{ sin(angle_in_radian) * -20, cos(angle_in_radian) * 20 }
		);

		m_owner->SetRotation(angle);

		if (value > 0)
		{
			vector3 convert_pos(pos.x, pos.y, 1.f);

			convert_pos = MATRIX3::build_rotation(to_radians(-20)) * convert_pos;

			pos.x = convert_pos.x;
			pos.y = convert_pos.y;
		}
		else if (value < 0)
		{
			vector3 convert_pos(pos.x, pos.y, 1.f);

			convert_pos = MATRIX3::build_rotation(to_radians(20)) * convert_pos;

			pos.x = convert_pos.x;
			pos.y = convert_pos.y;
		}
		m_owner->GetTransform().SetTranslation(pos);
	}
	else
	{
		m_owner->SetDeadCondition(true);
	}
}

void Missile::Set_Target(Object* obj)
{
	if(obj != nullptr)
	{
		target = obj;
		obj->Add_Pointed_By(&target);
	}
}



void Missile::Set_From_Obj(Object* obj)
{
	if(obj != nullptr)
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

