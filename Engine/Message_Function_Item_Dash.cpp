#include "Message_Function_Item_Dash.h"
#include "Message.h"
#include "vector2.hpp"
#include "Physics.h"
#include "Object.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Player_Ui.h"
#include "angles.hpp"

void Msg_Func_Item_Dash::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();
		Physics* info_physics = obj->GetComponentByTemplate<Physics>();
		//vector2 acceleration(1.f);

		
		vector2 acceleration = info_physics->GetAcceleration();
		acceleration = normalize(acceleration);
		acceleration += {50 * acceleration.x, 50 * acceleration.y};

		//float angle = obj->GetTransform().GetRotation();
		//float angle_in_radian = to_radians(angle);
		//acceleration.x += (-sin(angle_in_radian) * 10);
		//acceleration.y += (cos(angle_in_radian) * 10);

		//if(-sin(angle_in_radian) > 0)
		//{
		//	std::cout << "x : +" << std::endl;
		//}
		//else
		//{
		//	std::cout << "x : -" << std::endl;
		//}
		//if(cos(angle_in_radian) > 0)
		//{
		//	std::cout << "y : +" << std::endl;
		//}
		//else
		//{
		//	std::cout << "y : -" << std::endl;
		//}

		
		info_physics->SetAcceleration(acceleration);
		
		
		obj->GetMesh().Get_Is_Moved() = true;
		info_player->Set_Item_State(Item::Item_Kind::None);

		info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Dash);
	}
}

void Msg_Func_Item_Dash::Update(float dt)
{

	msg->Set_Should_Delete(true);

}
