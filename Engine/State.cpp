/*
 * Author		:Sangmin Kim
 * File			:State.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for State
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "State.h"
#include "Object.h"
#include "Player_Ui.h"
#include "Component_Player.h"
#include "Component_Sprite.h"
#include "Physics.h"
#include "ObjectManager.h"
#include "Component_Text.h"


Object* State::Make_Player(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale, bool is_main_menu)
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
	std::string sprite_path_dance = path_to_player_state;

	
	std::string sprite_path_reverse_moving_pen = path_to_player_item_effect;
	std::string sprite_path_ready = path_to_player_item_effect;
	std::string sprite_path_heal_effect = path_to_player_item_effect;
	std::string sprite_path_ready_bulkup = path_to_player_item_effect;
	std::string sprite_path_bulkup_used = path_to_player_item_effect;
	std::string sprite_path_throwing_effect = path_to_player_item_effect;
	std::string sprite_path_missile_effect = path_to_player_item_effect;
	std::string sprite_path_magnet_aiming = path_to_player_item_effect;
	std::string sprite_path_magnet_chasing = path_to_player_item_effect;
	std::string sprite_path_dash_effect = path_to_player_item_effect;
	std::string sprite_path_timestop_effect = path_to_player_item_effect;
	std::string sprite_path_reverse_effect = path_to_player_item_effect;

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
		sprite_path_reverse_effect += sprite_path + "_reverse_effect.png";
	}

	Object* player;
	player = new Object();
	player->SetTranslation(pos);
	player->Set_Name(name);
	player->Set_Tag(tag);
	player->SetNeedCollision(true);
	player->AddComponent(new Player(), "player");
	player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);

	player->AddComponent(new Sprite(player, sprite_path_spawn.c_str(), true, 37, 9.25, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Spawn), "spawn", !is_main_menu);

	bool is_debug_mode;
#if _DEBUG
	is_debug_mode = true;
#else
	is_debug_mode = false;
#endif
	player->AddComponent(new Sprite(player, sprite_path_normal.c_str(), true, 3, 6, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Normal, is_debug_mode), "normal", is_main_menu);

	player->AddComponent(new Sprite(player, sprite_path_speed2.c_str(), true, 3, 24, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Speed2, is_debug_mode), "speed2", false);

	player->AddComponent(new Sprite(player, sprite_path_speed3.c_str(), true, 3, 48, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Speed3, is_debug_mode), "speed3", false);
	
	player->AddComponent(new Sprite(player, sprite_path_lock.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Locking), "lock", false);
	
	player->AddComponent(new Sprite(player, sprite_path_ready.c_str(), pos, false, Sprite_Type::Player_Ready), "ready", false);
	
	player->AddComponent(new Sprite(player, sprite_path_die.c_str(), true, 8, 16, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Die, is_debug_mode), "die", false);
	
	player->AddComponent(new Sprite(player, sprite_path_crying.c_str(), true, 2, 4, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Crying, is_debug_mode), "crying", false);
	
	player->AddComponent(new Sprite(player, sprite_path_fat.c_str(), true, 3, 9, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Fat, is_debug_mode), "fat", false);

	player->AddComponent(new Sprite(player, sprite_path_reverse_moving_pen.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Reverse_Moving), "reverse", false);

	player->AddComponent(new Sprite(player, sprite_path_timestop_effect.c_str(), true, 4, 8, pos, { 200.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Effect_Timestop), "time", false);

	player->AddComponent(new Sprite(player, sprite_path_reverse_effect.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Effect_Reverse), "reverse", false);

	player->AddComponent(new Sprite(player, sprite_path_dance.c_str(), true, 15, 7, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Dance), "dance", false);

	player->AddComponent(new Sprite(player, sprite_path_paused.c_str(), pos, false, Sprite_Type::Player_Paused, { 100.f, 100.f }), "paused", false);

	player->AddComponent(new Sprite(player, sprite_path_ready_bulkup.c_str(), true, 4, 12, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Effect_Bulkp), "effect_bulkup", false);

	player->AddComponent(new Sprite(player, sprite_path_bulkup_used.c_str(), true, 3, 9, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Bulkup_Used), "effect_bulkup_use", false);
	
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
	
	player->AddComponent(new Physics(), "physics");

	if (!is_main_menu)
	{
		player->Set_Current_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Spawn));
	}
	else
	{
		player->Set_Current_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
	}

	player->GetTransform().SetScale(scale);

	if (name == "first")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_green");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}
	else if (name == "second")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_red");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}
	else if (name == "third")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_blue");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}
	else if (name == "fourth")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_normal");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}

	ObjectManager::GetObjectManager()->AddObject(player);

	return player;
}

PLAYER_UI* State::Make_Set_Ui(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale,
	Object* player)
{
	PLAYER_UI* player_ui;
	player_ui = new PLAYER_UI();
	player_ui->Set_Name(name);
	player_ui->SetNeedCollision(false);
	player_ui->GetTransform().GetScale_Reference() = scale;
	player_ui->Set_Name(name);
	player_ui->Set_Tag(tag);
	player_ui->AddComponent(new Sprite(player_ui, sprite_path.c_str(), pos));
	player_ui->AddComponent(new Ui(player_ui));
	player_ui->Set_Bitmap_Font(&font);
	player_ui->Initialize();
	ObjectManager::GetObjectManager()->AddObject(player_ui);

	//player->GetComponentByTemplate<Player>()->Set_This_UI_info(player_ui);

	return player_ui;
}

Object* State::Make_Set_Text(std::string name, std::string tag, vector2 pos, Object* player, Color4f color,
	vector2 size, BitmapFont* font)
{
	Object* text = new Object();

	text->SetTranslation(pos);
	text->AddComponent(new TextComp(text, L" ", color, size, *font));
	text->Set_Name(name);
	text->Set_Tag(tag);
	ObjectManager::GetObjectManager()->AddObject(text);
	player->Set_Dmg_Text(text);

	return text;
}