#include "Message_Function_Item_Recover.h"
#include "Component_Hpbar.h"
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
		hp_bar->GetComponentByTemplate<Hp_Bar>()->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Recovering);
		hp_bar->GetComponentByTemplate<Hp_Bar>()->Set_Timer(3.f);
	}
}

void Msg_Func_Item_Recover::Update(float dt)
{
	msg->Set_Should_Delete(true);
}
