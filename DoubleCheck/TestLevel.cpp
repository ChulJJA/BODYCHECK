/*
 * Author		:Chulseung Lee
 * File			:TestLevel.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/02/17
 * Description	:It is designed to test the bugs.
 *
 *				 copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Windows.h"
#include "Component_Collision.h"
#include "Referee.h"
#include "Component_Text.h"
#include "Player_Ui.h"
#include "TestLevel.h"

using namespace std;

namespace
{
    Referee* referee = nullptr;

    ObjectManager* object_manager = nullptr;

}

void TestLevel::Load()
{
    current_state = GameState::TestLevel;
    referee = Referee::Get_Referee();

    object_manager = ObjectManager::GetObjectManager();
    Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);

    SetArena();
    SetFirstPlayer();
    //SetSecondPlayer();
    //SetThirdPlayer();
    //SetFourthPlayer();
	
    //player_sec = new Object();
    //player_sec->Set_Name("second");
    //player_sec->Set_Tag("player");
    //player_sec->AddComponent(new Player());
    //player_sec->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    //player_sec->AddComponent(new Sprite(player_sec, "../Sprite/pen_red.png", { 400,-400 }));
    //player_sec->AddComponent(new Physics());
    //player_sec->GetTransform().SetScale({ 3.f,3.f });
    //ObjectManager::GetObjectManager()->AddObject(player_sec);

    //player_third = new Object();
    //player_third->Set_Name("third");
    //player_third->Set_Tag("player");
    //player_third->AddComponent(new Player());
    //player_third->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    //player_third->AddComponent(new Sprite(player_third, "../Sprite/pen_purple.png", { -400,400 }));
    //player_third->AddComponent(new Physics());
    //player_third->GetTransform().SetScale({ 3.f,3.f });
    //ObjectManager::GetObjectManager()->AddObject(player_third);

    //b = new Object();
    //ObjectManager::GetObjectManager()->AddObject(b);
    //b->AddComponent(new Sprite(b, "../Sprite/pen_purple.png", { -400,400 }));
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);
    //ObjectManager::GetObjectManager()->AddObject(b);

    //std::cout << object_manager->GetObjectManagerContainer().size();

    //Graphic::GetGraphic()->get_need_update_sprite() = true;
}

void TestLevel::Update(float dt)
{
}

void TestLevel::SetArena()
{
    //arena = new Object();
    //arena->Set_Name("arena");
    //arena->Set_Tag("arena");
    //arena->AddComponent(new Sprite(arena, "../Sprite/IceGround.png", { 0,0 }, false));
    //arena->SetScale({ 20, 20 });
    //ObjectManager::GetObjectManager()->AddObject(arena);
}

void TestLevel::SetFirstPlayer()
{
    first_player = new Object();
    first_player->Set_Name("first");
    first_player->Set_Tag("player");
    first_player->AddComponent(new Player());
    first_player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    first_player->AddComponent(new Sprite(first_player, "../Sprite/pen_red.png", { 400,400 }));
    first_player->AddComponent(new Physics());
    first_player->GetTransform().SetScale({ 3.f,3.f });
	
    ObjectManager::GetObjectManager()->AddObject(first_player);
}

void TestLevel::SetSecondPlayer()
{
    second_player = new Object();
    second_player->Set_Name("second");
    second_player->Set_Tag("player");
    second_player->AddComponent(new Player());
    second_player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    second_player->AddComponent(new Sprite(second_player, "../Sprite/pen_red.png", { -400,400 }));
    second_player->AddComponent(new Physics());
    second_player->GetTransform().SetScale({ 3.f,3.f });

    ObjectManager::GetObjectManager()->AddObject(second_player);
}

void TestLevel::SetThirdPlayer()
{
    third_player = new Object();
    third_player->Set_Name("third");
    third_player->Set_Tag("player");
    third_player->AddComponent(new Player());
    third_player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    third_player->AddComponent(new Sprite(third_player, "../Sprite/pen_red.png", { 400,-400 }));
    third_player->AddComponent(new Physics());
    third_player->GetTransform().SetScale({ 3.f,3.f });

    ObjectManager::GetObjectManager()->AddObject(third_player);
}

void TestLevel::SetFourthPlayer()
{
    fourth_player = new Object();
    fourth_player->Set_Name("fourth");
    fourth_player->Set_Tag("player");
    fourth_player->AddComponent(new Player());
    fourth_player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
    fourth_player->AddComponent(new Sprite(fourth_player, "../Sprite/pen_red.png", { -400,-400 }));
    fourth_player->AddComponent(new Physics());
    fourth_player->GetTransform().SetScale({ 3.f,3.f });

    ObjectManager::GetObjectManager()->AddObject(fourth_player);
}
