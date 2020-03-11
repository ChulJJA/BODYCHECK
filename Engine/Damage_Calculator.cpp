#include "Damage_Calculator.h"
#include "Object.h"
#include "Physics.h"
#include "UsefulTools.hpp"
#include "Component_Player.h"

std::pair<float, float> DamageCalculator(Object* target, Object* from)
{
	vector2 target_velocity = target->GetComponentByTemplate<Player>()->GetPlayerVelocity();
	vector2 from_velocity = from->GetComponentByTemplate<Player>()->GetPlayerVelocity();
	float target_power = (VectorToScalar(target_velocity) * target->GetTransform().GetScale().x);
	float from_power = (VectorToScalar(from_velocity) * from->GetTransform().GetScale().x);
	float total_power = target_power - from_power;
	std::pair<float, float> damage{};
	
	if(total_power >= 0)
	{
		float damage_setting = VectorToScalar(target_velocity - from_velocity);
		damage = { total_power * damage_setting / 50, total_power * damage_setting / 100 };
		return damage;
	}
	else if(total_power < 0)
	{
		float damage_setting = VectorToScalar(from_velocity - target_velocity);
		damage = { -total_power * damage_setting /100, -total_power * damage_setting / 50};
		return damage;
	}
}
