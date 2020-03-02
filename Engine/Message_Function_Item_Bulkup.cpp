#include "Message_Function_Item_Bulkup.h"
#include "Component_Player.h"
#include "Object.h"
#include "Message.h"

void Msg_Func_Item_Bulkup::Init()
{

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
