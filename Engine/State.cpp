#include "State.h"
#include "Object.h"
#include "Player_Ui.h"
#include "Component_Player.h"
#include "Component_Sprite.h"
#include "Physics.h"
#include "ObjectManager.h"


Object* State::Make_Player(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale)
{
	Object* player;
	player = new Object();
	player->Set_Name(name);
	player->Set_Tag(tag);
	player->AddComponent(new Player());
	player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
	player->AddComponent(new Sprite(player, sprite_path.c_str(), pos));
	player->AddComponent(new Physics());
	player->GetTransform().SetScale(scale);
	ObjectManager::GetObjectManager()->AddObject(player);

	return player;
}

PLAYER_UI* State::Make_Set_Ui(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale,
	Object* player)
{
	PLAYER_UI* player_ui;
	player_ui = new PLAYER_UI();
	player_ui->GetTransform().GetScale_Reference() = scale;
	player_ui->Set_Name(name);
	player_ui->Set_Tag(tag);
	player_ui->AddComponent(new Sprite(player_ui, sprite_path.c_str(), pos));
	player_ui->AddComponent(new Ui(player_ui));
	player_ui->Set_Bitmap_Font(&font);
	player_ui->Initialize();
	ObjectManager::GetObjectManager()->AddObject(player_ui);

	player->GetComponentByTemplate<Player>()->Set_This_UI_info(player_ui);

	return player_ui;
}
