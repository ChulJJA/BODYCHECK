#include "State.h"
#include "Object.h"
#include "Player_Ui.h"
#include "Component_Player.h"
#include "Component_Sprite.h"
#include "Physics.h"
#include "ObjectManager.h"
#include "Component_Text.h"


Object* State::Make_Player(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale)
{
	std::string sprite_path_normal = "../Sprite/";
	sprite_path_normal += sprite_path;
	sprite_path_normal += ".png";

	std::string sprite_path_lock = "../Sprite/";
	sprite_path_lock += sprite_path;
	sprite_path_lock += "_lock.png";

	std::string sprite_path_chase = "../Sprite/";
	sprite_path_chase += sprite_path;
	sprite_path_chase += "_chase.png";

	std::string sprite_path_thinking = "../Sprite/";
	sprite_path_thinking += sprite_path;
	sprite_path_thinking += "_thinking.png";

	std::string sprite_path_reverse_moving_pen = "../Sprite/reverse_moving_pen";
	sprite_path_reverse_moving_pen += ".png";

	std::string sprite_path_ready = "../Sprite/loadingscene.png";
	std::string sprite_path_heal_effect = "../Sprite/effect_heal.png";

	std::string sprite_path_ready_bulkup = "../Sprite/";
	sprite_path_ready_bulkup += sprite_path;
	sprite_path_ready_bulkup += "_effect_bulkup.png";

	
	Object* player;
	player = new Object();
	player->Set_Name(name);
	player->Set_Tag(tag);
	player->AddComponent(new Player());
	player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
	player->AddComponent(new Sprite(player, sprite_path_normal.c_str(), pos), "normal", true);
	player->AddComponent(new Sprite(player, sprite_path_lock.c_str(), pos), "lock", false);
	player->AddComponent(new Sprite(player, sprite_path_chase.c_str(), pos), "chase", false);
	player->AddComponent(new Sprite(player, sprite_path_thinking.c_str(), pos), "thinking", false);
	player->AddComponent(new Sprite(player, sprite_path_reverse_moving_pen.c_str(), pos), "reverse_moving_pen", false);
	player->AddComponent(new Sprite(player, sprite_path_ready.c_str(), pos), "ready", false);
	player->AddComponent(new Sprite(player, sprite_path_ready_bulkup.c_str(), true, 8, 24, pos, {100.f,100.f}, 
		{255,255,255,255}), "effect_bulkup", false);
	player->AddComponent(new Sprite(player, sprite_path_heal_effect.c_str(), true, 4, 6, pos, { 100.f,100.f },
	{255, 255, 255, 255}), "effect_heal", false);
	
	player->AddComponent(new Physics());
	player->Set_Current_Sprite(player->Find_Sprite_By_Name("normal"));
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