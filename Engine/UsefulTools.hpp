/*
 * Author		:Chulseung Lee
 * File			:UsefulTools.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for UsefulTools
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "vector2.hpp"

class Object;

bool MouseCollision(vector2 object_pos_max, vector2 object_pos_min, vector2 mouse_pos);
void ObjectHover(Object* current_obj, Object* next_obj);
std::wstring StringToWstring(std::string str);
float RadianToDegree(float radian);
float DegreeToRadian(float degree);//
float VectorToScalar(vector2 vector);
int RandomNumberGenerator(int min_value, int max_value);
float DistanceBetween(vector2 position_a, vector2 position_b);