#include "Message_Function_Item_Recover.h"
#include "Component_Hpbar.h"
#include <ostream>
#include <iostream>
#include "Object.h"
#include "Message.h"
#include "Component_Player.h"
#include "Component_Sprite.h"
#include "Player_Ui.h"

void Msg_Func_Item_Recover::Init()
{
	if(msg->Get_From() != nullptr && msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_From();

		obj->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
		
		obj->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->DeleteComponent(
			obj->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>());

		Object* hp_bar = msg->Get_Target();

		if (hp_bar->GetComponentByTemplate<Hp_Bar>() != nullptr)
		{
			hp_bar->GetTransform().GetTranslation_Reference().x = 0.f;
			hp_bar->GetComponentByTemplate<Hp_Bar>()->Get_Set_Offset() = 0;
		}

		hp_bar->GetMesh().Get_Is_Moved() = true;
	}
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
