/*
 * Author		:Chulseung Lee
 * File			:UsefulTools.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Useful Tools
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Text.h"
#include "Object.h"
#include "UsefulTools.hpp"
#include "angles.hpp"
#include "random"

bool MouseCollision(vector2 object_pos_max, vector2 object_pos_min, vector2 mouse_pos)
{
	if (mouse_pos.x < object_pos_max.x && mouse_pos.x > object_pos_min.x
		&& mouse_pos.y < object_pos_max.y && mouse_pos.y > object_pos_min.y)
	{
		return true;
	}
	else
	{
		return false;//
	}

}

void ObjectHover(Object* current_obj, Object* next_obj)
{
    current_obj->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
    next_obj->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,1 };
}

std::wstring StringToWstring(std::string str)
{
    std::wstring str_to_wstr;
    str_to_wstr.assign(str.begin(), str.end());
    return str_to_wstr;
}

float RadianToDegree(float radian)
{
    float degree = static_cast<float>(radian * (180 / PI));

    return degree;
}

float DegreeToRadian(float degree)
{
    float radian = static_cast<float>(degree * (PI / 180));

    return radian;
}

float VectorToScalar(vector2 vector)
{
    float result = sqrt((vector.x * vector.x) + (vector.y * vector.y));

    return result;
}

int RandomNumberGenerator(int min_value, int max_value)
{
	const int generated_number = rand() % (max_value - min_value + 1) + min_value;

    return generated_number;
}

float DistanceBetween(vector2 position_a, vector2 position_b)
{
    float distance = sqrt((position_a.x - position_b.x) * (position_a.x - position_b.x) + (position_a.y - position_b.y) * (position_a.y - position_b.y));

    return distance;
}
