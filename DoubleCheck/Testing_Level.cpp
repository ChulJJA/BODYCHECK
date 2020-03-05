#include "Testing_Level.h"
#include "Referee.h"
#include "ObjectManager.h"
#include "Graphic.h"
#include "Component_Player.h"

#include <fstream>
#include <sstream>
#include "Physics.h"
#include "Component_Sprite.h"
#include "Component_Text.h"
#include "Player_Ui.h"
#include "Component_Collision.h"
#include "Component_Ui.h"
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
	referee->AddComponent(new Collision());
	referee->Init();
}

void Testing_Level::Update(float dt)
{
	referee->Update(dt);
}

//Object* Testing_Level::Make_Player(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale)
//{
//	Object* player;
//	player = new Object();
//	player->Set_Name(name);
//	player->Set_Tag(tag);
//	player->AddComponent(new Player());
//	player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
//	player->AddComponent(new Sprite(player, sprite_path.c_str(), pos));
//	player->AddComponent(new Physics());
//	player->GetTransform().SetScale(scale);
//	ObjectManager::GetObjectManager()->AddObject(player);
//
//	return player;
//}
//
//PLAYER_UI* Testing_Level::Make_Set_Ui(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale, Object* player)
//{
//	PLAYER_UI* player_ui;
//	player_ui = new PLAYER_UI();
//	player_ui->GetTransform().GetScale_Reference() = scale;
//	player_ui->Set_Name(name);
//	player_ui->Set_Tag(tag);
//	player_ui->AddComponent(new Sprite(player_ui, sprite_path.c_str(), pos));
//	player_ui->AddComponent(new Ui(player_ui));
//	player_ui->Set_Bitmap_Font(&font);
//	player_ui->Initialize();
//	ObjectManager::GetObjectManager()->AddObject(player_ui);
//	
//	player->GetComponentByTemplate<Player>()->Set_This_UI_info(player_ui);
//	
//	return player_ui;
//}
