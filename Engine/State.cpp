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
	std::string path_to_player_state = "../Sprite/Player/State/";
	std::string path_to_player_item_effect = "../Sprite/Player/Item_Effect/";
	std::string path_to_player_display_item = "../Sprite/Player/Display_Item/";

	std::string sprite_path_normal = path_to_player_state;
	std::string sprite_path_lock = path_to_player_state;
	std::string sprite_path_chase = path_to_player_state;
	std::string sprite_path_thinking = path_to_player_state;
	std::string sprite_path_crying = path_to_player_state;
	
	std::string sprite_path_reverse_moving_pen = path_to_player_item_effect;
	std::string sprite_path_ready = path_to_player_item_effect;
	std::string sprite_path_heal_effect = path_to_player_item_effect;
	std::string sprite_path_ready_bulkup = path_to_player_item_effect;
	std::string sprite_path_throwing_effect = path_to_player_item_effect;
	std::string sprite_path_missile_effect = path_to_player_item_effect;
	
	std::string sprite_path_missile_launcher = path_to_player_display_item;
	std::string sprite_path_dash = path_to_player_display_item;
	std::string sprite_path_bulkup = path_to_player_display_item;
	std::string sprite_path_throwing = path_to_player_display_item;
	std::string sprite_path_heal = path_to_player_display_item;
	std::string sprite_path_magnet = path_to_player_display_item;


	{
		sprite_path_normal += sprite_path + ".png";
		sprite_path_lock += sprite_path + "_lock.png";
		sprite_path_chase += sprite_path + "_chase.png";
		sprite_path_thinking += sprite_path + "_thinking.png";
		sprite_path_crying += sprite_path + "_crying.png";
	}
	
	{
		sprite_path_reverse_moving_pen += "reverse_moving_pen.png";
		sprite_path_ready += "loadingscene.png";
		sprite_path_heal_effect += "effect_heal.png";
		sprite_path_ready_bulkup += sprite_path + "_effect_bulkup.png";
		sprite_path_throwing_effect += "effect_throwing.png";
		sprite_path_missile_effect += "pen_green_effect_missile.png";
	}

	{
		sprite_path_missile_launcher += "missile_launcher_showing.png";
		sprite_path_dash += "dash_showing.png";
		sprite_path_bulkup += "bulkup_showing.png";
		sprite_path_throwing += "throwing_showing.png";
		sprite_path_heal += "heal_showing.png";
		sprite_path_magnet += "magnet_showing.png";
	}
	
	Object* player;
	player = new Object();
	player->Set_Name(name);
	player->Set_Tag(tag);
	player->SetNeedCollision(true);
	player->AddComponent(new Player());
	player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);


	player->AddComponent(new Sprite(player, sprite_path_normal.c_str(), pos, false, Sprite_Type::Player_Normal), "normal", true);
	player->AddComponent(new Sprite(player, sprite_path_lock.c_str(), pos, false, Sprite_Type::Player_Locking), "lock", false);
	player->AddComponent(new Sprite(player, sprite_path_chase.c_str(), pos, false, Sprite_Type::Player_Chasing), "chase", false);
	player->AddComponent(new Sprite(player, sprite_path_thinking.c_str(), pos, false, Sprite_Type::Player_Thinking), "thinking", false);
	player->AddComponent(new Sprite(player, sprite_path_reverse_moving_pen.c_str(), pos, false, Sprite_Type::Player_Reverse_Moving), "reverse_moving_pen", false);
	player->AddComponent(new Sprite(player, sprite_path_ready.c_str(), pos, false, Sprite_Type::Player_Ready), "ready", false);
	player->AddComponent(new Sprite(player, sprite_path_crying.c_str(), pos, false, Sprite_Type::Player_Crying), "crying", false);

	
	player->AddComponent(new Sprite(player, sprite_path_missile_launcher.c_str(), pos, false, Sprite_Type::Missile_Launcher_Showing, { 80.f, 80.f }), "missile_launcher", false);
	player->AddComponent(new Sprite(player, sprite_path_dash.c_str(), pos, false, Sprite_Type::Dash_Showing, { 50.f, 50.f }), "dash", false);
	player->AddComponent(new Sprite(player, sprite_path_bulkup.c_str(), pos, false, Sprite_Type::Bulkup_Showing, { 100.f, 100.f }), "bulkup", false);
	player->AddComponent(new Sprite(player, sprite_path_throwing.c_str(), pos, false, Sprite_Type::Throwing_Showing, { 100.f, 100.f }), "throwing", false);
	player->AddComponent(new Sprite(player, sprite_path_heal.c_str(), pos, false, Sprite_Type::Heal_Showing, { 100.f, 100.f }), "heal", false);
	player->AddComponent(new Sprite(player, sprite_path_magnet.c_str(), pos, false, Sprite_Type::Magnet_Showing, { 100.f, 100.f }), "magnet", false);

	
	player->AddComponent(new Sprite(player, sprite_path_ready_bulkup.c_str(), true, 8, 24, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Effect_Bulkp), "effect_bulkup", false);
	player->AddComponent(new Sprite(player, sprite_path_heal_effect.c_str(), true, 4, 6, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Heal), "effect_heal", false);
	player->AddComponent(new Sprite(player, sprite_path_throwing_effect.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Throwing), "effect_throwing", false);
	player->AddComponent(new Sprite(player, sprite_path_missile_effect.c_str(), true, 8, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Missile), "effect_missile", false);

	
	player->AddComponent(new Physics());
	player->Set_Current_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
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