/*
 * Author		:Suwhan Kim
 * File			:Level1.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:This file is for intialize the stuff required on the prototype.
 *				 There are Player objects, refree, items, text, ui information.
 *
 *				 copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include <fstream>
#include <sstream>
#include "Windows.h"
#include "Level1.h"
#include "Component_Collision.h"
#include "Referee.h"
#include "Component_Text.h"
#include "Engine.hpp"
#include "Loading_Scene.h"
using namespace std;

namespace
{
    Referee* referee = nullptr;

    ObjectManager* object_manager = nullptr;

}

void Level1::Load()
{
	Loading_Scene* loading = new Loading_Scene;
	loading->Load();

	std::thread loading_thread(&Loading_Scene::Update, loading, 0.5f);
	
    current_state = GameState::Game;
    referee = Referee::Get_Referee();

    object_manager = ObjectManager::GetObjectManager();
    Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);


    sound.Stop(SOUND::BGM);
    sound.Play(SOUND::BGM2);

    arena = new Object();
    arena->Set_Name("arena");
    arena->Set_Tag("arena");
    arena->AddComponent(new Sprite(arena, "../Sprite/IceGround.png", { 0,0 }, false));
    arena->SetScale({ 20, 20 });
    ObjectManager::GetObjectManager()->AddObject(arena);

    player = new Object();

    ifstream readFile("../Data/Objects/Objects.txt");

    if (readFile.is_open())
    {
        string line;
        string type;
        string objectType;
        string name;
        string locate;
        string animate;     
        int result = 0, frame = 0;
        float value_x = 0, value_y = 0;
        while (std::getline(readFile, line))
        {
            std::stringstream keystream(line);
            keystream >> type;

            if (type == "Type:")
            {
                keystream >> objectType;
                player->AddComponent(new Player());
                player->AddComponent(new Physics());
                player->Set_Tag(objectType);

            }
            else if (type == "Name:")
            {
                keystream >> name;
                player->Set_Name(name);
            }
            else if (type == "Sprite:")
            {
                keystream >> locate;
                keystream >> animate;
                keystream >> frame;

                if (animate == "true")
                {
                    result = 1;
                }
                else if (animate == "false")
                {
                    result = 0;
                }


                player->AddComponent(new Sprite(player, locate.c_str(), { value_x,value_y }));
                player->Set_path(locate);
                player->Set_AniState(animate);
                player->Set_Frame(frame);
            }
            else if (type == "Position:")
            {
                keystream >> value_x;
                keystream >> value_y;

                player->SetTranslation(vector2(value_x, value_y));
            }
            else if (type == "Scale:")
            {
                keystream >> value_x;
                keystream >> value_y;

                player->SetScale(vector2(value_x, value_y));
                result = 0; frame = 0; value_x = 0; value_y = 0;
            }
        }
    }

    ObjectManager::GetObjectManager()->AddObject(player);
	
    player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    player->GetTransform().SetScale({ 3.f, 3.f });
	
	player_sec = Make_Player("second", "player", "../sprite/pen_red.png", { 400.f, -400.f }, { 3.f, 3.f });
	player_third = Make_Player("third", "player", "../sprite/pen_purple.png", { -400.f, 400.f }, { 3.f, 3.f });
	player_forth = Make_Player("forth", "player", "../sprite/pen_normal.png", { -400.f, -400.f }, { 3.f, 3.f });

	text = Make_Set_Text("red_text", "text", { 200,0 }, player, { 0,1,0,1 }, { 150,150 }, &font);
	text_2 = Make_Set_Text("green_text", "text", { 200,-200 }, player_sec, { 1,0,0,1 }, { 150,150 }, &font);
	text_3 = Make_Set_Text("blue_text", "text", { 200,-400 }, player_third, { 0.54,0,1,1 }, { 150,150 }, &font);
	text_4 = Make_Set_Text("yellow_text", "text", { 200,-400 }, player_forth, { 0.5,0.5,0.5,1 }, { 150,150 }, &font);

	player_first_ui = Make_Set_Ui("first_ui", "ui", "../sprite/pen_green.png", { 1200, 800 }, { 4.0f,4.0f }, player);
	player_second_ui = Make_Set_Ui("second_ui", "ui", "../sprite/pen_red.png", { 1200, -600 }, { 4.0f,4.0f }, player_sec);
	player_third_ui = Make_Set_Ui("third_ui", "ui", "../sprite/pen_purple.png", { -1600, 800 }, { 4.0f,4.0f }, player_third);
	player_fourth_ui = Make_Set_Ui("fourth_ui", "ui", "../sprite/pen_normal.png", { -1600, -600 }, { 4.0f,4.0f }, player_forth);

    player->GetComponentByTemplate<Player>()->Set_This_UI_info(player_first_ui);
    player_sec->GetComponentByTemplate<Player>()->Set_This_UI_info(player_second_ui);
    player_third->GetComponentByTemplate<Player>()->Set_This_UI_info(player_third_ui);
    player_forth->GetComponentByTemplate<Player>()->Set_This_UI_info(player_fourth_ui);

    Referee::Get_Referee()->Set_First_Ui(player_first_ui);
    Referee::Get_Referee()->Set_Second_Ui(player_second_ui);
    Referee::Get_Referee()->Set_Third_Ui(player_third_ui);
    Referee::Get_Referee()->Set_Fourth_Ui(player_fourth_ui);

    Referee::Get_Referee()->Set_First_Text(text);
    Referee::Get_Referee()->Set_Second_Text(text_2);
    Referee::Get_Referee()->Set_Third_Text(text_3);
    Referee::Get_Referee()->Set_Fourth_Text(text_4);
	
	referee->AddComponent(new Collision());
    referee->Init();
	Graphic::GetGraphic()->get_need_update_sprite() = true;

	loading->Set_Done(false);

	if (loading_thread.joinable())
		loading_thread.join();
}

void Level1::Update(float dt)
{
    referee->Update(dt);
	
}