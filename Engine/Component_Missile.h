/*
 * Author		:Sangmin Kim
 * File			:Component_Missile.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Component Missile
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Component.hpp"
#include "vector2.hpp"
#include "angles.hpp"
#include "Particle.h"

class Physics;

class Missile : public Component
{
public:
	Missile() : timer(0.f), angle(0.f), angle_in_radian(90.f)
	{

	}

	void Init(Object* obj) override;
	void Update(float dt) override;
	void Set_Target(Object* obj);
	void Set_From_Obj(Object* obj);
	Object* Get_Target() const;
	Object* Get_From_Obj() const;

	void Rotating_Toward_Target(vector2& pos);
	void Homing(vector2& target_, vector2& pos) const;
private:
	float timer;
	float angle;
	float angle_in_radian;

	Object* target;
	Object* from;
	
	matrix3 minus_rotation = MATRIX3::build_rotation(to_radians(-20));
	matrix3 plus_rotation = MATRIX3::build_rotation(to_radians(20));

	vector2 obj_pos;
	Physics* physics;	

	ParticleGenerator* missile_particle;

	float plaskSound = 0;
};
