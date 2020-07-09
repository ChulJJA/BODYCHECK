/*
 * Author		:Sangmin Kim
 * File			:Component_Timer.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Component Timer
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

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
