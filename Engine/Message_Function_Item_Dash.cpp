#include "Message_Function_Item_Dash.h"
#include "Message.h"


void Msg_Func_Item_Dash::Init()
{
}

void Msg_Func_Item_Dash::Update(float dt)
{
	msg->Set_Should_Delete(true);
}
