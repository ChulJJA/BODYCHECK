/*
 * Author		:Sangmin Kim
 * File			:Referee.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Referee
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Referee.h"
#include "Component_Player.h"
#include "Component_Sprite.h"
#include "ObjectManager.h"
#include "Graphic.h"
#include "Component_Item.h"
#include "Player_Ui.h"
#include "Engine.hpp"
#include "StateManager.h"
#include "Component_Text.h"
#include "Application.hpp"
#include "State.h"
#include "Component_Missile.h"
#include "UsefulTools.hpp"
#include "Physics.h"
#include "Message_Manager.h"
#include "Input.h"

extern int life;


Referee* Referee::referee = nullptr;
StateManager* state_manager = nullptr;
Application* app = nullptr;

void Referee::Set_Win_State()
{
	second_win = new Object();
	second_win->Set_Name("second_win");
	second_win->AddComponent(new Sprite(second_win, "../Sprite/pen_red2_win.png", true, 4, 8, { 0.f,0.f }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "win", true);
	second_win->GetTransform().SetScale({ 37.f, 21.f });


	third_win = new Object();
	third_win->Set_Name("third_win");
	third_win->AddComponent(new Sprite(third_win, "../Sprite/pen_blue2_win.png", true, 4, 8, { 0.f,0.f }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "win", true);
	third_win->GetTransform().SetScale({ 37.f, 21.f });
}

void Referee::Set_Timer()
{
	timer_1 = new Object();
	timer_2 = new Object();
	timer_3 = new Object();
	timer_erase = new Object();
	timer_start = new Object();

	timer_1->Set_Tag("timer");
	timer_2->Set_Tag("timer");
	timer_3->Set_Tag("timer");
	timer_erase->Set_Tag("timer");
	timer_start->Set_Tag("timer");
	timer_1->Set_Name("timer1");
	timer_2->Set_Name("timer2");
	timer_3->Set_Name("timer3");
	timer_erase->Set_Name("timer_erase");
	timer_start->Set_Name("timer_start");

	vector2 pos{ 0.f, 0.f };
	timer_start->AddComponent(new Sprite(timer_start, "../Sprite/UI/timer_start.png", pos, false, Sprite_Type::None), "timer_start", true);
	timer_start->Set_Need_To_Update(false);
	timer_1->AddComponent(new Sprite(timer_1, "../Sprite/UI/timer1.png", pos, false, Sprite_Type::Num_1), "num1", true);
	timer_1->Set_Need_To_Update(false);
	timer_2->AddComponent(new Sprite(timer_2, "../Sprite/UI/timer2.png", pos, false, Sprite_Type::Num_2), "num2", true);
	timer_2->Set_Need_To_Update(false);
	timer_3->AddComponent(new Sprite(timer_3, "../Sprite/UI/timer3.png", pos, false, Sprite_Type::Num_3), "num3", true);
	timer_3->Set_Need_To_Update(true);

	timer_erase->AddComponent(new Sprite(timer_erase, "../Sprite/UI/timer_erase.png", true, 3, 18, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "timer_erase", true);
	timer_erase->Set_Need_To_Update(false);

	vector2 scale{ 9.f, 7.f };
	timer_1->SetScale(scale);
	timer_2->SetScale(scale);
	timer_3->SetScale(scale);
	timer_erase->SetScale(scale);
	timer_start->SetScale(scale);

	ObjectManager::GetObjectManager()->AddObject(timer_1);
	ObjectManager::GetObjectManager()->AddObject(timer_2);
	ObjectManager::GetObjectManager()->AddObject(timer_3);
	ObjectManager::GetObjectManager()->AddObject(timer_erase);
	ObjectManager::GetObjectManager()->AddObject(timer_start);
}

void Referee::Reset_Variables()
{
	player_second_respawn_timer = 3.0f;
	player_first_respawn_timer = 3.0f;
	player_third_respawn_timer = 3.0f;
	player_fourth_respawn_timer = 3.0f;
	player_sec_temp = nullptr;
	player_first_temp = nullptr;
	player_third_temp = nullptr;
	player_fourth_temp = nullptr;
	missile_saving = nullptr;
	item_respawn_timer = 3.0f;
	missile_num = 20;
	missile_count = 0;
	win_player = nullptr;
	win = false;
	player_dance_time = 0.f;
	playOnce = false;
	change_once = false;
	aud_is_cheerup_mode_finish = false;
	audience_vec.clear();
	curr_field_num = 0;
	is_cheerup_mode = false;
	Reset_Item_Variables();
}

void Referee::Reset_Item_Variables()
{
	item_dash = nullptr;
	item_heal = nullptr;
	item_bulk_up = nullptr;
	item_throwing = nullptr;
	item_magnetic = nullptr;
	item_time_pause = nullptr;
	item_reverse_moving = nullptr;
	item_missile = nullptr;
	item_mine = nullptr;
	item_num = 1;
	item_num_heal = item_num;
	item_num_dash = item_num;
	item_num_bulk_up = item_num;
	item_num_throwing = item_num;
	item_num_magnetic = item_num;
	item_num_time_pause = item_num;
	item_num_reverse_moving = item_num;
	item_num_missile = item_num;
	item_num_mine = item_num;
	total_item_num = item_num * 8;
}

void Referee::Set_Sec_Player_Info(vector2 pos, vector2 scale, std::string path)
{
	player_sec_pos = pos;
	player_sec_scale = scale;
	player_sec_sprite_path = path;
}

void Referee::Set_Third_Player_Info(vector2 pos, vector2 scale, std::string path)
{
	player_third_pos = pos;
	player_third_scale = scale;
	player_third_sprite_path = path;
}

void Referee::Separate_Player()
{
	vector2& sec_pos = curr_sec_player->GetTransform().GetTranslation_Reference();
	vector2& third_pos = curr_third_player->GetTransform().GetTranslation_Reference();

	float distance = distance_between(sec_pos, third_pos);

	if (distance < 50.f)
	{
		float offset = 100.f;
		if (sec_pos.x > third_pos.x)
		{
			sec_pos.x += offset;
			third_pos.x -= offset;
		}
		else
		{
			sec_pos.x -= offset;
			third_pos.x += offset;
		}

		if (sec_pos.y > third_pos.y)
		{
			sec_pos.y += offset;
			third_pos.y -= offset;
		}
		else
		{
			sec_pos.y -= offset;
			third_pos.y += offset;
		}
	}
}

Referee::Referee()
{


	state_manager = StateManager::GetStateManager();
	if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Game)
	{
		int total = 1;
		player_first_life = total;
		player_sec_life = total;
		player_third_life = total;
		player_fourth_life = total;
		total_life_count = player_first_life + player_sec_life + player_third_life + player_fourth_life;
		total_life_count += 4;
	}
	else if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Tutorial)
	{
		player_sec_life = 1;
		player_third_life = 1;
		total_life_count = player_sec_life + player_third_life;
	}
}

Referee* Referee::Get_Referee()
{
	if (referee == nullptr)
	{
		referee = new Referee();
	}
	return referee;
}

void Referee::Init()
{
	Clear_Referee();
	Reset_Variables();

	state_manager = StateManager::GetStateManager();
	if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Game)
	{
		int total = life;
		player_sec_life = total;
		player_third_life = total;
		total_life_count = player_sec_life + player_third_life ;
		total_life_count += 2;
	}
	else if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Tutorial)
	{
		player_sec_life = 1;
		player_third_life = 1;
		total_life_count = player_sec_life + player_third_life;
	}

	stage_statements.clear();
	missile_saving = new Object * [missile_num];

	for (int i = 0; i < missile_num; i++)
	{
		missile_saving[i] = new Object();
		missile_saving[i]->Set_Name("missile");
		missile_saving[i]->Set_Tag("throwing");
		missile_saving[i]->SetNeedCollision(true);
		missile_saving[i]->AddComponent(new Sprite(missile_saving[i], "../sprite/Item/missiles.png", true, 3, 8, { 0.f,0.f },
			{ 100.f,100.f }, { 255,255,255,255 }), "missile");
		missile_saving[i]->AddComponent(new Physics);
		missile_saving[i]->AddComponent(new Missile);
		missile_saving[i]->SetScale(2.f);
		missile_saving[i]->Set_Current_Sprite(missile_saving[i]->Find_Sprite_By_Name("missile"));
	}

	SetPlayerTemp();
	SetItem();
	Set_Win_State();
	Set_Kill_State();
	Set_Timer();

	playOnce = false;
}

void Referee::Update(float dt)
{
	if (!stage_statements.empty())
	{
		for (auto i : stage_statements)
		{
			Respawn_Player(i, dt);
		}
	}
	
	if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Game && win == false)
	{
		Respawn_Item(dt);
	}
	Win(dt);

	if (total_item_num <= 0)
	{
		Reset_Item_Variables();
		SetItem();
	}
	Separate_Player();
}

void Referee::Delete()
{
}

void Referee::Clear_Referee()
{
	if (missile_saving != nullptr)
	{
		for (int i = 0; i < missile_num; ++i)
		{
			delete missile_saving[i];
		}
	}

	if (player_sec_temp != nullptr)
	{
		for (int i = 0; i < player_sec_life; ++i)
		{
			delete player_sec_temp[i];
		}
	}
	if (player_first_temp != nullptr)
	{
		for (int i = 0; i < player_first_life; ++i)
		{
			delete player_first_temp[i];
		}
	}
	if (player_third_temp != nullptr)
	{
		for (int i = 0; i < player_third_life; ++i)
		{
			delete player_third_temp[i];
		}
	}
	if (player_fourth_temp != nullptr)
	{
		for (int i = 0; i < player_fourth_life; ++i)
		{
			delete player_fourth_temp[i];
		}
	}
	if (item_dash != nullptr)
	{
		for (int i = 0; i < item_num_dash; ++i)
		{
			delete item_dash[i];
		}
	}
	if (item_heal != nullptr)
	{
		for (int i = 0; i < item_num_heal; ++i)
		{
			delete item_heal[i];
		}
	}
	if (item_bulk_up != nullptr)
	{
		for (int i = 0; i < item_num_bulk_up; ++i)
		{
			delete item_bulk_up[i];
		}
	}
	if (item_throwing != nullptr)
	{
		for (int i = 0; i < item_num_throwing; ++i)
		{
			delete item_throwing[i];
		}
	}
	if (item_magnetic != nullptr)
	{
		for (int i = 0; i < item_num_magnetic; ++i)
		{
			delete item_magnetic[i];
		}
	}
	if (item_time_pause != nullptr)
	{
		for (int i = 0; i < item_num_time_pause; ++i)
		{
			delete item_time_pause[i];
		}
	}
	if (item_reverse_moving != nullptr)
	{
		for (int i = 0; i < item_num_reverse_moving; ++i)
		{
			delete item_reverse_moving[i];
		}
	}
	if (item_missile != nullptr)
	{
		for (int i = 0; i < item_num_missile; ++i)
		{
			delete item_missile[i];
		}
	}
	if (item_mine != nullptr)
	{
		for (int i = 0; i < item_num_mine; ++i)
		{
			delete item_mine[i];
		}
	}

	if (timer_1 != nullptr)
	{
		timer_1 = nullptr;
		timer_2 = nullptr;
		timer_3 = nullptr;
		timer_erase = nullptr;
		timer_start = nullptr;
	}

}

Object* Referee::Make_Player_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag, Object* text, vector2 scale)
{
	std::string path_to_player_state = "../Sprite/Player/State/";
	std::string path_to_player_item_effect = "../Sprite/Player/Item_Effect/";

	std::string sprite_path_normal = path_to_player_state;
	std::string sprite_path_lock = path_to_player_state;
	std::string sprite_path_crying = path_to_player_state;
	std::string sprite_path_die = path_to_player_state;
	std::string sprite_path_paused = path_to_player_state;
	std::string sprite_path_speed2 = path_to_player_state;
	std::string sprite_path_speed3 = path_to_player_state;
	std::string sprite_path_fat = path_to_player_state;
	std::string sprite_path_spawn = path_to_player_state;

	std::string sprite_path_reverse_moving_pen = path_to_player_item_effect;
	std::string sprite_path_ready = path_to_player_item_effect;
	std::string sprite_path_heal_effect = path_to_player_item_effect;
	std::string sprite_path_throwing_effect = path_to_player_item_effect;
	std::string sprite_path_missile_effect = path_to_player_item_effect;
	std::string sprite_path_bulkup_used = path_to_player_item_effect;
	std::string sprite_path_ready_bulkup = path_to_player_item_effect;
	std::string sprite_path_magnet_aiming = path_to_player_item_effect;
	std::string sprite_path_magnet_chasing = path_to_player_item_effect;
	std::string sprite_path_dash_effect = path_to_player_item_effect;
	std::string sprite_path_timestop_effect = path_to_player_item_effect;
	std::string sprite_path_dance = path_to_player_state;

	{
		sprite_path_normal += sprite_path + ".png";
		sprite_path_lock += sprite_path + "_lock.png";
		sprite_path_crying += sprite_path + "_hit.png";
		sprite_path_die += sprite_path + "_die.png";
		sprite_path_paused += sprite_path + "_paused.png";
		sprite_path_speed2 += sprite_path + "_speed2.png";
		sprite_path_speed3 += sprite_path + "_speed3.png";
		sprite_path_fat += sprite_path + "_fat.png";
		sprite_path_spawn += sprite_path + "_spawn.png";
		sprite_path_dance += sprite_path + "_dance.png";
	}

	{
		sprite_path_reverse_moving_pen += sprite_path + "_reverse.png";
		sprite_path_ready += "loadingscene.png";
		sprite_path_heal_effect += "heal_effect.png";
		sprite_path_ready_bulkup += sprite_path + "_bulkupready.png";
		sprite_path_bulkup_used += sprite_path + "_bulkup.png";
		sprite_path_throwing_effect += "effect_throwing.png";
		sprite_path_missile_effect += sprite_path + "_missile_ready.png";
		sprite_path_magnet_aiming += sprite_path + "_magnet_aiming.png";
		sprite_path_magnet_chasing += sprite_path + "_chasing.png";
		sprite_path_dash_effect += sprite_path + "_dash_effect.png";
		sprite_path_timestop_effect += sprite_path + "_timestop.png";

	}
	Object* player = new Object();
	player->Set_Name(name);
	player->Set_Tag(tag);
	player->SetTranslation(pos);
	player->AddComponent(new Player(false), "player", false);

	bool is_debug_mode;
#if _DEBUG
	is_debug_mode = true;
#else
	is_debug_mode = false;
#endif

	player->AddComponent(new Sprite(player, sprite_path_normal.c_str(), true, 3, 6, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Normal, is_debug_mode), "normal", false);

	player->AddComponent(new Sprite(player, sprite_path_spawn.c_str(), true, 37, 9.25, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Spawn), "spawn", true);

	player->AddComponent(new Sprite(player, sprite_path_speed2.c_str(), true, 3, 24, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Speed2, is_debug_mode), "speed2", false);

	player->AddComponent(new Sprite(player, sprite_path_speed3.c_str(), true, 3, 48, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Speed3, is_debug_mode), "speed3", false);

	player->AddComponent(new Sprite(player, sprite_path_lock.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Locking), "lock", false);

	player->AddComponent(new Sprite(player, sprite_path_reverse_moving_pen.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Reverse_Moving), "reverse", false);

	player->AddComponent(new Sprite(player, sprite_path_ready.c_str(), pos, false, Sprite_Type::Player_Ready), "ready", false);

	player->AddComponent(new Sprite(player, sprite_path_timestop_effect.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Effect_Timestop), "time", false);

	player->AddComponent(new Sprite(player, sprite_path_die.c_str(), true, 8, 16, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Die, is_debug_mode), "die", false);

	player->AddComponent(new Sprite(player, sprite_path_crying.c_str(), true, 2, 4, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Crying, is_debug_mode), "crying", false);

	player->AddComponent(new Sprite(player, sprite_path_fat.c_str(), true, 3, 9, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Fat, is_debug_mode), "fat", false);

	player->AddComponent(new Sprite(player, sprite_path_paused.c_str(), pos, false, Sprite_Type::Player_Paused, { 100.f, 100.f }), "paused", false);

	player->AddComponent(new Sprite(player, sprite_path_ready_bulkup.c_str(), true, 4, 12, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Effect_Bulkp), "effect_bulkup", false);

	player->AddComponent(new Sprite(player, sprite_path_bulkup_used.c_str(), true, 3, 9, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Bulkup_Used), "effect_bulkup", false);

	player->AddComponent(new Sprite(player, sprite_path_heal_effect.c_str(), true, 6, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Heal), "effect_heal", false);

	player->AddComponent(new Sprite(player, sprite_path_throwing_effect.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Throwing), "effect_throwing", false);

	player->AddComponent(new Sprite(player, sprite_path_missile_effect.c_str(), true, 8, 16, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Missile), "effect_missile", false);

	player->AddComponent(new Sprite(player, sprite_path_magnet_aiming.c_str(), true, 4, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Aiming), "aiming", false);

	player->AddComponent(new Sprite(player, sprite_path_magnet_chasing.c_str(), true, 2, 16, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Chasing), "chasing", false);

	player->AddComponent(new Sprite(player, sprite_path_dash_effect.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Dash), "effect_dash", false);

	player->AddComponent(new Sprite(player, sprite_path_dance.c_str(), true, 15, 7, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Dance), "dance", false);

	player->AddComponent(new Physics(true), "physics");

	player->Set_Current_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Spawn));
	player->SetScale(scale);
	player->Set_Dmg_Text(text);
	player->SetNeedCollision(false);


	if (name == "second")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_red");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}
	else if (name == "third")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_blue");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}


	return player;
}

Object* Referee::Make_Item_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag,
	Item::Item_Kind kind)
{
	Object* item = new Object();
	std::string eat_effect = "../Sprite/Item/item_eateffect.png";
	std::string spawn_effect = "../Sprite/Item/item_spawn.png";

	item->AddComponent(new Sprite(item, spawn_effect.c_str(), true, 10, 10, pos, { 200.f,200.f },
		{ 255,255,255,255 }, Sprite_Type::Item_Spawn_Effect), "item_spawn", true);

	item->AddComponent(new Sprite(item, sprite_path.c_str(), true, 6, 12, pos, { 200.f,200.f },
		{ 255,255,255,255 }, Sprite_Type::Item), "item", false);

	item->AddComponent(new Sprite(item, eat_effect.c_str(), true, 3, 12, pos, { 200.f,200.f },
		{ 255,255,255,255 }, Sprite_Type::Item_Eateffect), "item_eat", false);

	item->AddComponent(new Item());
	item->AddComponent(new Physics());
	item->Set_Name(name);
	item->Set_Tag(tag);
	item->SetTranslation(pos);
	item->GetComponentByTemplate<Item>()->Set_Kind(kind);
	item->SetNeedCollision(true);
	item->SetScale(1.5f);
	total_item.push_back(item);

	return item;
}

void Referee::Respawn_Player(Stage_Statement state, float dt)
{
	switch (state) {
	
	case Stage_Statement::PLAYER_SECOND_DIE:
	{
		if (player_second_respawn_timer > 0.f)
		{
			player_second_respawn_timer -= dt;
		}
		else
		{
			sound.Play(SOUND::Respawn);
			player_second_respawn_timer = 3.0f;
			Respawn(state);

			player_sec_life--;
			stage_statements.erase(std::find(stage_statements.begin(), stage_statements.end(), state));
			total_life_count--;
		}
	}
	break;
	case Stage_Statement::PLAYER_THIRD_DIE:
	{
		if (player_third_respawn_timer > 0.f)
		{
			player_third_respawn_timer -= dt;
		}
		else
		{
			sound.Play(SOUND::Respawn);
			player_third_respawn_timer = 3.0f;
			Respawn(state);

			player_third_life--;
			stage_statements.erase(std::find(stage_statements.begin(), stage_statements.end(), state));
			total_life_count--;
		}
	}
	break;
	
	default:;
	}


}

void Referee::Respawn_Item(float dt)
{
	item_respawn_timer -= dt;
	const Item::Item_Kind item = static_cast<Item::Item_Kind>(RandomNumberGenerator(1, 9));

	Object* spawn_obj = nullptr;

	if (item_respawn_timer <= 0.0f && total_item_num > 0 && curr_field_num <= 3)
	{
		if (item == Item::Item_Kind::Dash)
		{
			if (item_num_dash > 0)
			{
				spawn_obj = item_dash[item_num_dash - 1];
				item_num_dash--;
			}
		}
		else if (item == Item::Item_Kind::HP)
		{
			if (item_num_heal > 0)
			{
				spawn_obj = item_heal[item_num_heal - 1];
				item_num_heal--;
			}
		}
		else if (item == Item::Item_Kind::Bulkup)
		{
			if (item_num_bulk_up > 0)
			{
				spawn_obj = item_bulk_up[item_num_bulk_up - 1];
				item_num_bulk_up--;
			}

		}
		else if (item == Item::Item_Kind::Throwing)
		{
			if (item_num_throwing > 0)
			{
				spawn_obj = item_throwing[item_num_throwing - 1];
				item_num_throwing--;
			}
		}
		else if (item == Item::Item_Kind::Time_Pause)
		{
			if (item_num_time_pause > 0)
			{
				spawn_obj = item_time_pause[item_num_time_pause - 1];
				item_num_time_pause--;
			}
		}
		else if (item == Item::Item_Kind::Reverse_Moving)
		{
			if (item_num_reverse_moving > 0)
			{
				spawn_obj = item_reverse_moving[item_num_reverse_moving - 1];
				item_num_reverse_moving--;
			}
		}
		else if (item == Item::Item_Kind::Missile)
		{
			if (item_num_missile > 0)
			{
				spawn_obj = item_missile[item_num_missile - 1];
				item_num_missile--;
			}
		}
		else if (item == Item::Item_Kind::Mine)
		{
			if (item_num_mine > 0)
			{
				spawn_obj = item_mine[item_num_mine - 1];
				item_num_mine--;
			}
		}

		if (spawn_obj != nullptr)
		{
			ObjectManager::GetObjectManager()->AddObject(spawn_obj);
			sound.Play(SOUND::ItemAppear);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(spawn_obj, nullptr, Message_Kind::Spawn_Object, 1.f));
			total_item_num--;
			item_respawn_timer = 5.0f;
			curr_field_num++;
		}

	}
}

void Referee::SetPlayerTemp()
{
	player_sec_temp = new Object * [player_sec_life]();
	player_third_temp = new Object * [player_third_life]();

	for (int i = 0; i < player_sec_life; i++)
	{
		player_sec_temp[i] = Make_Player_Pool(player_sec_sprite_path, player_sec_pos, "second", "save", second_text, player_sec_scale);
	}
	for (int i = 0; i < player_third_life; i++)
	{
		player_third_temp[i] = Make_Player_Pool(player_third_sprite_path, player_third_pos, "third", "save", third_text, player_third_scale);
	}
}

void Referee::SetItem()
{
	item_dash = new Object * [item_num]();
	item_heal = new Object * [item_num]();
	item_bulk_up = new Object * [item_num]();
	item_throwing = new Object * [item_num]();
	item_time_pause = new Object * [item_num]();
	item_reverse_moving = new Object * [item_num]();
	item_missile = new Object * [item_num]();
	item_mine = new Object * [item_num]();

	vector2 rand_pos;

	for (int i = 0; i < item_num; i++)
	{
		Set_Random_Pos(rand_pos);
		item_dash[i] = Make_Item_Pool("../Sprite/Item/fish.png", rand_pos, "item", "item", Item::Item_Kind::Dash);
	}
	for (int i = 0; i < item_num; i++)
	{
		Set_Random_Pos(rand_pos);
		item_heal[i] = Make_Item_Pool("../Sprite/Item/fish.png", rand_pos, "item", "item", Item::Item_Kind::HP);
	}
	for (int i = 0; i < item_num; i++)
	{
		Set_Random_Pos(rand_pos);
		item_bulk_up[i] = Make_Item_Pool("../Sprite/Item/fish.png", rand_pos, "item", "item", Item::Item_Kind::Bulkup);
	}
	for (int i = 0; i < item_num; i++)
	{
		Set_Random_Pos(rand_pos);
		item_throwing[i] = Make_Item_Pool("../Sprite/Item/fish.png", rand_pos, "item", "item", Item::Item_Kind::Throwing);
	}

	for (int i = 0; i < item_num; i++)
	{
		Set_Random_Pos(rand_pos);
		item_time_pause[i] = Make_Item_Pool("../Sprite/Item/fish.png", rand_pos, "item", "item", Item::Item_Kind::Time_Pause);
	}
	for (int i = 0; i < item_num; i++)
	{
		Set_Random_Pos(rand_pos);
		item_reverse_moving[i] = Make_Item_Pool("../Sprite/Item/fish.png", rand_pos, "item", "item", Item::Item_Kind::Reverse_Moving);
	}
	for (int i = 0; i < item_num; i++)
	{
		Set_Random_Pos(rand_pos);
		item_missile[i] = Make_Item_Pool("../Sprite/Item/fish.png", rand_pos, "item", "item", Item::Item_Kind::Missile);
	}
	for (int i = 0; i < item_num; i++)
	{
		Set_Random_Pos(rand_pos);
		item_mine[i] = Make_Item_Pool("../Sprite/Item/fish.png", rand_pos, "item", "item", Item::Item_Kind::Mine);
	}
}

void Referee::Set_Kill_State()
{
	second_kill = new Object;
	second_kill->Set_Name("kill");
	second_kill->Set_Tag("kill");
	second_kill->AddComponent(new Sprite(second_kill, "../sprite/Player/State/red_kill.png", true, 4, 12, { 0.f, 0.f }, { 100.f, 100.f },
		{ 255,255,255,255 }), "kill");
	second_kill->SetScale({ 15.f, 5.f });
	second_kill->SetTranslation({ 1400.f, -600.f });
	second_kill->Set_Need_To_Update(false);

	third_kill = new Object;
	third_kill->Set_Name("kill");
	third_kill->Set_Tag("kill");
	third_kill->AddComponent(new Sprite(third_kill, "../sprite/Player/State/blue_kill.png", true, 4, 12, { 0.f, 0.f }, { 100.f, 100.f },
		{ 255,255,255,255 }), "kill");
	third_kill->SetScale({ 15.f, 5.f });
	third_kill->SetTranslation({ -1400.f, 600.f });
	third_kill->Set_Need_To_Update(false);

	ObjectManager::GetObjectManager()->AddObject(second_kill);
	ObjectManager::GetObjectManager()->AddObject(third_kill);
}

void Referee::Win(float dt)
{
	if (win == false)
	{
		if((player_sec_life <= 0 || player_third_life <= 0))
		{
			FMOD_BOOL isBGM2Playing;
			FMOD_BOOL isMatchBGMPlaying;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &isBGM2Playing);
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::MatchBGM)], &isMatchBGMPlaying);
			if(isBGM2Playing)
			{
				sound.Stop(SOUND::BGM2);
			}
			if(!isMatchBGMPlaying && playOnce == false)
			{
				sound.Play(SOUND::MatchBGM);
				sound.currentBGM = SOUND::MatchBGM;
				playOnce = true;
			}

			if (!change_once)
			{
				audience_vec = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("audience");

				for (auto& aud : audience_vec)
				{
					aud->Change_Sprite(aud->Find_Sprite_By_Type(Sprite_Type::Audience_Cheerup));
					aud->GetTransform().GetTranslation_Reference().y -= 200.f;
				}
				change_once = true;
				is_cheerup_mode = true;
			}
		}
		if (player_sec_life == -1)
		{
			win = true;
			FMOD_BOOL isMatchBGMPlaying;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::MatchBGM)], &isMatchBGMPlaying);
			if (isMatchBGMPlaying)
			{
				sound.Stop(SOUND::MatchBGM);
			}
			sound.Play(SOUND::Win);
			player_dance_time = 5.f;
			curr_third_player->Change_Sprite(curr_third_player->Find_Sprite_By_Type(Sprite_Type::Player_Dance));
			win_player = curr_third_player;

			win_player->GetComponentByTemplate<Player>()->Set_Need_Update(false);
			win_player->SetNeedCollision(false);

			Graphic::GetGraphic()->Get_View().is_ended = true;
			win_particle = new ParticleGenerator(win_player, 50, "../Sprite/ParticleWin.png", ParticleType::WIN);
		}
		if (player_third_life == -1)
		{
			FMOD_BOOL isMatchBGMPlaying;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::MatchBGM)], &isMatchBGMPlaying);
			if (isMatchBGMPlaying)
			{
				sound.Stop(SOUND::MatchBGM);
			}
			win = true;
			sound.Play(SOUND::Win);
			player_dance_time = 5.f;
			curr_sec_player->Change_Sprite(curr_sec_player->Find_Sprite_By_Type(Sprite_Type::Player_Dance));
			win_player = curr_sec_player;

			win_player->GetComponentByTemplate<Player>()->Set_Need_Update(false);
			win_player->SetNeedCollision(false);

			Graphic::GetGraphic()->Get_View().is_ended = true;
			win_particle = new ParticleGenerator(win_player, 50, "../Sprite/ParticleWin.png", ParticleType::WIN);

		}
	}
	else
	{
		if (player_dance_time > 0.f)
		{
			player_dance_time -= dt;
			win_particle->Update(dt, win_player, 1, vector2(-500.0f, .0f));
			win_particle->Draw(win_player);
		}
		else
		{
			if (player_third_life == -1 && win_player != nullptr)
			{
				ObjectManager::GetObjectManager()->AddObject(second_win);
				sound.Play(SOUND::WinCrowd);
			}
			if (player_sec_life == -1 && win_player != nullptr)
			{
				sound.Play(SOUND::WinCrowd);
				ObjectManager::GetObjectManager()->AddObject(third_win);
			}

			Graphic::GetGraphic()->Get_View().Get_Camera().SetCenter(vector2{ 0.f, 0.f });
			Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
			Graphic::GetGraphic()->Get_View().Set_Is_Zoom_End_False();
			win_player = nullptr;
			is_cheerup_mode = false;
			if (input.Is_Key_Triggered(GLFW_KEY_SPACE))
			{
				sound.Play(SOUND::GameStart);
				isGameDone = true;
			}
		}
	}
}

Object* Referee::Get_Third_Kill()
{
	return third_kill;
}

Object* Referee::Get_First_Kill()
{
	return first_kill;
}

Object* Referee::Get_Second_Kill()
{
	return second_kill;
}

Object* Referee::Get_Fourth_Kill()
{
	return fourth_kill;
}

void Referee::Set_Random_Pos(vector2& pos)
{
	int rand_x = RandomNumberGenerator(0, 2400);
	int rand_y = RandomNumberGenerator(0, 1400);

	rand_x -= 1200;
	rand_y -= 800;

	pos.x = static_cast<int>(rand_x);
	pos.y = static_cast<int>(rand_y);
}

Object* Referee::Return_New_Missile()
{
	Object* missile = new Object();;
	missile->Set_Name("missile");
	missile->Set_Tag("throwing");
	missile->SetNeedCollision(true);
	missile->AddComponent(new Sprite(missile, "../sprite/Item/missile.png", true, 2, 8, { 0.f,0.f },
		{ 200.f,200.f }, { 255,255,255,255 }), "missile");
	missile->AddComponent(new Physics);
	missile->AddComponent(new Missile);
	missile->Set_Current_Sprite(missile->Find_Sprite_By_Name("missile"));
	missile->SetScale(2.f);

	return missile;
}

void Referee::Respawn(Stage_Statement statement)
{
	switch (statement)
	{
	case Stage_Statement::PLAYER_SECOND_DIE:
		if (player_sec_life > 0)
		{
			Object* player = player_sec_temp[player_sec_life - 1];

			if (player != nullptr)
			{
				player->GetComponentByTemplate<Player>()->Set_This_UI_info(second_ui);
				second_ui->Reset();
				ObjectManager::GetObjectManager()->AddObject(player);
				ObjectManager::GetObjectManager()->AddObject(player->GetComponentByTemplate<Player>()->Get_Hp_Bar());
				curr_sec_player = player;
				Message_Manager::Get_Message_Manager()->Save_Message(new Message(player, nullptr, Message_Kind::Spawn_Object, 4.1f));
			}

		}
		break;

	case Stage_Statement::PLAYER_THIRD_DIE:
		if (player_third_life > 0)
		{
			Object* player = player_third_temp[player_third_life - 1];

			if (player != nullptr)
			{
				player->GetComponentByTemplate<Player>()->Set_This_UI_info(third_ui);
				third_ui->Reset();
				curr_third_player = player;
				ObjectManager::GetObjectManager()->AddObject(player);
				ObjectManager::GetObjectManager()->AddObject(player->GetComponentByTemplate<Player>()->Get_Hp_Bar());
				Message_Manager::Get_Message_Manager()->Save_Message(new Message(player, nullptr, Message_Kind::Spawn_Object, 4.1f));
			}
		}
		break;
	}
}
