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
#include "Component_Collision.h"
#include "Component_Item.h"
#include "Player_Ui.h"
#include "Engine.hpp"
#include "StateManager.h"
#include "Component_Text.h"
#include "Application.hpp"

Referee* Referee::referee = nullptr;
StateManager* state_manager = nullptr;
Application* app = nullptr;

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
	player_first_temp = new Object * [player_first_life]();
	player_sec_temp = new Object * [player_sec_life]();

	player_third_temp = new Object * [player_third_life]();
	player_fourth_temp = new Object * [player_fourth_life]();

	item_save = new Object * [item_num]();
	item_save_hp = new Object * [item_num]();
	item_bulk_up = new Object * [item_num]();

	for (int i = 0; i < player_first_life; i++)
	{
		player_first_temp[i] = Make_Player_Pool("pen_green", { 400,400 }, "first", "save", first_text);
	}

	for (int i = 0; i < player_sec_life; i++)
	{
		player_sec_temp[i] = Make_Player_Pool("pen_red", { 400,-400 }, "second", "save", second_text);
	}
	for (int i = 0; i < player_third_life; i++)
	{
		player_third_temp[i] = Make_Player_Pool("pen_purple", { -400,400 }, "third", "save", third_text);
	}
	for (int i = 0; i < player_fourth_life; i++)
	{
		player_fourth_temp[i] = Make_Player_Pool("pen_normal", { -400,-400 }, "forth", "save", fourth_text);
	}


	for (int i = 0; i < item_num; i++)
	{
		item_save[i] = Make_Item_Pool("../Sprite/item.png", { 0,0 }, "item", "item", Item::Item_Kind::Dash);
	}

	for (int i = 0; i < item_num; i++)
	{

		item_save_hp[i] = Make_Item_Pool("../Sprite/item.png", { -400,0 }, "item", "item", Item::Item_Kind::Dash);
	}

	for (int i = 0; i < item_num; i++)
	{
		item_bulk_up[i] = Make_Item_Pool("../Sprite/item.png", { 400,0 }, "item", "item", Item::Item_Kind::Time_Pause);
	}
	for (int i = 0; i < item_num; i++)
	{
		item_bulk_up[i] = Make_Item_Pool("../Sprite/item.png", { 400,0 }, "item", "item", Item::Item_Kind::Reverse_Moving);
	}
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

	Respawn_Item(dt);

	this->GetComponentByTemplate<Collision>()->Update(dt);
}

void Referee::Delete()
{
}

Object* Referee::Make_Player_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag, Object* text)
{
	std::string sprite_path_normal = "../Sprite/";
	sprite_path_normal += sprite_path;
	sprite_path_normal += ".png";

	std::string sprite_path_lock = "../Sprite/";
	sprite_path_lock += sprite_path;
	sprite_path_lock += "_lock";
	sprite_path_lock += ".png";

	std::string sprite_path_chase = "../Sprite/";
	sprite_path_chase += sprite_path;
	sprite_path_chase += "_chase.png";

	std::string sprite_path_thinking = "../Sprite/";
	sprite_path_thinking += sprite_path;
	sprite_path_thinking += "_thinking.png";

	std::string sprite_path_reverse_moving_pen = "../Sprite/reverse_moving_pen";
	sprite_path_reverse_moving_pen += ".png";

	
	Object* player = new Object();
	player->Set_Name(name);
	player->Set_Tag(tag);
	player->AddComponent(new Player(false));
	player->AddComponent(new Sprite(player, sprite_path_normal.c_str(), pos), "normal", true);
	player->AddComponent(new Sprite(player, sprite_path_lock.c_str(), pos), "lock", false);
	player->AddComponent(new Sprite(player, sprite_path_chase.c_str(), pos), "chase", false);
	player->AddComponent(new Sprite(player, sprite_path_thinking.c_str(), pos), "thinking", false);
	player->AddComponent(new Sprite(player, sprite_path_reverse_moving_pen.c_str(), pos), "reverse_moving_pen", false);
	player->AddComponent(new Physics(true));
	player->Set_Current_Sprite(player->Find_Sprite_By_Name("normal"));
	player->SetScale({ 3.f,3.f });
	player->Set_Dmg_Text(text);

	return player;
}

Object* Referee::Make_Item_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag,
	Item::Item_Kind kind)
{
	Object* item = new Object();
	item->AddComponent(new Sprite(item, sprite_path.c_str(), pos, false));
	item->AddComponent(new Item());
	item->AddComponent(new Physics());
	item->Set_Name(name);
	item->Set_Tag(tag);
	item->SetTranslation(pos);
	item->GetComponentByTemplate<Item>()->Set_Kind(kind);
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
		}
	}
	break;
	default:;
	}


}

void Referee::Respawn_Item(float dt)
{
	item_respawn_timer -= dt;
	if (item_respawn_timer <= 0.0f && total_item_num > 0)
	{
		item_respawn_timer = 5.0f;

		if (total_item_num % 3 == 2)
		{
			ObjectManager::GetObjectManager()->AddObject(item_save[item_num_dash - 1]);
			item_num_dash--;
		}
		else if (total_item_num % 3 == 1)
		{
			ObjectManager::GetObjectManager()->AddObject(item_save_hp[item_num_hp - 1]);
			item_num_hp--;
		}
		else
		{
			ObjectManager::GetObjectManager()->AddObject(item_bulk_up[item_num_bulk_up - 1]);
			item_num_bulk_up--;
		}
		total_item_num--;
	}
}

void Referee::Respawn(Stage_Statement statement)
{
	switch (statement)
	{
	case Stage_Statement::PLAYER_SECOND_DIE:
		player_sec_temp[player_sec_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar()->GetComponentByTemplate<Sprite>()->Set_Need_Update(true);
		player_sec_temp[player_sec_life - 1]->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
		player_sec_temp[player_sec_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(second_ui);
		player_sec_temp[player_sec_life - 1]->Set_Tag("player");
		ObjectManager::GetObjectManager()->AddObject(player_sec_temp[player_sec_life - 1]);
		ObjectManager::GetObjectManager()->AddObject(player_sec_temp[player_sec_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar());
		second_ui->Reset();
		break;

	case Stage_Statement::PLAYER_FIRST_DIE:
		player_first_temp[player_first_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar()->GetComponentByTemplate<Sprite>()->Set_Need_Update(true);
		player_first_temp[player_first_life - 1]->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
		player_first_temp[player_first_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(first_ui);
		player_first_temp[player_first_life - 1]->Set_Tag("player");
		ObjectManager::GetObjectManager()->AddObject(player_first_temp[player_first_life - 1]);
		ObjectManager::GetObjectManager()->AddObject(player_first_temp[player_first_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar());
		first_ui->Reset();
		break;

	case Stage_Statement::PLAYER_THIRD_DIE:
		player_third_temp[player_third_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar()->GetComponentByTemplate<Sprite>()->Set_Need_Update(true);
		player_third_temp[player_third_life - 1]->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
		player_third_temp[player_third_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(third_ui);
		player_third_temp[player_third_life - 1]->Set_Tag("player");
		ObjectManager::GetObjectManager()->AddObject(player_third_temp[player_third_life - 1]);
		ObjectManager::GetObjectManager()->AddObject(player_third_temp[player_third_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar());
		third_ui->Reset();
		break;

	case Stage_Statement::PLAYER_FOURTH_DIE:
		player_fourth_temp[player_fourth_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar()->GetComponentByTemplate<Sprite>()->Set_Need_Update(true);
		player_fourth_temp[player_fourth_life - 1]->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
		player_fourth_temp[player_fourth_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(fourth_ui);
		player_fourth_temp[player_fourth_life - 1]->Set_Tag("player");
		ObjectManager::GetObjectManager()->AddObject(player_fourth_temp[player_fourth_life - 1]);
		ObjectManager::GetObjectManager()->AddObject(player_fourth_temp[player_fourth_life - 1]->GetComponentByTemplate<Player>()->Get_Hp_Bar());
		fourth_ui->Reset();
		break;
	}
}
