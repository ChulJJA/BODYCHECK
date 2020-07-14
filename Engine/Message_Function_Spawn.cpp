/*
 * Author		:Sangmin Kim
 * File			:Message_Function Spawn.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Spawn
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Spawn.h"
#include "Component_Player.h"
#include "Component_Item.h"
#include "Message.h"
#include "Component_Sprite.h"
#include "Engine.hpp"
#include "ObjectManager.h"

void Msg_Func_spawn::Init()
{
	if (m_target != nullptr)
	{
		Player* info_player = m_target->GetComponentByTemplate<Player>();

		if (info_player == nullptr)
		{
			//maybe item
		}
		else
		{
			//maybe player
			is_item = false;
		}
	}

}

void Msg_Func_spawn::Update(float dt)
{
	if (timer > 0.f)
	{
		if(dt < 0.5f)
		{
			timer -= dt;
		}
	}
	else
	{
		if (is_item)
		{
			Component* find_comp = m_target->Find_Sprite_By_Type(Sprite_Type::Item);
			sound.Play(SOUND::ItemAppear2);
			m_target->Change_Sprite(find_comp);
		}
		else
		{
			Player* info_player = m_target->GetComponentByTemplate<Player>();
			info_player->Set_Need_Update(true);

			info_player->Get_Hp_Bar()->GetComponentByTemplate<Sprite>()->Set_Need_Update(true);
			info_player->Set_Item_State(Item::Item_Kind::None);
			m_target->Set_Tag("player");
			m_target->SetNeedCollision(true);
			m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
			m_target->SetScale(2.f);
		}
		msg->Set_Should_Delete(true);
	}
}