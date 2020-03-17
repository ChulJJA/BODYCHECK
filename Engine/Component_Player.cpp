/*
 * Author		:Sangmin Kim
 * File			:Component_Player.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Basic component for player, which initialize the hpbar object and
 *				 attach to the owner object.
 *				 UI Objects are attached in here too.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Player.h"
#include "Message_Manager.h"
#include "ObjectManager.h"
#include "Input.h"
#include "Component_Enemy.h"
#include "Component_Sprite.h"
#include "Component_Hpbar.h"
#include <GLFW/glfw3.h>
#include "Player_Ui.h"
#include "UsefulTools.hpp"
#include "Engine.hpp"
#include "Referee.h"
#include "Message_Kind.h"

void Player::Init(Object* obj)
{
	m_owner = obj;
	m_owner->Get_Component_Info_Reference().component_info_player = true;
	SetHPBar();
}

void Player::Update(float dt)
{
	if (m_owner->Get_Tag() == "player")
	{
		if (curr_state == Char_State::Prepare)
		{
			if (prepare_sprite_timer != 0.f && change_to_sprite != nullptr)
			{
				if (prepare_sprite_timer > 0.f)
				{
					prepare_sprite_timer -= dt;
				}
				else
				{
					m_owner->Change_Sprite(change_to_sprite);
					curr_state = Char_State::Prepared;
				}
			}
		}

		else if (curr_state == Char_State::Time_Pause)
		{
			Func_Time_Pause(dt);
		}
		else if (curr_state == Char_State::Reverse_Moving)
		{
			Func_Reverse_Moving(dt);
		}


		
		vector2& player_pos = m_owner->GetTransform().GetTranslation_Reference();
		
		if (hp_bar != nullptr)
		{
			vector2& hp_pos = hp_bar->GetTransform().GetTranslation_Reference();
			
			hp_pos.x = player_pos.x;
			hp_pos.y = player_pos.y - 100;
		}


		if (curr_state != Player::Char_State::Reverse_Moving && curr_state != Player::Char_State::Time_Pause &&
			curr_state_additional != Char_State_Additional::Chasing)
		{
			PlayerMovement(0.6f, 0.12f);
			player_pos += velocity;

		}
		else if (curr_state == Player::Char_State::Reverse_Moving && curr_state != Player::Char_State::Time_Pause &&
			curr_state_additional != Char_State_Additional::Chasing)
		{
			PlayerMovement(-0.12f, -0.6f);
			player_pos += velocity;

		}
		PlayerDirecting();
		
		if (input.Is_Key_Triggered(GLFW_KEY_SPACE))
		{
			UseItem();
		}
	}
}

void Player::SetHPBar()
{
	Object* hp_bar = new Object();
	vector2 hp_bar_pos = m_owner->GetTransform().GetTranslation();
	hp_bar_pos.y -= 100;
	hp_bar->SetTranslation(hp_bar_pos);
	hp_bar->SetScale({ 1.f, 2.5f });
	hp_bar->Set_Name(m_owner->Get_Name() + "hp_bar");
	hp_bar->Set_Tag("hp_bar");
	hp_bar->AddComponent(new Sprite(hp_bar, "../Sprite/HP.png", hp_bar_pos, false), "sprite_hp_bar", need_update_hp_bar);
	hp_bar->Set_This_Obj_Owner(m_owner);
	hp_bar->AddComponent(new Hp_Bar());

	this->hp_bar = hp_bar;
	m_owner->Get_Belongs_Objects().push_back(hp_bar);

	if (m_owner->Get_Tag() != "save" && m_owner->Get_Tag() != "throwing")
	{
		ObjectManager::GetObjectManager()->AddObject(hp_bar);
	}
}

int Player::Get_Damage() const
{
	return damage;
}

Item::Item_Kind Player::Get_Item_State() const
{
	return belong_item;
}

void Player::Set_Item_State(Item::Item_Kind state)
{
	this->belong_item = state;
}


void Player::Set_Locking_By(Object* obj)
{
	if (obj != nullptr)
	{
		locking_by = obj;
		obj->Add_Pointed_By(&locking_by);
	}
}

void Player::Set_Locking_Result(Object* obj)
{
	if (obj != nullptr)
	{
		locking_result = obj;
		obj->Add_Pointed_By(&locking_result);
	}

}

Object* Player::Get_Locking_Result() const
{
	return locking_result;
}


void Player::Func_Time_Pause(float dt)
{
	std::vector<Object*> another_players = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");

	another_players.erase(std::find(another_players.begin(), another_players.end(), m_owner));

	if (stop_timer > 0.0f)
	{
		stop_timer -= dt;
	}
	else
	{
		curr_state = Char_State::None;
	}
}

void Player::Func_Reverse_Moving(float dt) const
{
	std::vector<Object*> another_players = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");

	another_players.erase(std::find(another_players.begin(), another_players.end(), m_owner));

	for (auto find_player : another_players)
	{
		Player* get_player = find_player->GetComponentByTemplate<Player>();

		if (get_player->Get_Char_State() == Player::Char_State::Reverse_Moving)
		{
			if (find_player->IsDead() == true)
			{
				get_player->Get_Char_State() == Player::Char_State::None;
			}
		}
	}
}

void Player::Set_This_UI_info(PLAYER_UI* ui)
{
	this_ui = ui;
}

PLAYER_UI* Player::Get_Ui() const
{
	return this_ui;
}

float& Player::Get_Regeneration_Timer()
{
	return regeneration_timer;
}

float& Player::Get_Bulkup_Timer()
{
	return bulkup_timer;
}

void Player::Set_Bulkup_Timer(float timer_)
{
	bulkup_timer = timer_;
}

Player::Char_State Player::Get_Char_State() const
{
	return curr_state;
}

void Player::Set_Char_State(Char_State state)
{
	curr_state = state;
}

void Player::Set_Char_State_Additional(Char_State_Additional state)
{
	curr_state_additional = state;
}

Player::Char_State_Additional Player::Get_Char_State_Additional() const
{
	return curr_state_additional;
}


Object* Player::Get_Locking() const
{
	return locking_pointer;
}

void Player::Set_Locking(Object* obj)
{
	if (obj != nullptr)
	{
		locking_pointer = obj;
		obj->Add_Pointed_By(&locking_pointer);
	}
}

Object* Player::Get_Hp_Bar() const
{
	return hp_bar;
}
float& Player::Get_Stop_Timer()
{
	return stop_timer;
}
void  Player::Set_Stop_Timer(float timer_)
{
	stop_timer = timer_;
}


void Player::PlayerMovement(float max_velocity, float min_velocity)
{
	if (input.Is_Key_Pressed(GLFW_KEY_W))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_W) && input.Is_Key_Pressed(GLFW_KEY_A))
		{
			if (velocity.x >= 0 && velocity.y >= 0)
			{
				velocity += {-max_velocity, min_velocity};
			}
			else if (velocity.x >= 0 && velocity.y < 0)
			{
				velocity += {-max_velocity, max_velocity};
			}
			else if (velocity.x < 0 && velocity.y >= 0)
			{
				velocity += {-min_velocity, min_velocity};
			}
			else if (velocity.x < 0 && velocity.y < 0)
			{
				velocity += {-min_velocity, max_velocity};
			}
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_W) && input.Is_Key_Pressed(GLFW_KEY_D))
		{
			if (velocity.x >= 0 && velocity.y >= 0)
			{
				velocity += {min_velocity, min_velocity};
			}
			else if (velocity.x >= 0 && velocity.y < 0)
			{
				velocity += {min_velocity, max_velocity};
			}
			else if (velocity.x < 0 && velocity.y >= 0)
			{
				velocity += {max_velocity, min_velocity};
			}
			else if (velocity.x < 0 && velocity.y < 0)
			{
				velocity += {max_velocity, max_velocity};
			}
		}
		else
		{
			if (abs(velocity.x) >= 0)
			{
				velocity.x -= velocity.x / 100;
			}
			if (velocity.y >= 0)
			{
				velocity += {0.00, min_velocity};
			}
			else if (velocity.y < 0)
			{
				velocity += {0.00, max_velocity};
			}
		}
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_A))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_A) && input.Is_Key_Pressed(GLFW_KEY_S))
		{
			if (velocity.x >= 0 && velocity.y >= 0)
			{
				velocity += {-max_velocity, -max_velocity};
			}
			else if (velocity.x >= 0 && velocity.y < 0)
			{
				velocity += {-max_velocity, -min_velocity};
			}
			else if (velocity.x < 0 && velocity.y >= 0)
			{
				velocity += {-min_velocity, -max_velocity};
			}
			else if (velocity.x < 0 && velocity.y < 0)
			{
				velocity += {-min_velocity, -min_velocity};
			}
		}
		else
		{
			if (velocity.x >= 0)
			{
				velocity.x += -max_velocity;
			}
			else
			{
				velocity.x += -min_velocity;
			}
			if (abs(velocity.y) >= 0)
			{
				velocity.y -= velocity.y / 100;
			}
		}
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_S))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_S) && input.Is_Key_Pressed(GLFW_KEY_D))
		{
			if (velocity.x >= 0 && velocity.y >= 0)
			{
				velocity += {min_velocity, -max_velocity};
			}
			else if (velocity.x >= 0 && velocity.y < 0)
			{
				velocity += {min_velocity, -min_velocity};
			}
			else if (velocity.x < 0 && velocity.y >= 0)
			{
				velocity += {max_velocity, -max_velocity};
			}
			else if (velocity.x < 0 && velocity.y < 0)
			{
				velocity += {max_velocity, -min_velocity};
			}
		}
		else
		{
			if (abs(velocity.x) >= 0)
			{
				velocity.x -= velocity.x / 100;
			}
			if (velocity.y >= 0)
			{
				velocity.y += -max_velocity;
			}
			else
			{
				velocity.y += -min_velocity;
			}
		}
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_D))
	{
		if (velocity.x >= 0)
		{
			velocity.x += min_velocity;
		}
		else
		{
			velocity.x += max_velocity;
		}
		if (abs(velocity.y) >= 0)
		{
			velocity.y -= velocity.y / 100;
		}
	}
	else
	{
		velocity += {-velocity.x / 100, -velocity.y / 100};
	}
}

void Player::SetPlayerVelocity(vector2 current_velocity)
{
	velocity = current_velocity;
}

vector2 Player::GetPlayerVelocity()
{
	return velocity;
}

void Player::PlayerDirecting()
{
	if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_UP))
		{
			direction.x += 0.03f;
			direction.y += 0.03f;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_DOWN))
		{
			direction.x += 0.03f;
			direction.y -= 0.03f;
		}
		else
		{
			direction.x += 0.045f;
		}
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_UP))
		{
			direction.x -= 0.03f;
			direction.y += 0.03f;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_DOWN))
		{
			direction.x -= 0.03f;
			direction.y -= 0.03f;
		}
		else
		{
			direction.x -= 0.045f;
		}
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_DOWN))
	{
		direction.y -= 0.045f;
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_UP))
	{
		direction.y += 0.045f;
	}

	float angle = RadianToDegree(angle_between({ 0,1 }, direction));
	if (direction.x >= 0)
	{
		angle *= -1;
	}
	m_owner->SetRotation(angle);
	direction = normalize(direction);
}

vector2 Player::GetPlayerDirection()
{
	return direction;
}

void Player::UseItem()
{
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Dash)
	{
		sound.Play(SOUND::Dash);
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Dash));
	}
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::HP)
	{
		sound.Play(SOUND::HP);
		Object* hp_bar = m_owner->Get_Belong_Object_By_Tag("hp_bar");
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(hp_bar, m_owner, Message_Kind::Item_Recover));
	}

	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Bulkup)
	{
		sound.Play(SOUND::BulkUp);
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Bulkup, 5.f));
	}

	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Throwing)
	{
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Throwing, 0.f));
	}
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Magnatic)
	{
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Magnetic));
	}
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Time_Pause)
	{
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Timepause));
	}
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Reverse_Moving)
	{
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Reverse));
	}
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Missile)
	{
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Missile));
	}
}

void Player::Set_Missile_Timer(float timer)
{
	missile_timer = timer;
}

void Player::Change_To_Normal_State()
{
	curr_state = Char_State::None;
	curr_state_additional = Char_State_Additional::None;
	m_owner->Change_Sprite(m_owner->Find_Sprite_By_Name("normal"));
}

void Player::Set_Prepare_Timer(float timer)
{
	prepare_sprite_timer = timer;
}

void Player::Sprite_After_Preparation(Component* sprite_to_change)
{
	if (sprite_to_change != nullptr)
	{
		change_to_sprite = sprite_to_change;
	}
}

void Player::State_After_Preparation(Char_State state)
{
	change_to_state = state;
}
