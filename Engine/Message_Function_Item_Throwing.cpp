#include "Message_Function_Item_Throwing.h"

#include "Message.h"
#include "Object.h"
#include "Component_Player.h"

void Msg_Func_Item_Throwing::Init()
{
	if(msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		obj->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
		obj->GetComponentByTemplate<Player>()->Set_Char_State(Player::Char_State::Throwing);
	}
}

void Msg_Func_Item_Throwing::Update(float dt)
{
	
}
