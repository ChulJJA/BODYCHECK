/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Collision.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Collision
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Collision.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Engine.hpp"
#include "Object.h"
#include "Player_Ui.h"
#include "Component_Hpbar.h"
#include "Component_Text.h"
#include "Message.h"
#include "Damage_Calculator.h"
#include "Component_Ui.h"
#include "Component_Lock.h"
#include "Message_Manager.h"
#include "Referee.h"
#include "Component_Missile.h"
#include "Component_Throwing.h"
#include "View.h"

void Msg_Func_Collision::Init()
{
	//
}

void Msg_Func_Collision::Update(float dt)
{
	if (m_target->Get_Tag() == "item" && m_from->Get_Tag() == "player")
	{
		Component* target_current_sprite = m_target->Get_Current_Sprite();
		Component* target_item_sprite = m_target->Find_Sprite_By_Type(Sprite_Type::Item);

		if (target_current_sprite == target_item_sprite)
		{
			Player_Get_Item(m_from, m_target);
		}
	}
	else if (m_from->Get_Tag() == "item" && m_target->Get_Tag() == "player")
	{
		Component* from_current_sprite = m_from->Get_Current_Sprite();
		Component* from_item_sprite = m_from->Find_Sprite_By_Type(Sprite_Type::Item);

		if (from_current_sprite == from_item_sprite)
		{
			Player_Get_Item(m_target, m_from);
		}
	}

	else if (m_target->Get_Tag() == "throwing" && m_from->Get_Tag() == "player")
	{
		physics.KnockBack_Missile(m_from, m_target);

		if (m_target->GetName() == "missile" || m_target->GetName() == "plask")
		{
			if (m_target->GetComponentByTemplate<Missile>()->Get_From_Obj() != m_from)
			{

				m_target->SetDeadCondition(true);
				Player* player_info_from = m_from->GetComponentByTemplate<Player>();

				if (m_target->GetName() == "missile")
				{
					Object* hp_bar = m_from->Get_Belong_Object_By_Tag("hp_bar");

					if (hp_bar != nullptr)
					{
						Hp_Bar* info_hp_bar = hp_bar->GetComponentByTemplate<Hp_Bar>();

						if (info_hp_bar != nullptr)
						{
							if (player_info_from->Get_Item_Used_Status() == Player::Item_Use_Status::None &&
								info_hp_bar->Get_Hp_Bar_State() == Hp_Bar::Hp_Bar_State::None)
							{
								sound.Play(SOUND::Missile);

								info_hp_bar->Decrease(0.5f);
								m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Crying));
								info_hp_bar->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);
								info_hp_bar->Set_Timer(1.f);
							}
						}
					}
				}
				else
				{
					sound.Play(SOUND::Plask);
					Player* player_info_target = m_from->GetComponentByTemplate<Player>();
					FMOD_BOOL isBGMPlaying;
					FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(sound.currentBGM)], &isBGMPlaying);
					if (!isBGMPlaying)
					{
						sound.Play(sound.currentBGM);
					}
					player_info_target->Set_Char_State(Player::Char_State::Reverse_Moving);
					m_from->Change_Sprite(m_from->Find_Sprite_By_Type(Sprite_Type::Player_Reverse_Moving));
				}
			}

		}
		else
		{
			if (m_target->GetComponentByTemplate<Throwing>()->Get_Throwing_Obj() != m_from)
			{
				m_target->SetDeadCondition(true);
				Player* player_info_from = m_from->GetComponentByTemplate<Player>();
				Object* hp_bar = m_from->Get_Belong_Object_By_Tag("hp_bar");

				if (hp_bar != nullptr)
				{
					Hp_Bar* info_hp_bar = hp_bar->GetComponentByTemplate<Hp_Bar>();

					if (info_hp_bar != nullptr)
					{
						if (player_info_from->Get_Item_Used_Status() == Player::Item_Use_Status::None &&
							info_hp_bar->Get_Hp_Bar_State() == Hp_Bar::Hp_Bar_State::None)
						{
							sound.Play(SOUND::ThrowingHit);

							info_hp_bar->Decrease(0.5f);
							m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Crying));
							info_hp_bar->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);
							info_hp_bar->Set_Timer(1.f);
						}
					}
				}
			}
		}
	}
	else if (m_from->Get_Tag() == "throwing" && m_target->Get_Tag() == "player")
	{
		physics.KnockBack_Missile(m_target, m_from);

		if (m_from->GetName() == "missile" || m_from->GetName() == "plask")
		{
			if (m_from->GetComponentByTemplate<Missile>()->Get_From_Obj() != m_target)
			{
				m_from->SetDeadCondition(true);

				if (m_from->GetName() == "missile")
				{
					Player* player_info_target = m_target->GetComponentByTemplate<Player>();
					Object* hp_bar = m_target->Get_Belong_Object_By_Tag("hp_bar");

					if (hp_bar != nullptr)
					{
						Hp_Bar* info_hp_bar = hp_bar->GetComponentByTemplate<Hp_Bar>();
						if (info_hp_bar != nullptr)
						{
							if (player_info_target->Get_Item_Used_Status() == Player::Item_Use_Status::None &&
								info_hp_bar->Get_Hp_Bar_State() == Hp_Bar::Hp_Bar_State::None)
							{
								sound.Play(SOUND::Missile);
								info_hp_bar->Decrease(0.5f);
								m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Crying));
								info_hp_bar->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);
								info_hp_bar->Set_Timer(1.f);
							}
						}
					}
				}
				else
				{
					sound.Play(SOUND::Plask);
					Player* player_info_target = m_target->GetComponentByTemplate<Player>();
					if (player_info_target->Get_Char_State() == Player::Char_State::Time_Pause)
					{
						FMOD_BOOL isBGMPlaying;
						FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(sound.currentBGM)], &isBGMPlaying);
						if(!isBGMPlaying)
						{
							sound.Play(sound.currentBGM);
						}
					}
					player_info_target->Set_Char_State(Player::Char_State::Reverse_Moving);
					m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Reverse_Moving));
				}
			}
		}
		else
		{
			if (m_from->GetComponentByTemplate<Throwing>()->Get_Throwing_Obj() != m_target)
			{
				m_from->SetDeadCondition(true);
				Player* player_info_target = m_target->GetComponentByTemplate<Player>();
				Object* hp_bar = m_target->Get_Belong_Object_By_Tag("hp_bar");

				if (hp_bar != nullptr)
				{
					Hp_Bar* info_hp_bar = hp_bar->GetComponentByTemplate<Hp_Bar>();

					if (info_hp_bar != nullptr)
					{
						if (player_info_target->Get_Item_Used_Status() == Player::Item_Use_Status::None &&
							info_hp_bar->Get_Hp_Bar_State() == Hp_Bar::Hp_Bar_State::None)
						{
							sound.Play(SOUND::ThrowingHit);

							info_hp_bar->Decrease(0.5f);
							m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Crying));
							info_hp_bar->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);
							info_hp_bar->Set_Timer(1.f);
						}
					}
				}

			}
		}

	}
	else if (m_from->Get_Tag() == "throwing" && m_target->Get_Tag() == "throwing")
	{
	}
	else if (m_from->Get_Tag() == "lock" && m_target->Get_Tag() == "player")
	{
		Player_And_Lock_Collision(m_target, m_from);
	}
	else if (m_target->Get_Tag() == "lock" && m_from->Get_Tag() == "player")
	{
		Player_And_Lock_Collision(m_from, m_target);
	}
	else if (m_from->Get_Tag() == "install_mine" && m_target->Get_Tag() == "player")
	{
		Player_And_Mine_Collision(m_target, m_from);
		sound.Play(SOUND::MineBomb);

	}
	else if (m_target->Get_Tag() == "install_mine" && m_from->Get_Tag() == "player")
	{
		Player_And_Mine_Collision(m_from, m_target);
		sound.Play(SOUND::MineBomb);

	}
	else if (m_from->Get_Tag() == "player" && m_target->Get_Tag() == "player")
	{
		sound.Play(SOUND::Crack);
		Player_And_Player_Collision();
		Graphic::GetGraphic()->Get_View().Active_Screen_Shake(10.f);
		const float speed_mag1 = magnitude_squared(m_from->GetComponentByTemplate<Player>()->GetPlayerVelocity());
		const float speed_mag2 = magnitude_squared(m_target->GetComponentByTemplate<Player>()->GetPlayerVelocity());
		if (speed_mag1 + speed_mag2 > 300.0f)
		{
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(m_target, nullptr, Message_Kind::Particle_Collision, .5f));
		}

		Player* player_from_info = m_from->GetComponentByTemplate<Player>();
		Player* player_target_info = m_target->GetComponentByTemplate<Player>();

		if (player_target_info->Get_Item_Used_Status() != Player::Item_Use_Status::Magnet &&
			player_from_info->Get_Item_Used_Status() != Player::Item_Use_Status::Magnet)
		{
			physics.KnockBack(m_from, m_target);
		}

		if (player_from_info->Get_Char_State() == Player::Char_State::Lock_Ing)
		{
			Object* pointer = player_from_info->Get_Locking();

			if (pointer != nullptr)
			{
				pointer->SetDeadCondition(true);
				Object* pointer_target = pointer->GetComponentByTemplate<Lock>()->Get_Locking_Target();
				if (pointer_target != nullptr)
				{
					pointer_target->Change_Sprite(pointer_target->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
				}

				player_from_info->Change_To_Normal_State();
			}
		}
		else if (player_target_info->Get_Char_State() == Player::Char_State::Lock_Ing)
		{
			Object* pointer = player_target_info->Get_Locking();
			if (pointer != nullptr)
			{
				pointer->SetDeadCondition(true);
				Object* pointer_target = pointer->GetComponentByTemplate<Lock>()->Get_Locking_Target();
				if (pointer_target != nullptr)
				{
					pointer_target->Change_Sprite(pointer_target->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
				}

				player_target_info->Change_To_Normal_State();
			}
		}

		if (player_from_info->Get_Item_Used_Status() == Player::Item_Use_Status::Magnet)
		{
			if (player_from_info->Get_Locking_Result() == m_target)
			{
				player_from_info->Change_To_Normal_State();
				player_from_info->Set_Item_Used_Status(Player::Item_Use_Status::None);
			}
		}
		else if (player_target_info->Get_Item_Used_Status() == Player::Item_Use_Status::Magnet)
		{
			if (player_target_info->Get_Locking_Result() == m_from)
			{
				player_target_info->Change_To_Normal_State();
				player_target_info->Set_Item_Used_Status(Player::Item_Use_Status::None);
			}
		}

		if (player_target_info->Get_Char_State() == Player::Char_State::Missile_Ready)
		{
			player_target_info->Change_To_Normal_State();
		}
		else if (player_from_info->Get_Char_State() == Player::Char_State::Missile_Ready)
		{
			player_from_info->Change_To_Normal_State();
		}


		if (player_from_info->Get_Char_State() == Player::Char_State::Time_Pause)
		{
			FMOD_BOOL isBgm;
			FMOD_BOOL isStopClocking;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(sound.currentBGM)], &isBgm);
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::ClockTicking)], &isStopClocking);
			if(isStopClocking)
			{
				sound.Stop(SOUND::ClockTicking);
			}

			if (!isBgm)
			{
				sound.Play(sound.currentBGM);
			}
			player_from_info->Change_To_Normal_State();

		}
		else if (player_target_info->Get_Char_State() == Player::Char_State::Time_Pause)
		{
			FMOD_BOOL isBgm;
			FMOD_BOOL isStopClocking;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(sound.currentBGM)], &isBgm);
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::ClockTicking)], &isStopClocking);
			if (isStopClocking)
			{
				sound.Stop(SOUND::ClockTicking);
			}

			if (!isBgm)
			{
				sound.Play(sound.currentBGM);
			}

			player_target_info->Change_To_Normal_State();
		}

		if (player_from_info->Get_Char_State_Additional() == Player::Char_State_Additional::Get_mine)
		{
			player_from_info->Change_To_Normal_State();

		}
		else if (player_target_info->Get_Char_State_Additional() == Player::Char_State_Additional::Get_mine)
		{
			player_target_info->Change_To_Normal_State();

		}
	}
	msg->Set_Should_Delete(true);
}

void Msg_Func_Collision::Player_Get_Item(Object* player, Object* item)
{
	sound.Play(SOUND::Item);
	Referee::Get_Referee()->Decre_Curr_Item_Field_Num();
	item->Change_Sprite(item->Find_Sprite_By_Type(Sprite_Type::Item_Eateffect));
	Message_Manager::Get_Message_Manager()->Save_Message(new Message(item, nullptr, Message_Kind::Delete_Object, 0.5f));

	Player* player_info = player->GetComponentByTemplate<Player>();
	PLAYER_UI* ui_info = player_info->Get_Ui();
	const Item::Item_Kind item_kind = item->GetComponentByTemplate<Item>()->Get_Kind();

	if (player_info->Get_Char_State() == Player::Char_State::None && player_info->Get_Char_State_Additional() != Player::Char_State_Additional::Get_mine)
	{

		if (item_kind == Item::Item_Kind::Dash)
		{
			player_info->Set_Item_State(Item::Item_Kind::Dash);
			ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Dash);
		}
		else if (item_kind == Item::Item_Kind::HP)
		{
			player_info->Set_Item_State(Item::Item_Kind::HP);
			ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Hp);
		}
		else if (item_kind == Item::Item_Kind::Bulkup)
		{
			player_info->Set_Item_State(Item::Item_Kind::Bulkup);
			ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Bulkup);
		}
		else if (item_kind == Item::Item_Kind::Throwing)
		{
			player_info->Set_Item_State(Item::Item_Kind::Throwing);
			ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Throwing);
		}

		else if (item_kind == Item::Item_Kind::Magnatic)
		{
			player_info->Set_Item_State(Item::Item_Kind::Magnatic);
			ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Magnatic);
		}

		else if (item_kind == Item::Item_Kind::Time_Pause)
		{
			player_info->Set_Item_State(Item::Item_Kind::Time_Pause);
			ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Time_Pause);
		}

		else if (item_kind == Item::Item_Kind::Reverse_Moving)
		{
			player_info->Set_Item_State(Item::Item_Kind::Reverse_Moving);
			ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Reverse_Moving);
		}
		else if (item_kind == Item::Item_Kind::Missile)
		{
			player_info->Set_Item_State(Item::Item_Kind::Missile);
			ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Missile);
		}
		else if (item->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Mine)
		{
			player_info->Set_Item_State(Item::Item_Kind::Mine);
			ui_info->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Get, Ui::Ui_Status_Obj::Item_Mine);
		}

		player->Change_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Fat));
	}

}

void Msg_Func_Collision::Player_And_Player_Collision()
{
	std::pair<float, float> dmg_set = DamageCalculator(m_target, m_from);

	Player* info_player_target = m_target->GetComponentByTemplate<Player>();
	Player* info_player_from = m_from->GetComponentByTemplate<Player>();

	if (info_player_from != nullptr && info_player_target != nullptr)
	{
		info_player_target->Get_Regeneration_Timer() = 0.f;
		info_player_from->Get_Regeneration_Timer() = 0.f;


		if (m_from->GetComponentByTemplate<Player>() != nullptr)
		{
			m_target->Set_Hitted_By(m_from);
		}

		if (m_target->GetComponentByTemplate<Player>() != nullptr)
		{
			m_from->Set_Hitted_By(m_target);
		}

		Object* target_hp_bar = m_target->Get_Belong_Object_By_Tag("hp_bar");
		Object* from_hp_bar = m_from->Get_Belong_Object_By_Tag("hp_bar");

		if (target_hp_bar != nullptr && from_hp_bar != nullptr)
		{
			Hp_Bar* hp_bar_info_target = target_hp_bar->GetComponentByTemplate<Hp_Bar>();
			Hp_Bar* hp_bar_info_from = from_hp_bar->GetComponentByTemplate<Hp_Bar>();

			if (hp_bar_info_from != nullptr && hp_bar_info_target != nullptr)
			{
				if (info_player_target->Get_Item_Used_Status() == Player::Item_Use_Status::None &&
					hp_bar_info_target->Get_Hp_Bar_State() == Hp_Bar::Hp_Bar_State::None)
				{
					hp_bar_info_target->Decrease(dmg_set.first / 20);

					if (info_player_target->Get_Char_State() != Player::Char_State::Reverse_Moving)
					{
						m_target->Change_Sprite(m_target->Find_Sprite_By_Type(Sprite_Type::Player_Crying));
						hp_bar_info_target->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);
						hp_bar_info_target->Set_Timer(1.f);
					}
				}
				if (info_player_from->Get_Item_Used_Status() == Player::Item_Use_Status::None &&
					hp_bar_info_from->Get_Hp_Bar_State() == Hp_Bar::Hp_Bar_State::None)
				{
					hp_bar_info_from->Decrease(dmg_set.second / 20);

					if (info_player_from->Get_Char_State() != Player::Char_State::Reverse_Moving)
					{
						m_from->Change_Sprite(m_from->Find_Sprite_By_Type(Sprite_Type::Player_Crying));
						hp_bar_info_from->Set_Hp_Bar_State(Hp_Bar::Hp_Bar_State::Damaging);
						hp_bar_info_from->Set_Timer(1.f);
					}
				}
			}
		}
		else
		{

		}

	}
}

void Msg_Func_Collision::Player_And_Lock_Collision(Object* player, Object* lock)
{
	Lock* info_lock = lock->GetComponentByTemplate<Lock>();

	if (lock->IsDead() == false)
	{
		player->Change_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Locking));
		info_lock->Set_Locking_Target(player);
	}
}

void Msg_Func_Collision::Player_And_Mine_Collision(Object* player, Object* mine)
{
	Player* get_player = player->GetComponentByTemplate<Player>();
	get_player->Set_Char_State_Additional(Player::Char_State_Additional::Get_mine);
	get_player->Set_Mine_Timer(5.f);
	mine->SetDeadCondition(true);
	player->Change_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Locking));
}