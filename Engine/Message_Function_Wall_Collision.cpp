#include "Message_Function_Wall_Collision.h"
#include "Component_Player.h"
#include "Component_Hpbar.h"
#include "Physics.h"
#include "Component_Text.h"
#include "Message.h"

void Msg_Func_Wall_Collision::Init()
{
	
}

void Msg_Func_Wall_Collision::Update(float dt)
{
	if (m_target->GetComponentByTemplate<Player>() != nullptr)
	{
		Object* target_hp_bar = m_target->Get_Belong_Object_By_Tag("hp_bar");
		if (target_hp_bar != nullptr)
		{
			if (target_hp_bar->GetComponentByTemplate<Hp_Bar>() != nullptr)
			{
				float damage_to_target = 0;
				Physics* temp_physics = m_target->GetComponentByTemplate<Physics>();
				damage_to_target += (sqrt((temp_physics->Get_Save_Acceleration_Reference().x * temp_physics->Get_Save_Acceleration_Reference().x) +
					(temp_physics->Get_Save_Acceleration_Reference().y * temp_physics->Get_Save_Acceleration_Reference().y)));
				damage_to_target -= m_target->Get_Plus_Dmg();
				

				target_hp_bar->GetComponentByTemplate<Hp_Bar>()->Decrease(damage_to_target / 200);

				m_target->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->GetText().SetString(L"-" + std::to_wstring(static_cast<int>(damage_to_target)));
				m_target->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->Get_Timer() = 1.f;
				m_target->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().x = m_target->GetTransform().GetTranslation().x;
				m_target->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().y = m_target->GetTransform().GetTranslation().y;
			}
		}
	}
	m_target->Set_Is_It_Collided(false);
	msg->Set_Should_Delete(true);
}
