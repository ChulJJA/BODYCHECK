/*
 * Author		:Jeesoo Kim
 * File			:Message_Function_ParticleCollision.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Particle Collision
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_ParticleCollision.h"
#include "Message.h"

void Msg_Func_ParticleCollision::Init()
{
	collide_particle = new ParticleGenerator(m_target, 30, "../Sprite/ParticleCollision2.png", ParticleType::COLLIDE);
}

void Msg_Func_ParticleCollision::Update(float dt)
{
	timer -= dt;
	if (timer > 0.f)
	{
		if (m_target != nullptr && collide_particle != nullptr)
		{
			GLfloat rand1 = ((rand() % 200) - 100);
			GLfloat rand2 = ((rand() % 200) - 100);
			if (timer > 0.2f)
			{
				collide_particle->Update(dt, m_target, 1, vector2(rand1, rand2));
			}
			else 
			{
				collide_particle->Update(dt, m_target, 0, vector2(rand1, rand2));
			}
			collide_particle->Draw(m_target);
		}
	}
	else 
	{
		delete(collide_particle);
		msg->Set_Should_Delete(true);
	}
}
