#include "Message_Function_Item_Recover.h"
#include "Component_Hpbar.h"
#include <ostream>
#include <iostream>
#include "Object.h"
#include "Message.h"

void Msg_Func_Item_Recover::Init()
{
}

void Msg_Func_Item_Recover::Update(float dt)
{
	if (timer >= 0.f)
	{
		timer -= dt;

		std::cout << "check!" << std::endl;
		if (m_target->GetTransform().GetScale_Reference().x <= 1.f)
		{
			m_target->GetTransform().GetScale_Reference().x += dt;

			if (m_target->GetComponentByTemplate<Hp_Bar>() != nullptr)
			{
				m_target->GetComponentByTemplate<Hp_Bar>()->Get_Set_Offset() = 0;
			}

			m_target->GetTransform().GetTranslation_Reference().x = m_target->Get_This_Obj_Owner()->GetTransform().GetTranslation().x;
		}

		if (timer <= 0.f)
		{
			msg->Set_Should_Delete(true);
		}
	}
}
