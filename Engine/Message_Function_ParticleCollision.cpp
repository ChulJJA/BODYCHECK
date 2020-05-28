#include "Message_Function_ParticleCollision.h"
#include "Message.h"

void Msg_Func_ParticleCollision::Init()
{
	collide_particle = new ParticleGenerator(m_target, 30, "../Sprite/ParticleCollision.png", ParticleType::COLLIDE);
}

void Msg_Func_ParticleCollision::Update(float dt)
{
	if (timer > 0.f)
	{
		timer -= dt;
		if (m_target != nullptr && collide_particle != nullptr)
		{
			GLfloat rand1 = ((rand() % 200) - 100);
			GLfloat rand2 = ((rand() % 200) - 100);

			collide_particle->Update(dt, m_target, 1, vector2(rand1, rand2));
			collide_particle->Draw(m_target);
		}
	}
	else
	{
		delete(collide_particle);
		msg->Set_Should_Delete(true);
	}
}
