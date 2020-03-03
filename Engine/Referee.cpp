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
        player_first_temp[i] = new Object();
        //player_first_temp[i]->AddComponent(new Player());
        player_first_temp[i]->AddComponent(new Sprite(player_first_temp[i], "../Sprite/pen_green.png", { 400,400 }));
        player_first_temp[i]->AddComponent(new Physics(true));
        player_first_temp[i]->Set_Name("first");
        player_first_temp[i]->Set_Tag("player");
        player_first_temp[i]->SetScale({ 3.f,3.f });
        //player_first_temp[i]->GetComponentByTemplate<Player>()->Set_This_UI_info(first_ui);
        player_first_temp[i]->Set_Dmg_Text(first_text);
    }

    for (int i = 0; i < player_sec_life; i++)
    {
        player_sec_temp[i] = new Object();
        //player_sec_temp[i]->AddComponent(new Player());
        player_sec_temp[i]->AddComponent(new Sprite(player_sec_temp[i], "../Sprite/pen_red.png", { 400,-400 }));
        player_sec_temp[i]->AddComponent(new Physics(true));
        player_sec_temp[i]->Set_Name("second");
        player_sec_temp[i]->Set_Tag("player");
        player_sec_temp[i]->SetScale({ 3.f,3.f });
        //player_sec_temp[i]->GetComponentByTemplate<Player>()->Set_This_UI_info(second_ui);
        player_sec_temp[i]->Set_Dmg_Text(second_text);
    }
    for (int i = 0; i < player_third_life; i++)
    {
        player_third_temp[i] = new Object();
        //player_third_temp[i]->AddComponent(new Player());
        player_third_temp[i]->AddComponent(new Sprite(player_third_temp[i], "../Sprite/pen_purple.png", { -400,400 }));
        player_third_temp[i]->AddComponent(new Physics(true));
        player_third_temp[i]->Set_Name("third");
        player_third_temp[i]->Set_Tag("player");
        player_third_temp[i]->SetScale({ 3.f,3.f });
        //player_third_temp[i]->GetComponentByTemplate<Player>()->Set_This_UI_info(third_ui);
        player_third_temp[i]->Set_Dmg_Text(third_text);
    }
    for (int i = 0; i < player_fourth_life; i++)
    {
        player_fourth_temp[i] = new Object();
        //player_fourth_temp[i]->AddComponent(new Player());
        player_fourth_temp[i]->AddComponent(new Sprite(player_fourth_temp[i], "../Sprite/pen_normal.png", { -400,-400 }));
        player_fourth_temp[i]->AddComponent(new Physics(true));
        player_fourth_temp[i]->Set_Name("forth");
        player_fourth_temp[i]->Set_Tag("player");
        player_fourth_temp[i]->SetScale({ 3.f,3.f });
        //player_fourth_temp[i]->GetComponentByTemplate<Player>()->Set_This_UI_info(fourth_ui);
        player_fourth_temp[i]->Set_Dmg_Text(fourth_text);
    }


    for (int i = 0; i < item_num; i++)
    {
        item_save[i] = new Object();
        item_save[i]->AddComponent(new Sprite(item_save[i], "../Sprite/item.png", { 0,0 }, false));
        item_save[i]->AddComponent(new Item());
        item_save[i]->AddComponent(new Physics());
        item_save[i]->Set_Name("item");
        item_save[i]->Set_Tag("item");
        item_save[i]->SetTranslation({ 0,0 });
        item_save[i]->GetComponentByTemplate<Item>()->Set_Kind(Item::Item_Kind::Dash);
    }

    for (int i = 0; i < item_num; i++)
    {
        item_save_hp[i] = new Object();
        item_save_hp[i]->AddComponent(new Sprite(item_save_hp[i], "../Sprite/item.png", { 0,0 }, false));
        item_save_hp[i]->AddComponent(new Item());
        item_save_hp[i]->AddComponent(new Physics());
        item_save_hp[i]->Set_Name("item");
        item_save_hp[i]->Set_Tag("item");
        item_save_hp[i]->SetTranslation({ -400,0 });
        item_save_hp[i]->GetComponentByTemplate<Item>()->Set_Kind(Item::Item_Kind::HP);
    }

    for (int i = 0; i < item_num; i++)
    {
        item_bulk_up[i] = new Object();
        item_bulk_up[i]->AddComponent(new Sprite(item_bulk_up[i], "../Sprite/item.png", { 0,0 }, false));
        item_bulk_up[i]->AddComponent(new Item());
        item_bulk_up[i]->AddComponent(new Physics());
        item_bulk_up[i]->Set_Name("item");
        item_bulk_up[i]->Set_Tag("item");
        item_bulk_up[i]->SetTranslation({ 400,0 });
        item_bulk_up[i]->GetComponentByTemplate<Item>()->Set_Kind(Item::Item_Kind::Bulkup);
    }
}

void Referee::Update(float dt)
{
    if (!stage_statements.empty())
    {
        for (auto i : stage_statements)
        {
            if (i == PLAYER_SECOND_DIE && player_sec_life > 0)
            {
                player_second_respawn_timer -= dt;

                if (player_second_respawn_timer <= 0.0f)
                {
                    sound.Play(SOUND::Respawn);

                    player_second_respawn_timer = 3.0f;
                    Respawn(i);

                    player_sec_life--;
                    stage_statements.erase(std::find(stage_statements.begin(), stage_statements.end(), i));
                    second_ui->Get_Life_Num()->GetComponentByTemplate<TextComp>()->GetText().SetString(std::to_wstring(player_sec_life));
                }
            }
            if (i == PLAYER_FIRST_DIE && player_first_life > 0)
            {

                player_first_respawn_timer -= dt;

                if (player_first_respawn_timer <= 0.0f)
                {
                    sound.Play(SOUND::Respawn);

                    player_first_respawn_timer = 3.0f;
                    Respawn(i);

                    player_first_life--;
                    stage_statements.erase(std::find(stage_statements.begin(), stage_statements.end(), i));
                    first_ui->Get_Life_Num()->GetComponentByTemplate<TextComp>()->GetText().SetString(std::to_wstring(player_first_life));
                }
            }
            if (i == PLAYER_THIRD_DIE && player_third_life > 0)
            {

                player_third_respawn_timer -= dt;

                if (player_third_respawn_timer <= 0.0f)
                {
                    sound.Play(SOUND::Respawn);

                    player_third_respawn_timer = 3.0f;
                    Respawn(i);

                    player_third_life--;
                    stage_statements.erase(std::find(stage_statements.begin(), stage_statements.end(), i));
                    third_ui->Get_Life_Num()->GetComponentByTemplate<TextComp>()->GetText().SetString(std::to_wstring(player_third_life));
                }
            }
            if (i == PLAYER_FOURTH_DIE && player_fourth_life > 0)
            {

                player_fourth_respawn_timer -= dt;

                if (player_fourth_respawn_timer <= 0.0f)
                {
                    sound.Play(SOUND::Respawn);
                    player_fourth_respawn_timer = 3.0f;
                    Respawn(i);

                    player_fourth_life--;
                    stage_statements.erase(std::find(stage_statements.begin(), stage_statements.end(), i));
                    fourth_ui->Get_Life_Num()->GetComponentByTemplate<TextComp>()->GetText().SetString(std::to_wstring(player_fourth_life));
                }
            }
        }
    }
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

    if (this->GetComponentByTemplate<Collision>() != nullptr)
    {
        this->GetComponentByTemplate<Collision>()->Update(dt);
    }
}

void Referee::Delete()
{
}

void Referee::Respawn(Stage_Statement statement)
{
    switch (statement)
    {
    case PLAYER_SECOND_DIE:
		player_sec_temp[player_sec_life - 1]->AddComponent(new Player());
		player_sec_temp[player_sec_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(second_ui);
        ObjectManager::GetObjectManager()->AddObject(player_sec_temp[player_sec_life - 1]);
        second_ui->Reset();
        break;

    case PLAYER_FIRST_DIE:
		player_first_temp[player_first_life - 1]->AddComponent(new Player());
		player_first_temp[player_first_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(first_ui);
        ObjectManager::GetObjectManager()->AddObject(player_first_temp[player_first_life - 1]);
        first_ui->Reset();
        break;

    case PLAYER_THIRD_DIE:
		player_third_temp[player_third_life - 1]->AddComponent(new Player());
		player_third_temp[player_third_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(third_ui);
        ObjectManager::GetObjectManager()->AddObject(player_third_temp[player_third_life - 1]);
        third_ui->Reset();
        break;

    case PLAYER_FOURTH_DIE:
		player_fourth_temp[player_fourth_life - 1]->AddComponent(new Player());
		player_fourth_temp[player_fourth_life - 1]->GetComponentByTemplate<Player>()->Set_This_UI_info(fourth_ui);
        ObjectManager::GetObjectManager()->AddObject(player_fourth_temp[player_fourth_life - 1]);
        fourth_ui->Reset();
        break;
    }
}