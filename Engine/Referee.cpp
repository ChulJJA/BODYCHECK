/*
 * Author		:Sangmin Kim
 * File			:Referee.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for making for manager of game board. This object will
 *				 add item & respawn player to the prototype game screen.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
#include "Component_Missile.h"
#include "Physics.h"


Referee* Referee::referee = nullptr;
StateManager* state_manager = nullptr;
Application* app = nullptr;

void Referee::Set_Win_State()
{
	first_win = new Object();
	first_win->AddComponent(new Sprite(first_win, "../Sprite/pen_green2_win.png", true, 2, 8, { 0.f,0.f }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "win", true);
	first_win->GetTransform().SetScale({ 40.f, 22.f });

	second_win = new Object();
	second_win->AddComponent(new Sprite(second_win, "../Sprite/pen_red2_win.png", true, 2, 8, { 0.f,0.f }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "win", true);
	second_win->GetTransform().SetScale({ 40.f, 22.f });

	third_win = new Object();
	third_win->AddComponent(new Sprite(third_win, "../Sprite/pen_blue2_win.png", true, 2, 8, { 0.f,0.f }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "win", true);
	third_win->GetTransform().SetScale({ 40.f, 22.f });

	fourth_win = new Object();
	fourth_win->AddComponent(new Sprite(fourth_win, "../Sprite/pen_normal2_win.png", true, 2, 8, { 0.f,0.f }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "win", true);
	fourth_win->GetTransform().SetScale({ 40.f, 22.f });

}

Referee::Referee()
{
	state_manager = StateManager::GetStateManager();
	if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Game)
	{
		player_first_life = 1;
		player_sec_life = 1;
		player_third_life = 1;
		player_fourth_life = 1;
		total_life_count = player_first_life + player_sec_life + player_third_life + player_fourth_life;
		total_life_count += 4;
	}
	else if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Tutorial)
	{
		player_first_life = 20;
		player_sec_life = 20;
		player_third_life = 20;
		player_fourth_life = 20;
		total_life_count = player_first_life + player_sec_life + player_third_life + player_fourth_life;
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

	stage_statements.clear();
	missile_saving = new Object * [missile_num];
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

	if (win == false)
	{
		Respawn_Item(dt);
	}

	Win();

}

void Referee::Delete()
{
}

Object* Referee::Make_Player_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag, Object* text)
{
	std::string path_to_player_state = "../Sprite/Player/State/";
	std::string path_to_player_item_effect = "../Sprite/Player/Item_Effect/";
	std::string path_to_player_display_item = "../Sprite/Player/Display_Item/";

	std::string sprite_path_normal = path_to_player_state;
	std::string sprite_path_lock = path_to_player_state;
	std::string sprite_path_crying = path_to_player_state;
	std::string sprite_path_die = path_to_player_state;
	std::string sprite_path_paused = path_to_player_state;


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

	std::string sprite_path_missile_launcher = path_to_player_display_item;
	std::string sprite_path_dash = path_to_player_display_item;
	std::string sprite_path_bulkup = path_to_player_display_item;
	std::string sprite_path_throwing = path_to_player_display_item;
	std::string sprite_path_heal = path_to_player_display_item;
	std::string sprite_path_magnet = path_to_player_display_item;
	std::string sprite_path_timestop = path_to_player_display_item;
	std::string sprite_path_reverse = path_to_player_display_item;


	{
		sprite_path_normal += sprite_path + ".png";
		sprite_path_lock += sprite_path + "_lock.png";
		sprite_path_crying += sprite_path + "_hit.png";
		sprite_path_die += sprite_path + "_die.png";
		sprite_path_paused += sprite_path + "_paused.png";

	}

	//effect when using item.
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

	//display when get item.
	{
		sprite_path_missile_launcher += "missile_launcher_showing.png";
		sprite_path_dash += sprite_path + "_dash_display.png";
		sprite_path_bulkup += "bulkup_display.png";
		sprite_path_throwing += "throwing_display.png";
		sprite_path_heal += "heal_showing.png";
		sprite_path_magnet += "magnet_display.png";
		sprite_path_timestop += "time_stop_display.png";
		sprite_path_reverse += "reverse_display.png";
	}

	Object* player = new Object();
	player->Set_Name(name);
	player->Set_Tag(tag);
	player->AddComponent(new Player(false), "player");


	player->AddComponent(new Sprite(player, sprite_path_normal.c_str(), true, 3, 6, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Normal), "normal", true);

	player->AddComponent(new Sprite(player, sprite_path_lock.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Locking), "lock", false);
	player->AddComponent(new Sprite(player, sprite_path_reverse_moving_pen.c_str(), true, 2, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Reverse_Moving), "reverse", false);
	player->AddComponent(new Sprite(player, sprite_path_ready.c_str(), pos, false, Sprite_Type::Player_Ready), "ready", false);
	player->AddComponent(new Sprite(player, sprite_path_timestop_effect.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Effect_Timestop), "time", false);
	player->AddComponent(new Sprite(player, sprite_path_die.c_str(), true, 8, 16, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Die), "die", false);

	player->AddComponent(new Sprite(player, sprite_path_crying.c_str(), true, 2, 4, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Crying), "crying", false);

	player->AddComponent(new Sprite(player, sprite_path_missile_launcher.c_str(), pos, false, Sprite_Type::Missile_Launcher_Showing, { 80.f, 80.f }), "missile_launcher", false);

	player->AddComponent(new Sprite(player, sprite_path_dash.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Dash_Showing), "dash", false);

	player->AddComponent(new Sprite(player, sprite_path_bulkup.c_str(), pos, false, Sprite_Type::Bulkup_Showing, { 100.f, 100.f }), "bulkup", false);
	player->AddComponent(new Sprite(player, sprite_path_throwing.c_str(), pos, false, Sprite_Type::Throwing_Showing, { 100.f, 100.f }), "throwing", false);
	player->AddComponent(new Sprite(player, sprite_path_magnet.c_str(), pos, false, Sprite_Type::Magnet_Showing, { 100.f, 100.f }), "magnet", false);
	player->AddComponent(new Sprite(player, sprite_path_timestop.c_str(), pos, false, Sprite_Type::Timestop_Showing, { 100.f, 100.f }), "time", false);
	player->AddComponent(new Sprite(player, sprite_path_reverse.c_str(), pos, false, Sprite_Type::Reverse_Showing, { 100.f, 100.f }), "reverse", false);
	player->AddComponent(new Sprite(player, sprite_path_paused.c_str(), pos, false, Sprite_Type::Player_Paused, { 100.f, 100.f }), "paused", false);
	player->AddComponent(new Sprite(player, sprite_path_heal.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Heal_Showing), "heal", false);

	player->AddComponent(new Sprite(player, sprite_path_ready_bulkup.c_str(), true, 8, 16, pos, { 100.f,100.f },
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

	player->AddComponent(new Physics(true), "physics");

	player->Set_Current_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
	player->SetScale({ 2.f,2.f });
	player->Set_Dmg_Text(text);
	player->SetNeedCollision(true);

	return player;
}

Object* Referee::Make_Item_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag,
	Item::Item_Kind kind)
{
	Object* item = new Object();
	item->AddComponent(new Sprite(item, sprite_path.c_str(), pos, false), "item");
	item->AddComponent(new Item());
	item->AddComponent(new Physics());
	item->Set_Name(name);
	item->Set_Tag(tag);
	item->SetTranslation(pos);
	item->GetComponentByTemplate<Item>()->Set_Kind(kind);
	item->Set_Current_Sprite(item->Find_Sprite_By_Name("item"));
	item->SetNeedCollision(true);
	item->SetScale(2.f);
	total_item.push_back(item);

	return item;
}

void Referee::Respawn_Player(Stage_Statement state, float dt)
{
	switch (state) {
	case Stage_Statement::PLAYER_FIRST_DIE:
	{
		if (player_first_respawn_timer > 0.f)
		{
			player_first_respawn_timer -= dt;
		}
		else
		{
			sound.Play(SOUND::Respawn);
			player_first_respawn_timer = 3.0f;
			Respawn(state);

			player_first_life--;
			stage_statements.erase(std::find(stage_statements.begin(), stage_statements.end(), state));
			first_ui->Get_Life_Num()->GetComponentByTemplate<TextComp>()->GetText().SetString(std::to_wstring(player_first_life));
			total_life_count--;
		}
	}
	break;
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
			second_ui->Get_Life_Num()->GetComponentByTemplate<TextComp>()->GetText().SetString(std::to_wstring(player_sec_life));
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
			third_ui->Get_Life_Num()->GetComponentByTemplate<TextComp>()->GetText().SetString(std::to_wstring(player_third_life));
			total_life_count--;
		}
	}
	break;
	case Stage_Statement::PLAYER_FOURTH_DIE:
	{
		if (player_fourth_respawn_timer > 0.f)
		{
			player_fourth_respawn_timer -= dt;
		}
		else
		{
			sound.Play(SOUND::Respawn);
			player_fourth_respawn_timer = 3.0f;
			Respawn(state);

			player_fourth_life--;
			stage_statements.erase(std::find(stage_statements.begin(), stage_statements.end(), state));
			fourth_ui->Get_Life_Num()->GetComponentByTemplate<TextComp>()->GetText().SetString(std::to_wstring(player_fourth_life));
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

	if (item_respawn_timer <= 0.0f && total_item_num > 0)
	{
		if (item == Item::Item_Kind::Dash)
		{
			if (item_num_dash > 0)
			{
				ObjectManager::GetObjectManager()->AddObject(item_dash[item_num_dash - 1]);
				item_num_dash--;
			}
		}
		else if (item == Item::Item_Kind::HP)
		{
			if (item_num_heal > 0)
			{
				ObjectManager::GetObjectManager()->AddObject(item_heal[item_num_heal - 1]);
				item_num_heal--;
			}
		}
		else if (item == Item::Item_Kind::Bulkup)
		{
			if (item_num_bulk_up > 0)
			{
				ObjectManager::GetObjectManager()->AddObject(item_bulk_up[item_num_bulk_up - 1]);
				item_num_bulk_up--;
			}

		}
		else if (item == Item::Item_Kind::Throwing)
		{
			if (item_num_throwing > 0)
			{
				ObjectManager::GetObjectManager()->AddObject(item_throwing[item_num_throwing - 1]);
				item_num_throwing--;
			}
		}
		else if (item == Item::Item_Kind::Magnatic)
		{
			if (item_num_magnetic > 0)
			{
				ObjectManager::GetObjectManager()->AddObject(item_magnetic[item_num_magnetic - 1]);
				item_num_magnetic--;
			}
		}
		else if (item == Item::Item_Kind::Time_Pause)
		{
			if (item_num_time_pause > 0)
			{
				ObjectManager::GetObjectManager()->AddObject(item_time_pause[item_num_time_pause - 1]);
				item_num_time_pause--;
			}
		}
		else if (item == Item::Item_Kind::Reverse_Moving)
		{
			if (item_num_reverse_moving > 0)
			{
				ObjectManager::GetObjectManager()->AddObject(item_reverse_moving[item_num_reverse_moving - 1]);
				item_num_reverse_moving--;
			}
		}
		else if (item == Item::Item_Kind::Missile)
		{
			if (item_num_missile > 0)
			{
				ObjectManager::GetObjectManager()->AddObject(item_missile[item_num_missile - 1]);
				item_num_missile--;
			}
		}
		else if (item == Item::Item_Kind::Mine)
		{
			if (item_num_mine > 0)
			{
				ObjectManager::GetObjectManager()->AddObject(item_mine[item_num_mine - 1]);
				item_num_mine--;
			}
		}
		total_item_num--;
		item_respawn_timer = 5.0f;
	}
}

void Referee::SetPlayerTemp()
{
	player_first_temp = new Object * [player_first_life]();
	player_sec_temp = new Object * [player_sec_life]();
	player_third_temp = new Object * [player_third_life]();
	player_fourth_temp = new Object * [player_fourth_life]();


	for (int i = 0; i < player_first_life; i++)
	{
		player_first_temp[i] = Make_Player_Pool("pen_green2", { 400,400 }, "first", "save", first_text);
	}
	for (int i = 0; i < player_sec_life; i++)
	{
		player_sec_temp[i] = Make_Player_Pool("pen_red2", { 400,-400 }, "second", "save", second_text);
	}
	for (int i = 0; i < player_third_life; i++)
	{
		player_third_temp[i] = Make_Player_Pool("pen_blue2", { -400,400 }, "third", "save", third_text);
	}
	for (int i = 0; i < player_fourth_life; i++)
	{
		player_fourth_temp[i] = Make_Player_Pool("pen_normal2", { -400,-400 }, "forth", "save", fourth_text);
	}
}

void Referee::SetItem()
{
	item_dash = new Object * [item_num]();
	item_heal = new Object * [item_num]();
	item_bulk_up = new Object * [item_num]();
	item_throwing = new Object * [item_num]();
	item_magnetic = new Object * [item_num]();
	item_time_pause = new Object * [item_num]();
	item_reverse_moving = new Object * [item_num]();
	item_missile = new Object * [item_num]();
	item_mine = new Object * [item_num]();

	for (int i = 0; i < item_num; i++)
	{
		item_dash[i] = Make_Item_Pool("../Sprite/Item/item.png", { 0,0 }, "item", "item", Item::Item_Kind::Dash);
	}
	for (int i = 0; i < item_num; i++)
	{
		item_heal[i] = Make_Item_Pool("../Sprite/Item/item.png", { -400,0 }, "item", "item", Item::Item_Kind::HP);
	}
	for (int i = 0; i < item_num; i++)
	{
		item_bulk_up[i] = Make_Item_Pool("../Sprite/Item/item.png", { 400,0 }, "item", "item", Item::Item_Kind::Bulkup);
	}
	for (int i = 0; i < item_num; i++)
	{
		item_throwing[i] = Make_Item_Pool("../Sprite/Item/item.png", { 400,0 }, "item", "item", Item::Item_Kind::Throwing);
	}
	for (int i = 0; i < item_num; i++)
	{
		item_magnetic[i] = Make_Item_Pool("../Sprite/Item/item.png", { 400,0 }, "item", "item", Item::Item_Kind::Magnatic);
	}
	for (int i = 0; i < item_num; i++)
	{
		item_time_pause[i] = Make_Item_Pool("../Sprite/Item/item.png", { 400,0 }, "item", "item", Item::Item_Kind::Time_Pause);
	}
	for (int i = 0; i < item_num; i++)
	{
		item_reverse_moving[i] = Make_Item_Pool("../Sprite/Item/item.png", { 400,0 }, "item", "item", Item::Item_Kind::Reverse_Moving);
	}
	for (int i = 0; i < item_num; i++)
	{
		item_missile[i] = Make_Item_Pool("../Sprite/Item/item.png", { 400,0 }, "item", "item", Item::Item_Kind::Missile);
	}
	for (int i = 0; i < item_num; i++)
	{
		item_mine[i] = Make_Item_Pool("../Sprite/Item/item.png", { 400,0 }, "item", "item", Item::Item_Kind::Mine);
	}
}

void Referee::Win()
{
	if (win == false)
	{
		if (player_first_life == -1 && player_sec_life == -1 && player_third_life == -1)
		{
			ObjectManager::GetObjectManager()->AddObject(fourth_win);
			win = true;
		}
		else if (player_first_life == -1 && player_sec_life == -1 && player_fourth_life == -1)
		{
			ObjectManager::GetObjectManager()->AddObject(third_win);
			win = true;
		}
		else if (player_first_life == -1 && player_third_life == -1 && player_fourth_life == -1)
		{
			ObjectManager::GetObjectManager()->AddObject(second_win);
			win = true;
		}
		else if (player_sec_life == -1 && player_third_life == -1 && player_fourth_life == -1)
		{
			ObjectManager::GetObjectManager()->AddObject(first_win);
			win = true;
		}
	}
}

Object* Referee::Return_New_Missile()
{
	Object* missile = new Object();;
	missile->Set_Name("missile");
	missile->Set_Tag("throwing");
	missile->SetNeedCollision(true);
	missile->AddComponent(new Sprite(missile, "../sprite/Item/missiles.png", true, 3, 8, { 0.f,0.f },
		{ 100.f,100.f }, { 255,255,255,255 }), "missile");
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
			player_sec_temp[player_sec_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar()->GetComponentByTemplate<Sprite>()->Set_Need_Update(true);
			player_sec_temp[player_sec_life - 1]->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
			player_sec_temp[player_sec_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(second_ui);
			player_sec_temp[player_sec_life - 1]->Set_Tag("player");
			ObjectManager::GetObjectManager()->AddObject(player_sec_temp[player_sec_life - 1]);
			ObjectManager::GetObjectManager()->AddObject(player_sec_temp[player_sec_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar());
			second_ui->Reset();
		}
		break;

	case Stage_Statement::PLAYER_FIRST_DIE:
		if (player_first_life > 0)
		{
			player_first_temp[player_first_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar()->GetComponentByTemplate<Sprite>()->Set_Need_Update(true);
			player_first_temp[player_first_life - 1]->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
			player_first_temp[player_first_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(first_ui);
			player_first_temp[player_first_life - 1]->Set_Tag("player");
			ObjectManager::GetObjectManager()->AddObject(player_first_temp[player_first_life - 1]);
			ObjectManager::GetObjectManager()->AddObject(player_first_temp[player_first_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar());
			first_ui->Reset();
		}
		break;

	case Stage_Statement::PLAYER_THIRD_DIE:
		if (player_third_life > 0)
		{
			player_third_temp[player_third_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar()->GetComponentByTemplate<Sprite>()->Set_Need_Update(true);
			player_third_temp[player_third_life - 1]->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
			player_third_temp[player_third_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(third_ui);
			player_third_temp[player_third_life - 1]->Set_Tag("player");
			ObjectManager::GetObjectManager()->AddObject(player_third_temp[player_third_life - 1]);
			ObjectManager::GetObjectManager()->AddObject(player_third_temp[player_third_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar());
			third_ui->Reset();
		}
		break;

	case Stage_Statement::PLAYER_FOURTH_DIE:
		if (player_fourth_life > 0)
		{
			player_fourth_temp[player_fourth_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar()->GetComponentByTemplate<Sprite>()->Set_Need_Update(true);
			player_fourth_temp[player_fourth_life - 1]->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
			player_fourth_temp[player_fourth_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(fourth_ui);
			player_fourth_temp[player_fourth_life - 1]->Set_Tag("player");
			ObjectManager::GetObjectManager()->AddObject(player_fourth_temp[player_fourth_life - 1]);
			ObjectManager::GetObjectManager()->AddObject(player_fourth_temp[player_fourth_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar());
			fourth_ui->Reset();
		}
		break;
	}
}
