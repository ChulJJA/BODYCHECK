/*
 * Author		:Sangmin Kim
 * File			:angles.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for angles
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
constexpr float PI = 3.1415926535897932384626433832795f;
constexpr float HALF_PI = PI / 2.0f;
constexpr float QUARTER_PI = PI / 4.0f;
constexpr float TWO_PI = 2.0f * PI;

constexpr float to_radians(float angle_in_degrees) { return angle_in_degrees * PI / 180.0f; }
constexpr float to_degrees(float angle_in_radians) { return angle_in_radians * 180.0f / PI; }