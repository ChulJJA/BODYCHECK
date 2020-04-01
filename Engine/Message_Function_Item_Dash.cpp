#include "Message_Function_Item_Dash.h"
#include "Message.h"
#include "vector2.hpp"
#include "Object.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Player_Ui.h"

void Msg_Func_Item_Dash::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();
		vector2 velocity = info_player->GetPlayerVelocity();

		vector2 direction = info_player->GetPlayerDirection();
		info_player->SetPlayerVelocity(velocity + direction * 50);
		info_player->Set_Item_State(Item::Item_Kind::None);
		info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Dash);

		dash_particle = new ParticleGenerator(obj, 50, "../Sprite/ParticleDash.png", ParticleType::DASH);
	}
}

void Msg_Func_Item_Dash::Update(float dt)
{
	timer -= dt;
	if (m_target != nullptr)
	{
		dash_particle->Update(dt, m_target, 2, vector2(0, -50.0f));
		dash_particle->Draw(m_target);
	}
	if(timer < 0)
	{
		physics.SpeedDown(m_target);
		msg->Set_Should_Delete(true);
		delete(dash_particle);
	}
}