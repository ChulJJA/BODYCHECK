#include "Audience.h"
#include "Component_Sprite.h"
#include "ObjectManager.h"

Object* Get_Audience()
{
	//Object* aud = new Object;

	Object* aud_red = new Object;
	Object* aud_green = new Object;
	Object* aud_blue = new Object;
	Object* aud_normal = new Object;


	aud_red->Set_Name("audience_red");
	aud_red->Set_Tag("audience");
	aud_green->Set_Name("audience_green");
	aud_green->Set_Tag("audience");
	aud_blue->Set_Name("audience_blue");
	aud_blue->Set_Tag("audience");
	aud_normal->Set_Name("audience_normal");
	aud_normal->Set_Tag("audience");

	vector2 pos = { -1200.f,950.f };

	aud_red->AddComponent(new Sprite(aud_red, "../Sprite/Player/Audience/aud_red_normal.png", true, 4, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Normal), "aud_red", true);
	aud_red->AddComponent(new Sprite(aud_red, "../Sprite/Player/Audience/aud_red_joy.png", true, 4, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Joy), "aud_red", false);
	aud_red->AddComponent(new Sprite(aud_red, "../Sprite/Player/Audience/aud_red_sad.png", true, 4, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Sad), "aud_red", false);

	aud_green->AddComponent(new Sprite(aud_green, "../Sprite/Player/Audience/aud_green_normal.png", true, 4, 12, { pos.x + 800.f, pos.y}, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Normal), "aud_green", true);
	aud_green->AddComponent(new Sprite(aud_green, "../Sprite/Player/Audience/aud_green_joy.png", true, 4, 12, { pos.x + 800.f, pos.y }, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Joy), "aud_green", false);
	aud_green->AddComponent(new Sprite(aud_green, "../Sprite/Player/Audience/aud_green_sad.png", true, 4, 12, { pos.x + 800.f, pos.y }, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Sad), "aud_green", false);

	aud_blue->AddComponent(new Sprite(aud_blue, "../Sprite/Player/Audience/aud_blue_normal.png", true, 4, 12, { pos.x + 1600.f, pos.y }, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Normal), "aud_blue", true);
	aud_blue->AddComponent(new Sprite(aud_blue, "../Sprite/Player/Audience/aud_blue_joy.png", true, 4, 12, { pos.x + 1600.f, pos.y }, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Joy), "aud_blue", false);
	aud_blue->AddComponent(new Sprite(aud_blue, "../Sprite/Player/Audience/aud_blue_sad.png", true, 4, 12, { pos.x + 1600.f, pos.y }, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Sad), "aud_blue", false);


	aud_normal->AddComponent(new Sprite(aud_normal, "../Sprite/Player/Audience/aud_normal_normal.png", true, 4, 12, { pos.x + 2400.f, pos.y }, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Normal), "aud_normal", true);
	aud_normal->AddComponent(new Sprite(aud_normal, "../Sprite/Player/Audience/aud_normal_joy.png", true, 4, 12, { pos.x + 2400.f, pos.y }, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Joy), "aud_normal", false);
	aud_normal->AddComponent(new Sprite(aud_normal, "../Sprite/Player/Audience/aud_normal_sad.png", true, 4, 12, { pos.x + 2400.f, pos.y }, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Sad), "aud_normal", false);

	vector2 aud_scale{ 8.f, 8.f };

	aud_red->GetTransform().SetScale(aud_scale);
	aud_green->GetTransform().SetScale(aud_scale);
	aud_blue->GetTransform().SetScale(aud_scale);
	aud_normal->GetTransform().SetScale(aud_scale);


	ObjectManager::GetObjectManager()->AddObject(aud_red);
	ObjectManager::GetObjectManager()->AddObject(aud_green);
	ObjectManager::GetObjectManager()->AddObject(aud_blue);
	ObjectManager::GetObjectManager()->AddObject(aud_normal);


	/*aud->Set_Name("audience");
	aud->Set_Tag("audience");
	aud->AddComponent(new Sprite(aud, "../Sprite/Player/Audience/Audience.png", true, 3, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Normal), "aud_normal", true);
	
	aud->AddComponent(new Sprite(aud, "../Sprite/Player/Audience/Audience_pen_red_good.png", true, 3, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Red_Good), "aud_normal", false);
	aud->AddComponent(new Sprite(aud, "../Sprite/Player/Audience/Audience_pen_blue_good.png", true, 3, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Blue_Good), "aud_normal", false);
	aud->AddComponent(new Sprite(aud, "../Sprite/Player/Audience/Audience_pen_green_good.png", true, 3, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Green_Good), "aud_normal", false);
	aud->AddComponent(new Sprite(aud, "../Sprite/Player/Audience/Audience_pen_normal_good.png", true, 3, 12, pos, { 100.f,100.f },
		{ 255, 255, 255, 255 }, Sprite_Type::Audience_Normal_Good), "aud_normal", false);
	
	aud->GetTransform().SetScale({ 30.f, 6.f });
	aud->Set_Current_Sprite(aud->Find_Sprite_By_Type(Sprite_Type::Audience_Normal));
	ObjectManager::GetObjectManager()->AddObject(aud);*/

	return aud_red;
}
