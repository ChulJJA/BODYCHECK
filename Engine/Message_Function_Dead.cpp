#include "Message_Function_Dead.h"
#include "Object.h"
#include "Message.h"
#include "Component_Sprite.h"
#include "Component_Player.h"
#include "Player_Ui.h"

void Msg_Func_Dead::Init()
{
	if(m_target != nullptr)
	{
		Player* info_player = m_target->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();
		
		m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Die));
		info_player->Change_Weapon_Sprite(nullptr);
		m_target->SetNeedCollision(false);

		info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Life, Ui::Ui_Status_Verb::None, Ui::Ui_Status_Obj::None);
		//m_target->Delete_All_Components_But_Sprite();
	}
}

void Msg_Func_Dead::Update(float dt)
{
	if(m_target != nullptr)
	{
		if(timer > 0.f)
		{
			timer -= dt;
		}
		else
		{
			//m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
			m_target->SetDeadCondition(true);
			msg->Set_Should_Delete(true);
		}
	}
}
