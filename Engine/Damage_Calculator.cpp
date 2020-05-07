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

	if(target_power > from_power)
	{
		const float damage_setting = VectorToScalar(from_velocity - target_velocity);
		return {(from_power * damage_setting) / 200, (target_power * damage_setting) / 100};
	}
	const float damage_setting = VectorToScalar(target_velocity - from_velocity);
	return { (from_power * damage_setting) / 100, (target_power * damage_setting) / 200 };
}