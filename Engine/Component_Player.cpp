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
#include "Particle.h"
#include <GLFW/glfw3.h>
#include "Player_Ui.h"
#include "UsefulTools.hpp"
#include "Engine.hpp"
#include "Referee.h"
#include "Message_Kind.h"
#include "Physics.h"
#include "Gamepad.hpp"

GLFWgamepadstate state;

namespace
{
	Gamepad* gamepadManager = nullptr;
	ParticleGenerator* speedParticle = nullptr;
}


void Player::Init(Object* obj)
{
	gamepadManager = Gamepad::getGamepad();

	m_owner = obj;
	m_owner->Get_Component_Info_Reference().component_info_player = true;
	if (m_owner->Get_Tag() == "install_mine")
	{
		hp_bar = nullptr;
	}
	else
	{
		SetHPBar();
	}
}

void Player::Update(float dt)
{
	float RightTriggerState = gamepadManager->RightTrigger();
	
	if (curr_state == Char_State::Prepare)
	{
		if (prepare_sprite_timer != 0.f)
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
	if (item_used == Item_Use_Status::Bulkup)
	{
		m_owner->Change_Sprite(m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Bulkup_Used));
	}

	else if (curr_state == Char_State::Time_Pause)
	{
		Func_Time_Pause(dt);
	}
	else if (curr_state == Char_State::Reverse_Moving)
	{
		Func_Reverse_Moving(dt);
	}
	else if (curr_state == Char_State::Mine)
	{
		Func_Mine(dt);
	}

	else if (curr_state_additional == Char_State_Additional::Get_mine)
	{
		Func_Mine_Collided(dt);
	}


	vector2& player_pos = m_owner->GetTransform().GetTranslation_Reference();

	if (hp_bar != nullptr)
	{
		vector2& hp_pos = hp_bar->GetTransform().GetTranslation_Reference();

		hp_pos.x = player_pos.x;
		hp_pos.y = player_pos.y - 100;
	}


	if (curr_state != Player::Char_State::Reverse_Moving && curr_state != Player::Char_State::Time_Pause &&
		curr_state_additional != Char_State_Additional::Chasing /*&& curr_state_additional != Char_State_Additional::Get_mine*/)
	{
		if (m_owner->Get_Current_Sprite() != m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Die))
		{
			if (curr_state_additional != Char_State_Additional::Get_mine)
			{

				PlayerMovement(0.6f, 0.12f);
				player_pos += velocity;
			}
			else
			{
				player_pos += velocity;
			}
		}
		const float scale_plus = 0.003f;
		const float scale_minus = 0.01f;

		const float speed_mag = magnitude_squared(velocity);

		if (speed_mag > 100.f)
		{
			Component* normal_sprite = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Normal);

			if (speed_mag < 2000.f)
			{
				if (normal_sprite == m_owner->Get_Current_Sprite())
				{
					Component* speed2_sprite = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Speed2);
					if (speed2_sprite != m_owner->Get_Current_Sprite())
					{
						m_owner->Change_Sprite(speed2_sprite);
						/*if (speedParticle != nullptr)
						{
							delete speedParticle;
							speedParticle = nullptr;
						}*/
					}
				}
			}
			else
			{
				Component* speed2_sprite = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Speed2);

				if (speed2_sprite == m_owner->Get_Current_Sprite())
				{
					Component* speed3_sprite = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Speed3);
					if (speed3_sprite != m_owner->Get_Current_Sprite())
					{
						m_owner->Change_Sprite(speed3_sprite);
						//speedParticle = new ParticleGenerator(m_owner, 20, "../Sprite/Particle.png", ParticleType::DASH);
					}
				}
			}

			vector2& scale = m_owner->GetScale_Reference();
			if (scale.x < 4.f && scale.y < 4.f)
			{
				scale.x += scale_plus;
				scale.y += scale_plus;
			}
			
			/*if (speedParticle != nullptr && speed_mag > 2000.0f)
			{
				speedParticle->Update(dt, m_owner, 1, vector2(-m_owner->GetScale_Reference() / 2.0f));
				speedParticle->Draw(m_owner);
			}*/
		}
		else
		{
			vector2& scale = m_owner->GetScale_Reference();
			vector2 og_scale = m_owner->GetTransform().Get_Original_Scale();
			if (scale.x > og_scale.x)
			{
				scale.x -= scale_minus;
				scale.y -= scale_minus;
			}

			if (speed_mag < 20.f)
			{
				if (m_owner->Get_Current_Sprite() == m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Speed2) ||
					m_owner->Get_Current_Sprite() == m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Speed3))
				{
					Component* normal_sprite = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Normal);
					if (normal_sprite != m_owner->Get_Current_Sprite())
					{
						m_owner->Change_Sprite(normal_sprite);
					}
				}
			}
		}

	}
	else if (curr_state == Player::Char_State::Reverse_Moving && curr_state != Player::Char_State::Time_Pause &&
		curr_state_additional != Char_State_Additional::Chasing/*&&curr_state_additional != Char_State_Additional::Get_mine*/)
	{
		if (m_owner->Get_Current_Sprite() != m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Die))
		{
			PlayerMovement(-0.12f, -0.6f);
			player_pos += velocity;
		}
		else
		{
			player_pos += velocity;
		}
	}
	const float speed_magn = magnitude_squared(velocity);
	if (speed_magn > 2000.f && speedParticle == nullptr)
	{
		speedParticle = new ParticleGenerator(m_owner, 20, "../Sprite/Particle.png", ParticleType::SPEEDMODE);
	}
	else if (speed_magn > 100.f && speed_magn < 2000.f && speedParticle != nullptr)
	{
		delete speedParticle;
		speedParticle = nullptr;
	}
	if (speedParticle != nullptr && m_owner != nullptr && speed_magn > 2000.f)
	{
		speedParticle->Update(dt, m_owner, 1, vector2(-m_owner->GetScale_Reference() / 2.0f));
		speedParticle->Draw(m_owner);
	}

	if (input.Is_Key_Triggered(GLFW_KEY_R)
		|| input.Is_Key_Triggered(GLFW_KEY_SPACE)
		|| input.Is_Key_Triggered(GLFW_KEY_KP_7)
		|| RightTriggerState > 0 && (
			curr_state != Char_State::Reverse_Moving && curr_state != Char_State::Time_Pause))
	{
		UseItem();
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
		//ObjectManager::GetObjectManager()->AddObject(hp_bar);
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
		Change_To_Normal_State();
		FMOD_BOOL isBgm;
		FMOD_Channel_IsPlaying(sound.channel[1], &isBgm);

		if (!isBgm)
		{
			sound.Stop(SOUND::ClockTicking);
			sound.Play(SOUND::BGM2);
		}
		curr_state = Char_State::None;
	}
}

void Player::Func_Reverse_Moving(float dt)
{
	FMOD_BOOL isBGM;
	FMOD_BOOL isBGMReverse;
	FMOD_Channel_IsPlaying(sound.channel[1], &isBGM);
	FMOD_Channel_IsPlaying(sound.channel[26], &isBGMReverse);
	if (!isBGMReverse && !isBGM)
	{
		sound.Play(SOUND::BGM2);
	}
	std::vector<Object*> another_players = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");

	another_players.erase(std::find(another_players.begin(), another_players.end(), m_owner));
	if (stop_timer > 0.0f)
	{
		stop_timer -= dt;
	}
	else
	{
		Change_To_Normal_State();
		FMOD_BOOL isBgm;
		FMOD_Channel_IsPlaying(sound.channel[1], &isBgm);

		if (!isBgm)
		{
			sound.Play(SOUND::BGM2);
		}
		curr_state = Char_State::None;
	}
}

void Player::Func_Mine(float dt)
{
	if (input.Is_Key_Pressed(GLFW_KEY_SPACE))
	{
		srand(time(NULL));
		float random_position_x = rand() % 3000 - 1500;
		float random_position_y = rand() % 1300 - 650;

		curr_state = Char_State::None;
		install_mine = new Object();
		install_mine->Set_Name("install_mine");
		install_mine->Set_Tag("install_mine");
		install_mine->AddComponent(new Physics());
		install_mine->AddComponent(new Player());
		//install_mine->AddComponent(new Sprite(install_mine, "../sprite/mine_object.png", { m_owner->GetTransform().GetTranslation().x ,m_owner->GetTransform().GetTranslation().y - 150 }));
		install_mine->AddComponent(new Sprite(install_mine, "../Sprite/Item/mine.png", { random_position_x ,random_position_y }));
		//install_mine->AddComponent(new Sprite(install_mine, "../Sprite/Player/Item_Effect/mine_active.png", true, 4, 8, {random_position_x, random_position_y},
		//	{100.f, 100.f}, {255,255,255,255}, Sprite_Type::Item), "none", false);
		//install_mine->DeleteComponent(install_mine->GetComponentByTemplate<Hp_Bar>());
		install_mine->SetScale(2.f);
		install_mine->SetNeedCollision(true);
		Change_To_Normal_State();
		ObjectManager::GetObjectManager()->AddObject(install_mine);
	}

}

void Player::Func_Mine_Collided(float dt)
{
	srand(time(NULL));
	float random_velocity_x = rand() % 5 - 2;
	float random_velocity_y = rand() % 5 - 2;
	//m_owner->SetNeedCollision
	if (mine_timer > 0.0f)
	{
		velocity += {random_velocity_x, random_velocity_y};
		mine_timer -= dt;
	}
	else
	{
		velocity += {-velocity.x / 100, -velocity.y / 100};
		curr_state_additional = Char_State_Additional::None;
		//install_mine->SetDeadCondition(true);
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
void  Player::Set_Mine_Timer(float timer)
{
	mine_timer = timer;
}
float Player::Get_Mine_Timer()
{
	return mine_timer;
}

void Player::PlayerMovement(float max_velocity, float min_velocity)
{
	float LeftThumbStateX = gamepadManager->LeftStick_X();
	float LeftThumbStateY = gamepadManager->LeftStick_Y();


	if (m_owner->Get_Name() == "first")
	{
		if (LeftThumbStateY > 0)
		{
			if (LeftThumbStateY > 0 && LeftThumbStateX < 0)
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
			else if (LeftThumbStateY > 0 && LeftThumbStateX > 0)
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
		else if (LeftThumbStateX < 0)
		{
			if (LeftThumbStateX < 0 && LeftThumbStateY < 0)
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
		else if (LeftThumbStateY < 0)
		{
			if (LeftThumbStateY < 0 && LeftThumbStateX > 0)
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
		else if (LeftThumbStateX > 0)
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
	else if (m_owner->Get_Name() == "second")
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
				direction.x -= 0.07f;
				direction.y += 0.07f;
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
				direction.x += 0.07f;
				direction.y += 0.07f;
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
				direction.y += 0.1f;
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
				direction.x -= 0.07f;
				direction.y -= 0.07f;
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
				direction.x -= 0.1f;
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
				direction.x += 0.07f;
				direction.y -= 0.07f;
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
				direction.y -= 0.1f;
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
			direction.x += 0.1f;
		}
		else
		{
			velocity += {-velocity.x / 100, -velocity.y / 100};
		}
		float angle = RadianToDegree(angle_between({ 0,1 }, direction));
		if (direction.x >= 0)
		{
			angle *= -1;
		}
		m_owner->SetRotation(angle);
		direction = normalize(direction);

	}
	else if (m_owner->GetName() == "third")
	{
		if (input.Is_Key_Pressed(GLFW_KEY_UP))
		{
			if (input.Is_Key_Pressed(GLFW_KEY_UP) && input.Is_Key_Pressed(GLFW_KEY_LEFT))
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
				direction.x -= 0.07f;
				direction.y += 0.07f;
			}
			else if (input.Is_Key_Pressed(GLFW_KEY_UP) && input.Is_Key_Pressed(GLFW_KEY_RIGHT))
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
				direction.x += 0.07f;
				direction.y += 0.07f;
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
				direction.y += 0.1f;
			}
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
		{
			if (input.Is_Key_Pressed(GLFW_KEY_LEFT) && input.Is_Key_Pressed(GLFW_KEY_DOWN))
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
				direction.x -= 0.07f;
				direction.y -= 0.07f;
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
				direction.x -= 0.1f;
			}
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_DOWN))
		{
			if (input.Is_Key_Pressed(GLFW_KEY_DOWN) && input.Is_Key_Pressed(GLFW_KEY_RIGHT))
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
				direction.x += 0.07f;
				direction.y -= 0.07f;
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
				direction.y -= 0.1f;
			}
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
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
			direction.x += 0.1f;
		}
		else
		{
			velocity += {-velocity.x / 100, -velocity.y / 100};
		}
		float angle = RadianToDegree(angle_between({ 0,1 }, direction));
		if (direction.x >= 0)
		{
			angle *= -1;
		}
		m_owner->SetRotation(angle);
		direction = normalize(direction);
	}
	else if (m_owner->GetName() == "fourth")
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
}

void Player::SetPlayerVelocity(vector2 current_velocity)
{
	velocity = current_velocity;
}

vector2 Player::GetPlayerVelocity()
{
	return velocity;
}

vector2 Player::GetPlayerDirection()
{
	return direction;
}

void Player::UseItem()
{
	float RightTriggerState = gamepadManager->RightTrigger();

	if (m_owner->Get_Name() == "first")
	{
		if (RightTriggerState > 0 && belong_item == Item::Item_Kind::Dash)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();
			sound.Play(SOUND::Dash);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Dash));
		}
		if (RightTriggerState > 0 && belong_item == Item::Item_Kind::HP)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			sound.Play(SOUND::HP);
			Object* hp_bar = m_owner->Get_Belong_Object_By_Tag("hp_bar");
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(hp_bar, m_owner, Message_Kind::Item_Recover));
		}

		if (RightTriggerState > 0 && belong_item == Item::Item_Kind::Bulkup)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			sound.Play(SOUND::BulkUp);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Bulkup, 15.f));
		}

		if (RightTriggerState > 0 && belong_item == Item::Item_Kind::Throwing)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			m_owner->Change_Sprite(m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Throwing));
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Throwing, 0.f));
		}
		if (RightTriggerState > 0 && belong_item == Item::Item_Kind::Magnatic)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Magnetic));
		}
		if (RightTriggerState > 0 && belong_item == Item::Item_Kind::Time_Pause)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Timepause));
		}
		if (RightTriggerState > 0 && belong_item == Item::Item_Kind::Reverse_Moving)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Reverse));
		}
		if (RightTriggerState > 0 && belong_item == Item::Item_Kind::Missile)
		{
			Change_To_Normal_State();
			m_owner->Change_Sprite(m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Missile));
			Change_Weapon_Sprite(nullptr);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Missile));
		}
		if (RightTriggerState > 0 && belong_item == Item::Item_Kind::Mine)
		{
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Mine));
		}

	}
	else if (m_owner->Get_Name() == "second")
	{
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Dash)
		{
			Change_Weapon_Sprite(nullptr);
			sound.Play(SOUND::Dash);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Dash));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::HP)
		{
			Change_Weapon_Sprite(nullptr);
			sound.Play(SOUND::HP);
			Change_To_Normal_State();

			Object* hp_bar = m_owner->Get_Belong_Object_By_Tag("hp_bar");
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(hp_bar, m_owner, Message_Kind::Item_Recover));
		}

		if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Bulkup)
		{
			Change_Weapon_Sprite(nullptr);
			sound.Play(SOUND::BulkUp);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Bulkup, 5.f));
		}

		if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Throwing)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Throwing)->Set_Need_Update(true);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Throwing, 0.f));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Magnatic)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Magnetic));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Time_Pause)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Timepause));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Reverse_Moving)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Reverse));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Missile)
		{
			Change_To_Normal_State();

			m_owner->Change_Sprite(m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Missile));
			Change_Weapon_Sprite(nullptr);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Missile));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && belong_item == Item::Item_Kind::Mine)
		{
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Mine));
		}
	}
	else if (m_owner->Get_Name() == "third")
	{
		if (input.Is_Key_Pressed(GLFW_KEY_KP_7) && belong_item == Item::Item_Kind::Dash)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			sound.Play(SOUND::Dash);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Dash));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_KP_7) && belong_item == Item::Item_Kind::HP)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			sound.Play(SOUND::HP);
			Object* hp_bar = m_owner->Get_Belong_Object_By_Tag("hp_bar");
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(hp_bar, m_owner, Message_Kind::Item_Recover));
		}

		if (input.Is_Key_Pressed(GLFW_KEY_KP_7) && belong_item == Item::Item_Kind::Bulkup)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			sound.Play(SOUND::BulkUp);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Bulkup, 5.f));
		}

		if (input.Is_Key_Pressed(GLFW_KEY_KP_7) && belong_item == Item::Item_Kind::Throwing)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Throwing)->Set_Need_Update(true);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Throwing, 0.f));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_KP_7) && belong_item == Item::Item_Kind::Magnatic)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Magnetic));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_KP_7) && belong_item == Item::Item_Kind::Time_Pause)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Timepause));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_KP_7) && belong_item == Item::Item_Kind::Reverse_Moving)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Reverse));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_KP_7) && belong_item == Item::Item_Kind::Missile)
		{
			Change_To_Normal_State();

			m_owner->Change_Sprite(m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Missile));
			Change_Weapon_Sprite(nullptr);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Missile));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_KP_7) && belong_item == Item::Item_Kind::Mine)
		{
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Mine));
		}
	}
	else if (m_owner->Get_Name() == "fourth")
	{

		if (input.Is_Key_Pressed(GLFW_KEY_R) && belong_item == Item::Item_Kind::Dash)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			sound.Play(SOUND::Dash);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Dash));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_R) && belong_item == Item::Item_Kind::HP)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			sound.Play(SOUND::HP);
			Object* hp_bar = m_owner->Get_Belong_Object_By_Tag("hp_bar");
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(hp_bar, m_owner, Message_Kind::Item_Recover));
		}

		if (input.Is_Key_Pressed(GLFW_KEY_R) && belong_item == Item::Item_Kind::Bulkup)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			sound.Play(SOUND::BulkUp);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Bulkup, 5.f));
		}

		if (input.Is_Key_Pressed(GLFW_KEY_R) && belong_item == Item::Item_Kind::Throwing)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Throwing)->Set_Need_Update(true);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Throwing, 0.f));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_R) && belong_item == Item::Item_Kind::Magnatic)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Magnetic));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_R) && belong_item == Item::Item_Kind::Time_Pause)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Timepause));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_R) && belong_item == Item::Item_Kind::Reverse_Moving)
		{
			Change_Weapon_Sprite(nullptr);
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Reverse));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_R) && belong_item == Item::Item_Kind::Missile)
		{
			Change_To_Normal_State();

			m_owner->Change_Sprite(m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Missile));
			Change_Weapon_Sprite(nullptr);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Missile));
		}
		if (input.Is_Key_Pressed(GLFW_KEY_R) && belong_item == Item::Item_Kind::Mine)
		{
			Change_To_Normal_State();

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_owner, nullptr, Message_Kind::Item_Mine));
		}
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
	//last_sprite = m_owner->Get_Current_Sprite();
	Component* chubby = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Fat);
	Component* normal_sprite = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Normal);

	if (belong_item == Item::Item_Kind::None)
	{
		m_owner->Change_Sprite(normal_sprite);
	}
	else
	{
		m_owner->Change_Sprite(chubby);
	}
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

void Player::Change_Weapon_Sprite(Component* weapon_sprite)
{
	if (weapon_sprite != nullptr)
	{
		if (weapon_state != nullptr)
		{
			weapon_state->Set_Need_Update(false);
		}
		weapon_state = weapon_sprite;
		weapon_state->Set_Need_Update(true);
	}
	else
	{
		if (weapon_state != nullptr)
		{
			weapon_state->Set_Need_Update(false);
			weapon_state = nullptr;
		}
	}
}

void Player::Check_Current_Sprite_Status(float dt)
{
	Component* normal = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Normal);
	Component* speed2 = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Speed2);
	Component* speed3 = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Speed3);
	Component* chubby = m_owner->Find_Sprite_By_Type(Sprite_Type::Player_Fat);
	Component* curr = m_owner->Get_Current_Sprite();

	if (curr != normal && curr != speed2 && curr != speed3 && curr != chubby)
	{
		sprite_check_timer += dt;

		if (sprite_check_timer < 5.f)
		{

		}
	}

}

Player::Item_Use_Status Player::Get_Item_Used_Status()
{
	return item_used;
}

void Player::Set_Item_Used_Status(Item_Use_Status status)
{
	item_used = status;
}

void Player::Set_Audience(Object* obj)
{
	aud = obj;
}

Object* Player::Get_Audience()
{
	return aud;
}
