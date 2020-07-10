/*
 * Author		:Chulseung Lee
 * File			:Damage_Calculator.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Damage Calculator
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <utility>
class Object;

std::pair<float, float> DamageCalculator(Object* target, Object* from);