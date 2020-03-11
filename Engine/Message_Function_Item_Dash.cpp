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
		
		vector2 acceleration = info_player->GetPlayerVelocity();

		vector2 direction = info_physics->GetObjectAngle();
		info_player->SetPlayerVelocity(acceleration + direction * 30);
		info_player->Set_Item_State(Item::Item_Kind::None);
		info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Dash);
	}
}

void Msg_Func_Item_Dash::Update(float dt)
{

	msg->Set_Should_Delete(true);

}
