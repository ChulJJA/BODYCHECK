/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Collision.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message Function Collision
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include "Message_Function_Base.h"
#include "Physics.h"
#include "View.h"
#include "Particle.h"


class Msg_Func_Collision : public Msg_Func_Base
{
public:
	void Init() override;
	void Update(float dt) override;
	

	Msg_Func_Collision(Object* m_from_, Object* m_target_, Message* msg_)
	{
		m_from = m_from_;
		m_target = m_target_;
		msg = msg_;
	}

	~Msg_Func_Collision()
	{

	}

	void Player_Get_Item(Object* player, Object* item);
	void Player_And_Player_Collision();
	void Player_And_Lock_Collision(Object* player, Object* lock);
	void Player_And_Mine_Collision(Object* player, Object* mine);

private:
	float timer = 0.5f;

	Physics physics;

	ParticleGenerator* collide_particle;
	float* particle_timer = 0;
};
