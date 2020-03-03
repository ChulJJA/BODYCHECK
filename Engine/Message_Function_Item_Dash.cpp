#include "Message_Function_Item_Dash.h"
#include "Message.h"
#include "vector2.hpp"
#include "Physics.h"
#include "Object.h"
#include "Sound_Manager.h"
#include "Engine.hpp"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Component_Sprite.h"
#include "Player_Ui.h"


void Msg_Func_Item_Dash::Init()
{
}

void Msg_Func_Item_Dash::Update(float dt)
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		vector2 acceleration = obj->GetComponentByTemplate<Physics>()->GetAcceleration();
		acceleration = normalize(acceleration);

		acceleration += {50 * acceleration.x, 50 * acceleration.y};

		obj->GetComponentByTemplate<Physics>()->SetAcceleration(acceleration);
		obj->GetMesh().Get_Is_Moved() = true;
		obj->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);

		obj->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->DeleteComponent(
			obj->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>());


		msg->Set_Should_Delete(true);
	}
}
