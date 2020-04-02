#include "Audience.h"
#include "Component_Sprite.h"
#include "ObjectManager.h"

Object* Get_Audience()
{
	Object* aud = new Object;
	aud->Set_Name("audience");
	aud->Set_Tag("audience");
	vector2 pos = { 0.f,800.f };
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
	ObjectManager::GetObjectManager()->AddObject(aud);

	return aud;
}
