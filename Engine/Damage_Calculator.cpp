#include "Damage_Calculator.h"
#include "Object.h"
#include "UsefulTools.hpp"
#include "Component_Player.h"

std::pair<float, float> DamageCalculator(Object* target, Object* from)
{
	const vector2 target_velocity = target->GetComponentByTemplate<Player>()->GetPlayerVelocity();
	const vector2 from_velocity = from->GetComponentByTemplate<Player>()->GetPlayerVelocity();
	const float target_power = (VectorToScalar(target_velocity) * target->GetTransform().GetScale().x);
	const float from_power = (VectorToScalar(from_velocity) * from->GetTransform().GetScale().x);
	const float total_power = target_power - from_power;
	std::pair<float, float> damage{};
	
	if(total_power >= 0)
	{
		const float damage_setting = VectorToScalar(target_velocity - from_velocity);
		damage = { total_power * damage_setting / 50, total_power * damage_setting / 100 };
		std::cout << "first: " << damage.first << std::endl;
		std::cout << "second: " << damage.second << std::endl;
		return damage;
	}
	else if(total_power < 0)
	{
		const float damage_setting = VectorToScalar(from_velocity - target_velocity);
		damage = { -total_power * damage_setting /100, -total_power * damage_setting / 50};
		std::cout << "first: " << damage.first << std::endl;
		std::cout << "second: " << damage.second << std::endl;
		return damage;
	}

	return damage;
}