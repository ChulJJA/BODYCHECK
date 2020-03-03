#include "Message_Function_Item_Bulkup.h"
#include "Component_Player.h"
#include "Object.h"
#include "Message.h"
#include "Component_Sprite.h"
#include "Player_Ui.h"


void Msg_Func_Item_Bulkup::Init()
{
	if(msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();

		obj->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);

		obj->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->DeleteComponent(
			obj->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>());
	}
}

void Msg_Func_Item_Bulkup::Update(float dt)
{
	if (m_target->GetComponentByTemplate<Player>() != nullptr &&
		m_target->GetComponentByTemplate<Player>()->Get_Char_State() == Player::Char_State::None)
	{
		m_target->GetComponentByTemplate<Player>()->Set_Char_State(Player::Char_State::Bulk_Up);
		m_target->GetComponentByTemplate<Player>()->Get_Bulkup_Timer() = 5.f;
	}
	msg->Set_Should_Delete(true);
}
