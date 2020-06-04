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
	//std::string path_to_player_display_item = "../Sprite/Player/Display_Item/";

	std::string sprite_path_normal = path_to_player_state;
	std::string sprite_path_lock = path_to_player_state;
	std::string sprite_path_crying = path_to_player_state;
	std::string sprite_path_die = path_to_player_state;
	std::string sprite_path_paused = path_to_player_state;
	std::string sprite_path_speed2 = path_to_player_state;
	std::string sprite_path_speed3 = path_to_player_state;
	std::string sprite_path_fat = path_to_player_state;
	std::string sprite_path_spawn = path_to_player_state;

	
	std::string sprite_path_reverse_moving_pen = path_to_player_item_effect;
	std::string sprite_path_ready = path_to_player_item_effect;
	std::string sprite_path_heal_effect = path_to_player_item_effect;
	std::string sprite_path_ready_bulkup = path_to_player_item_effect;
	std::string sprite_path_bulkup_used = path_to_player_item_effect;
	std::string sprite_path_throwing_effect = path_to_player_item_effect;
	std::string sprite_path_missile_effect = path_to_player_item_effect;
	std::string sprite_path_magnet_aiming = path_to_player_item_effect;
	std::string sprite_path_magnet_chasing = path_to_player_item_effect;
	std::string sprite_path_dash_effect = path_to_player_item_effect;
	std::string sprite_path_timestop_effect = path_to_player_item_effect;
	
	//std::string sprite_path_missile_launcher = path_to_player_display_item;
	//std::string sprite_path_dash = path_to_player_display_item;
	//std::string sprite_path_bulkup = path_to_player_display_item;
	//std::string sprite_path_throwing = path_to_player_display_item;
	//std::string sprite_path_heal = path_to_player_display_item;
	//std::string sprite_path_magnet = path_to_player_display_item;
	//std::string sprite_path_timestop = path_to_player_display_item;
	//std::string sprite_path_reverse = path_to_player_display_item;


	{
		sprite_path_normal += sprite_path + ".png";
		sprite_path_lock += sprite_path + "_lock.png";
		sprite_path_crying += sprite_path + "_hit.png";
		sprite_path_die += sprite_path + "_die.png";
		sprite_path_paused += sprite_path + "_paused.png";
		sprite_path_speed2 += sprite_path + "_speed2.png";
		sprite_path_speed3 += sprite_path + "_speed3.png";
		sprite_path_fat += sprite_path + "_fat.png";
		sprite_path_spawn += sprite_path + "_spawn.png";

		//sprite_path_fat += "pen_special.png";
	}

	//itwem effect
	{
		sprite_path_reverse_moving_pen += sprite_path + "_reverse.png";
		sprite_path_ready += "loadingscene.png";
		sprite_path_heal_effect += "heal_effect.png";
		sprite_path_ready_bulkup += sprite_path + "_bulkupready.png";
		sprite_path_bulkup_used += sprite_path + "_bulkup.png";
		sprite_path_throwing_effect += "effect_throwing.png";
		sprite_path_missile_effect += sprite_path + "_missile_ready.png";
		sprite_path_magnet_aiming += sprite_path + "_magnet_aiming.png";
		sprite_path_magnet_chasing += sprite_path + "_chasing.png";
		sprite_path_dash_effect += sprite_path + "_dash_effect.png";
		sprite_path_timestop_effect += sprite_path + "_timestop.png";
	}

	{
		//sprite_path_missile_launcher += "missile_launcher_showing.png";
		//sprite_path_dash += sprite_path + "_dash_display.png";
		//sprite_path_bulkup += "bulkup_display.png";
		//sprite_path_throwing += "throwing_display.png";
		//sprite_path_heal += "heal_showing.png";
		//sprite_path_magnet += "magnet_display.png";
		//sprite_path_timestop += "time_stop_display.png";
		//sprite_path_reverse += "reverse_display.png";
	}
	
	Object* player;
	player = new Object();
	player->SetTranslation(pos);
	player->Set_Name(name);
	player->Set_Tag(tag);
	player->SetNeedCollision(true);
	player->AddComponent(new Player(), "player");
	player->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);



	player->AddComponent(new Sprite(player, sprite_path_spawn.c_str(), true, 37, 9.25, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Spawn), "spawn", true);
	
	player->AddComponent(new Sprite(player, sprite_path_normal.c_str(), true, 3, 6, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Normal), "normal", false);

	player->AddComponent(new Sprite(player, sprite_path_speed2.c_str(), true, 3, 24, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Speed2), "speed2", false);

	player->AddComponent(new Sprite(player, sprite_path_speed3.c_str(), true, 3, 48, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Speed3), "speed3", false);
	
	player->AddComponent(new Sprite(player, sprite_path_lock.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Locking), "lock", false);
	
	player->AddComponent(new Sprite(player, sprite_path_ready.c_str(), pos, false, Sprite_Type::Player_Ready), "ready", false);
	
	player->AddComponent(new Sprite(player, sprite_path_die.c_str(), true, 8, 16, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Die), "die", false);
	
	player->AddComponent(new Sprite(player, sprite_path_crying.c_str(), true, 2, 4, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Crying), "crying", false);
	
	player->AddComponent(new Sprite(player, sprite_path_fat.c_str(), true, 3, 9, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Fat), "fat", false);


	player->AddComponent(new Sprite(player, sprite_path_reverse_moving_pen.c_str(), true, 2, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Reverse_Moving), "reverse", false);
	
	/*player->AddComponent(new Sprite(player, sprite_path_missile_launcher.c_str(), pos, false, Sprite_Type::Missile_Launcher_Showing, { 80.f, 80.f }), "missile_launcher", false);

	player->AddComponent(new Sprite(player, sprite_path_dash.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Dash_Showing), "dash", false);*/

	player->AddComponent(new Sprite(player, sprite_path_timestop_effect.c_str(), true, 4, 8, pos, { 200.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Effect_Timestop), "time", false);

	
	//player->AddComponent(new Sprite(player, sprite_path_bulkup.c_str(), pos, false, Sprite_Type::Bulkup_Showing, { 100.f, 100.f }), "bulkup", false);
	//player->AddComponent(new Sprite(player, sprite_path_throwing.c_str(), pos, false, Sprite_Type::Throwing_Showing, { 100.f, 100.f }), "throwing", false);
	//player->AddComponent(new Sprite(player, sprite_path_heal.c_str(), pos, false, Sprite_Type::Heal_Showing, { 100.f, 100.f }), "heal", false);
	//player->AddComponent(new Sprite(player, sprite_path_magnet.c_str(), pos, false, Sprite_Type::Magnet_Showing, { 100.f, 100.f }), "magnet", false);
	//player->AddComponent(new Sprite(player, sprite_path_timestop.c_str(), pos, false, Sprite_Type::Timestop_Showing, { 100.f, 100.f }), "time", false);
	//player->AddComponent(new Sprite(player, sprite_path_reverse.c_str(), pos, false, Sprite_Type::Reverse_Showing, { 100.f, 100.f }), "reverse", false);
	player->AddComponent(new Sprite(player, sprite_path_paused.c_str(), pos, false, Sprite_Type::Player_Paused, { 100.f, 100.f }), "paused", false);


	/*player->AddComponent(new Sprite(player, sprite_path_heal.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Heal_Showing), "heal", false);*/
	
	
	player->AddComponent(new Sprite(player, sprite_path_ready_bulkup.c_str(), true, 8, 16, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Effect_Bulkp), "effect_bulkup", false);

	player->AddComponent(new Sprite(player, sprite_path_bulkup_used.c_str(), true, 3, 9, pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Bulkup_Used), "effect_bulkup_use", false);
	
	
	player->AddComponent(new Sprite(player, sprite_path_heal_effect.c_str(), true, 6, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Heal), "effect_heal", false);
	player->AddComponent(new Sprite(player, sprite_path_throwing_effect.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Throwing), "effect_throwing", false);
	player->AddComponent(new Sprite(player, sprite_path_missile_effect.c_str(), true, 8, 16, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Missile), "effect_missile", false);

	player->AddComponent(new Sprite(player, sprite_path_magnet_aiming.c_str(), true, 4, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Aiming), "aiming", false);
	player->AddComponent(new Sprite(player, sprite_path_magnet_chasing.c_str(), true, 2, 16, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Chasing), "chasing", false);


	player->AddComponent(new Sprite(player, sprite_path_dash_effect.c_str(), true, 4, 8, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Player_Effect_Dash), "effect_dash", false);
	
	player->AddComponent(new Physics(), "physics");
	player->Set_Current_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Spawn));
	player->GetTransform().SetScale(scale);

	if (name == "first")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_green");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}
	else if (name == "second")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_red");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}
	else if (name == "third")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_blue");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}
	else if (name == "fourth")
	{
		Object* aud = ObjectManager::GetObjectManager()->Find_Object_By_Name("audience_normal");
		player->GetComponentByTemplate<Player>()->Set_Audience(aud);
	}

	ObjectManager::GetObjectManager()->AddObject(player);

	return player;
}

PLAYER_UI* State::Make_Set_Ui(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale,
	Object* player)
{
	PLAYER_UI* player_ui;
	player_ui = new PLAYER_UI();
	player_ui->SetNeedCollision(false);
	player_ui->GetTransform().GetScale_Reference() = scale;
	player_ui->Set_Name(name);
	player_ui->Set_Tag(tag);
	player_ui->AddComponent(new Sprite(player_ui, sprite_path.c_str(), pos));
	player_ui->AddComponent(new Ui(player_ui));
	player_ui->Set_Bitmap_Font(&font);
	player_ui->Initialize();
	ObjectManager::GetObjectManager()->AddObject(player_ui);

	//player->GetComponentByTemplate<Player>()->Set_This_UI_info(player_ui);

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