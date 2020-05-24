#include "Component_Timer.h"

void Component_Timer::Init(Object* obj)
{
	m_owner = obj;
}

void Component_Timer::Update(float dt)
{
	vector2& pos = m_owner->GetTransform().GetTranslation_Reference();

	if (pos.x > 0.f)
	{

	}
}
