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
#include "Player_Ui.h"
#include "Engine.hpp"

using namespace std;

namespace
{
    Referee* referee = nullptr;

    ObjectManager* object_manager = nullptr;

}

void Level1::Load()
{
    current_state = GameState::Game;
    referee = Referee::Get_Referee();

    object_manager = ObjectManager::GetObjectManager();
    Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);

    sound.stop(SOUND::BGM);
    sound.play(SOUND::BGM2);
    sound.SetVolume(SOUND::BGM2, 0.3);

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

    ofstream fileOut;
    player->Get_Is_Debugmode();
    fileOut.open("../Data/Objects/Objects.txt");
    if (fileOut.fail())
    {
        cout << "Can't read the file " << endl;
    }

    fileOut << "Type: " << player->Get_Tag() << endl;
    fileOut << "Name: " << player->Get_Name() << endl;
    fileOut << "Sprite: " << player->Get_Path() << " ";
    fileOut << player->Get_AnimateState() << " ";
    fileOut << player->Get_Frame() << endl;
    fileOut << "Position: " << player->GetTransform().GetTranslation_Reference().x << " ";
    fileOut << player->GetTransform().GetTranslation_Reference().y << endl;
    fileOut << "Scale: " << player->GetTransform().GetScale_Reference().x << " ";
    fileOut << player->GetTransform().GetScale_Reference().y << endl;
    player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    fileOut.close();
    player->GetTransform().SetScale({ 3, 3 });

    player_sec = new Object();
    player_sec->Set_Name("second");
    player_sec->Set_Tag("player");
    player_sec->AddComponent(new Player());
    player_sec->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    player_sec->AddComponent(new Sprite(player_sec, "../Sprite/pen_red.png", { 400,-400 }));
    player_sec->AddComponent(new Physics());
    player_sec->GetTransform().SetScale({ 3.f,3.f });
    ObjectManager::GetObjectManager()->AddObject(player_sec);

    player_third = new Object();
    player_third->Set_Name("third");
    player_third->Set_Tag("player");
    player_third->AddComponent(new Player());
    player_third->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    player_third->AddComponent(new Sprite(player_third, "../Sprite/pen_purple.png", { -400,400 }));
    player_third->AddComponent(new Physics());
    player_third->GetTransform().SetScale({ 3.f,3.f });
    ObjectManager::GetObjectManager()->AddObject(player_third);

    player_forth = new Object();
    player_forth->Set_Name("forth");
    player_forth->Set_Tag("player");
    player_forth->AddComponent(new Player());
    player_forth->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    player_forth->AddComponent(new Sprite(player_forth, "../Sprite/pen_normal.png", { -400,-400 }));
    player_forth->AddComponent(new Physics());
    player_forth->GetTransform().SetScale({ 3.f,3.f });
    ObjectManager::GetObjectManager()->AddObject(player_forth);

    referee->AddComponent(new Collision());

    if (!font.LoadFromFile(L"../assets/malgungothic.fnt"))
    {
        std::cout << "Failed to Load Font!" << std::endl;
    }

    text = new Object();
    text->SetTranslation({ 200,0 });
    text->AddComponent(new TextComp(text, L" ", { 0,1,0,1 }, { 150,150 }, font));
    text->Set_Name("red_text");
    text->Set_Tag("text");
    ObjectManager::GetObjectManager()->AddObject(text);
    player->Set_Dmg_Text(text);

    Object* text_2 = new Object();
    text_2->SetTranslation({ 200,-200 });
    text_2->AddComponent(new TextComp(text_2, L" ", { 1,0,0,1 }, { 150,150 }, font));
    text_2->Set_Name("green_text");
    text_2->Set_Tag("text");
    ObjectManager::GetObjectManager()->AddObject(text_2);
    player_sec->Set_Dmg_Text(text_2);

    Object* text_3 = new Object();
    text_3->SetTranslation({ 200,-400 });
    text_3->AddComponent(new TextComp(text_3, L" ", { 0.54,0,1,1 }, { 150,150 }, font));
    text_3->Set_Name("blue_text");
    text_3->Set_Tag("text");
    ObjectManager::GetObjectManager()->AddObject(text_3);
    player_third->Set_Dmg_Text(text_3);

    Object* text_4 = new Object();
    text_4->SetTranslation({ 200,-400 });
    text_4->AddComponent(new TextComp(text_4, L" ", { 0.5,0.5,0.5,1 }, { 150,150 }, font));
    text_4->Set_Name("yellow_text");
    text_4->Set_Tag("text");
    ObjectManager::GetObjectManager()->AddObject(text_4);
    player_forth->Set_Dmg_Text(text_4);

    player_first_ui = new PLAYER_UI();
    player_first_ui->GetTransform().GetScale_Reference() = { 4.0f,4.0f };
    player_first_ui->Set_Name("first_ui");
    player_first_ui->Set_Tag("ui");
    player_first_ui->AddComponent(new Sprite(player_first_ui, "../sprite/pen_green.png", { 1200, 800 }));
    player_first_ui->Set_Bitmap_Font(&font);
    player_first_ui->Initialize();
    ObjectManager::GetObjectManager()->AddObject(player_first_ui);

    player_second_ui = new PLAYER_UI();
    player_second_ui->GetTransform().GetScale_Reference() = { 4.0f,4.0f };
    player_second_ui->Set_Name("second_ui");
    player_second_ui->Set_Tag("ui");
    player_second_ui->AddComponent(new Sprite(player_second_ui, "../sprite/pen_red.png", { 1200, -600 }));
    player_second_ui->Set_Bitmap_Font(&font);
    player_second_ui->Initialize();
    ObjectManager::GetObjectManager()->AddObject(player_second_ui);

    player_third_ui = new PLAYER_UI();
    player_third_ui->GetTransform().GetScale_Reference() = { 4.0f,4.0f };
    player_third_ui->Set_Name("third_ui");
    player_third_ui->Set_Tag("ui");
    player_third_ui->AddComponent(new Sprite(player_third_ui, "../sprite/pen_purple.png", { -1600, 800 }));
    player_third_ui->Set_Bitmap_Font(&font);
    player_third_ui->Initialize();
    ObjectManager::GetObjectManager()->AddObject(player_third_ui);

    player_fourth_ui = new PLAYER_UI();
    player_fourth_ui->GetTransform().GetScale_Reference() = { 4.0f,4.0f };
    player_fourth_ui->Set_Name("fourth_ui");
    player_fourth_ui->Set_Tag("ui");
    player_fourth_ui->AddComponent(new Sprite(player_fourth_ui, "../sprite/pen_normal.png", { -1600, -600 }));
    player_fourth_ui->Set_Bitmap_Font(&font);
    player_fourth_ui->Initialize();
    ObjectManager::GetObjectManager()->AddObject(player_fourth_ui);

    player->GetComponentByTemplate<Player>()->Set_This_UI_info(player_first_ui);
    player_sec->GetComponentByTemplate<Player>()->Set_This_UI_info(player_second_ui);
    player_third->GetComponentByTemplate<Player>()->Set_This_UI_info(player_third_ui);
    player_forth->GetComponentByTemplate<Player>()->Set_This_UI_info(player_fourth_ui);

    Graphic::GetGraphic()->get_need_update_sprite() = true;

    Referee::Get_Referee()->Set_First_Ui(player_first_ui);
    Referee::Get_Referee()->Set_Second_Ui(player_second_ui);
    Referee::Get_Referee()->Set_Third_Ui(player_third_ui);
    Referee::Get_Referee()->Set_Fourth_Ui(player_fourth_ui);

    Referee::Get_Referee()->Set_First_Text(text);
    Referee::Get_Referee()->Set_Second_Text(text_2);
    Referee::Get_Referee()->Set_Third_Text(text_3);
    Referee::Get_Referee()->Set_Fourth_Text(text_4);

    referee->Init();
}

void Level1::Update(float dt)
{
    referee->Update(dt);
}