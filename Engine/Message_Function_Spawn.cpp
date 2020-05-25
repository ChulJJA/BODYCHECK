#include "Message_Function_Spawn.h"
#include "Component_Player.h"
#include "Component_Item.h"
#include "Message.h"
#include "Component_Sprite.h"

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
		timer -= dt;
	}
	else
	{
		if (is_item)
		{
			Component* find_comp = m_target->Find_Sprite_By_Type(Sprite_Type::Item);
			m_target->Change_Sprite(find_comp);
		}
		else
		{

		}
		msg->Set_Should_Delete(true);
	}

}
