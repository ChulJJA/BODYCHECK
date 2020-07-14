/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Item_Throwing.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Item Throwing
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Item_Throwing.h"

#include "Message.h"
#include "Object.h"
#include "Component_Player.h"
#include "Player_Ui.h"
#include "Component_Sprite.h"
#include "Physics.h"
#include "Component_Throwing.h"
#include "ObjectManager.h"
#include "Engine.hpp"

void Msg_Func_Item_Throwing::Init()
{
	if(msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();

		if(info_player != nullptr)
		{
			PLAYER_UI* info_ui = info_player->Get_Ui();

			info_player->Set_Item_State(Item::Item_Kind::None);
			info_player->Set_Char_State(Player::Char_State::Prepare);
			info_player->Set_Prepare_Timer(0.1f);
			sound.Play(SOUND::Throwing);
			obj->Change_Sprite(obj->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Throwing));
			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Throwing);

			particle = new ParticleGenerator(obj, 20, "../Sprite/ParticleFire.png", ParticleType::SPEEDMODE);
		}
	}
}

void Msg_Func_Item_Throwing::Update(float dt)
{
	Player* info_player = m_target->GetComponentByTemplate<Player>();

	if (info_player != nullptr)
	{
		if (info_player->Get_Char_State() == Player::Char_State::Prepared)
		{
			info_player->Set_Char_State(Player::Char_State::None);
			throwing = new Object();
			throwing->Set_Name("throwing");
			throwing->Set_Tag("throwing");
			throwing->AddComponent(new Sprite(throwing, "../Sprite/Item/bullet.png", m_target->GetTransform().GetTranslation()));
			throwing->AddComponent(new Physics());
			throwing->AddComponent(new Throwing);
			throwing->GetComponentByTemplate<Throwing>()->Set_Timer(3.f);
			throwing->GetComponentByTemplate<Throwing>()->Set_Angle(m_target->GetTransform().GetRotation());
			throwing->GetComponentByTemplate<Throwing>()->Set_Throwing_Obj(m_target);
			throwing->SetScale(5.f);
			throwing->SetNeedCollision(true);
			ObjectManager::GetObjectManager()->AddObject(throwing);
			info_player->Change_To_Normal_State();


			m_target->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Throwing)->Set_Need_Update(false);
			msg->Set_Should_Delete(true);

		}
		else if (info_player->Get_Char_State() == Player::Char_State::None)
		{
			info_player->Change_To_Normal_State();
			m_target->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Throwing)->Set_Need_Update(false);
			msg->Set_Should_Delete(true);
			delete particle;
		}
	}
	if (particle != nullptr && throwing != nullptr)
	{
		particle->Update(dt, throwing, 1, vector2(-throwing->GetScale_Reference() / 2.0f));
		particle->Draw(throwing);
	}
}
