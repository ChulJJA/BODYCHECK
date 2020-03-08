#include "Damage_Calculator.h"
#include "Object.h"
#include "Physics.h"

std::pair<float, float> Damaege_Calculation(Object* target, Object* from)
{
	Physics* target_physics = target->GetComponentByTemplate<Physics>();
	Physics* from_physics = from->GetComponentByTemplate<Physics>();

	if (target_physics != nullptr && from_physics != nullptr)
	{
		float target_scale = 1.f;
		target_scale += target->Get_Plus_Dmg();
		float from_scale = 1.f;
		from_scale += from->Get_Plus_Dmg();

		vector2 target_pos = target->GetTransform().GetTranslation();
		vector2 from_pos = from->GetTransform().GetTranslation();

		bool same_direction_x = false;
		bool same_direction_y = false;

		same_direction_x = (target_physics->GetAcceleration().x < 0 && from_physics->GetAcceleration().x < 0);
		same_direction_x |= (target_physics->GetAcceleration().x > 0 && from_physics->GetAcceleration().x > 0);
		same_direction_y = (target_physics->GetAcceleration().y < 0 && from_physics->GetAcceleration().y < 0);
		same_direction_y |= (target_physics->GetAcceleration().y > 0 && from_physics->GetAcceleration().y > 0);


		//both directions are same.
		if (same_direction_x && same_direction_y)
		{
			//if the positive.
			if (target_physics->GetAcceleration().x > 0)
			{
				if (target_pos.x > from_pos.x&& target_pos.y > from_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.first -= target_scale;
					dmg.second = 2;
					dmg.second -= from_scale;
					return dmg;
				}
				if (from_pos.x > target_pos.x&& from_pos.y > target_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
					dmg.second -= from_scale;
					dmg.first = 2;
					dmg.first -= target_scale;
					return dmg;
				}

				float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
					(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
				target_dmg -= target_scale;
				float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
					(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
				from_dmg -= from_scale;
				return std::pair<float, float> {target_dmg, from_dmg};
			}
			if (target_physics->GetAcceleration().x < 0)
			{
				if (target_pos.x < from_pos.x && target_pos.y < from_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.first -= target_scale;
					dmg.second = 2;
					dmg.second -= from_scale;
					return dmg;
				}
				if (from_pos.x < target_pos.x && from_pos.y < target_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
					dmg.first = 2;
					dmg.second -= from_scale;
					dmg.first -= target_scale;
					return dmg;
				}

				float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
					(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
				target_dmg -= target_scale;
				float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
					(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
				from_dmg -= from_scale;

				return std::pair<float, float> {target_dmg, from_dmg};
			}
		}
		else if (same_direction_x)
		{
			if (target_physics->GetAcceleration().x > 0)
			{
				if (target_pos.x > from_pos.x)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.first -= target_scale;
					dmg.second = 2;
					dmg.second -= from_scale;
					return dmg;
				}
				if (from_pos.x > target_pos.x)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;

					dmg.first = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;
					return dmg;
				}
			}
			if (target_physics->GetAcceleration().x < 0)
			{
				std::pair<float, float> dmg;
				dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
					(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y)));
				if (from_pos.x > target_pos.x&& from_pos.y > target_pos.y)
					dmg.first = 0;
				return dmg;
			}
			if (target_pos.x < from_pos.x)
			{
				std::pair<float, float> dmg;
				dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
					(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
				dmg.second = 2;
				dmg.first -= target_scale;
				dmg.second -= from_scale;

				return dmg;
			}
			if (from_pos.x < target_pos.x)
			{
				std::pair<float, float> dmg;
				dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
					(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
				dmg.first = 2;
				dmg.first -= target_scale;
				dmg.second -= from_scale;

				return dmg;
			}

			float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
				(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
			target_dmg -= target_scale;
			float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
				(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
			from_dmg -= from_scale;
			return std::pair<float, float> {target_dmg, from_dmg};
		}
		else if (same_direction_y)
		{
			if (target_physics->GetAcceleration().y > 0)
			{
				if (target_pos.y > from_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.second = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
				if (from_pos.y > target_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
					dmg.first = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
			}
			if (target_physics->GetAcceleration().y < 0)
			{
				if (target_pos.y < from_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.second = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
				if (from_pos.y < target_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
					dmg.first = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
			}
			float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
				(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
			target_dmg -= target_scale;
			float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
				(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
			from_dmg -= from_scale;
			return std::pair<float, float> {target_dmg, from_dmg};
		}
		else
		{
			float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
				(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
			float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
				(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
			target_dmg -= target_scale;
			from_dmg -= from_scale;
			return std::pair<float, float> {target_dmg, from_dmg};
		}

	}
	return {};
}
