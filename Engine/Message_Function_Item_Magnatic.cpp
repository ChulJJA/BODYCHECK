/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Item_Magnatic.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Item Magnetic
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Item_Magnatic.h"
#include "Object.h"
#include "Message.h"
#include "Component_Player.h"
#include "Player_Ui.h"
#include "Component_Sprite.h"
#include "Physics.h"
#include "Component_Lock.h"
#include "ObjectManager.h"
#include "angles.hpp"

void Msg_Func_Item_Magnatic::Init()
{
	if (msg->Get_Target() != nullptr)
	{
		Object* obj = msg->Get_Target();
		Player* info_player = obj->GetComponentByTemplate<Player>();
		PLAYER_UI* info_ui = info_player->Get_Ui();

		if (obj != nullptr && info_player != nullptr && info_ui != nullptr)
		{
			obj->GetMesh().Get_Is_Moved() = true;

			info_player->Set_Item_State(Item::Item_Kind::None);
			info_player->Set_Char_State(Player::Char_State::Prepare);
			info_player->Set_Prepare_Timer(-1.f);
			
			obj->Change_Sprite(obj->Find_Sprite_By_Type(Sprite_Type::Player_Aiming));
			info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Magnatic);
		}
	}
}

void Msg_Func_Item_Magnatic::Update(float dt)
{
	Player* info_player = m_target->GetComponentByTemplate<Player>();
	if(info_player != nullptr)
	{
		if(info_player->Get_Char_State() == Player::Char_State::Prepared)
		{
			Object* lock = new Object();
			lock->Set_Name("lock");
			lock->Set_Tag("lock");
			lock->SetNeedCollision(true);
			lock->AddComponent(new Sprite(lock, "../sprite/zoom.png", m_target->GetTransform().GetTranslation()));
			lock->AddComponent(new Physics());
			lock->AddComponent(new Lock());
			lock->GetComponentByTemplate<Lock>()->Set_Speed(1000.f);
			lock->GetComponentByTemplate<Lock>()->Set_Locking_Obj(m_target);
			lock->SetScale(2.f);
			info_player->Set_Locking(lock);
			info_player->Set_Char_State(Player::Char_State::Lock_Ing);
			ObjectManager::GetObjectManager()->AddObject(lock);
		}
		else if(info_player->Get_Char_State() == Player::Char_State::Magnatic)
		{
			if (info_player->Get_Locking_Result() != nullptr)
			{
				info_player->Set_Char_State_Additional(Player::Char_State_Additional::Chasing);
				Object* locking_result = info_player->Get_Locking_Result();
				
				vector2 target = locking_result->GetTransform().GetTranslation() - m_target->GetTransform().GetTranslation();

				vector2 target_dir = normalize(target);
				vector2 own_pos = m_target->GetTransform().GetTranslation();

				own_pos.x += (target_dir.x * 15);
				own_pos.y += (target_dir.y * 15);

				vector2 this_pos = m_target->GetTransform().GetTranslation();
				vector2 obj_pos = locking_result->GetTransform().GetTranslation();
				float value = cross({ target.x, target.y, 0.f }, { this_pos.x, this_pos.y, 0.f }).z;

				float angle_in_radian = atan2(obj_pos.y - this_pos.y, obj_pos.x - this_pos.x);
				float angle = to_degrees(angle_in_radian);
				angle += 90;

				m_target->GetComponentByTemplate<Player>()->SetPlayerVelocity(
					{ sin(angle_in_radian) * -20, cos(angle_in_radian) * 20 }
				);

				m_target->SetRotation(angle);

				if (value > 0)
				{
					vector3 convert_pos(own_pos.x, own_pos.y, 1.f);

					convert_pos = MATRIX3::build_rotation(to_radians(-10)) * convert_pos;

					own_pos.x = convert_pos.x;
					own_pos.y = convert_pos.y;
				}
				else if (value < 0)
				{
					vector3 convert_pos(own_pos.x, own_pos.y, 1.f);

					convert_pos = MATRIX3::build_rotation(to_radians(10)) * convert_pos;

					own_pos.x = convert_pos.x;
					own_pos.y = convert_pos.y;
				}
				m_target->GetTransform().SetTranslation(own_pos);
			}
			else
			{
				info_player->Set_Char_State(Player::Char_State::None);
				m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
				msg->Set_Should_Delete(true);
			}
		}
		else if(info_player->Get_Char_State() == Player::Char_State::None)
		{
			msg->Set_Should_Delete(true);
		}
	}
	
}
