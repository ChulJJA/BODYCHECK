#include "Testing_Level.h"
#include "Referee.h"
#include "ObjectManager.h"
#include "Graphic.h"
#include "Physics.h"
#include "Component_Sprite.h"
#include "Component_Text.h"
using namespace std;

namespace
{
	Referee* referee = nullptr;

	ObjectManager* object_manager = nullptr;

}

void Testing_Level::Load()
{
	current_state = GameState::Game;
	referee = Referee::Get_Referee();
	object_manager = ObjectManager::GetObjectManager();
	
	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);

	player = Make_Player("first", "player", "../sprite/pen_green.png", { 400.f, 400.f }, { 3.f, 3.f });
	player_first_ui = Make_Set_Ui("first_ui", "ui", "../sprite/pen_green.png", { 1200, 800 }, { 4.0f,4.0f }, player);

	Referee::Get_Referee()->Set_First_Ui(player_first_ui);

	text = new Object();
	text->SetTranslation({ 200,0 });
	text->AddComponent(new TextComp(text, L" ", { 0,1,0,1 }, { 150,150 }, font));
	text->Set_Name("red_text");
	text->Set_Tag("text");
	ObjectManager::GetObjectManager()->AddObject(text);
	player->Set_Dmg_Text(text);

	Referee::Get_Referee()->Set_First_Text(text);
	referee->Init();
}

void Testing_Level::Update(float dt)
{
	referee->Update(dt);
}