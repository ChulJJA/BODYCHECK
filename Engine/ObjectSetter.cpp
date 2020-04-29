#include "ObjectSetter.h"
#include "ObjectManager.h"
#include "Component_Sprite.h"

Object* SetObject(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale)
{
	std::string sprite = "../Sprite/";
	sprite += sprite_path;
	sprite += ".png";

	Object* obj = new Object();
	obj->Set_Name("arena");
	obj->Set_Tag("arena");
	obj->AddComponent(new Sprite(obj, sprite.c_str(), { 0,150 }, false), name);
	obj->SetScale({ 35, 17 });
	ObjectManager::GetObjectManager()->AddObject(obj);

	return obj;
}

Object* SetArena(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale)
{
	std::string sprite = "../Sprite/";
	sprite += sprite_path;
	sprite += ".png";
	
	Object* arena = new Object();
	arena->Set_Name("arena");
	arena->Set_Tag("arena");
	arena->AddComponent(new Sprite(arena, sprite.c_str(), { 0,150 }, false), name);
	arena->SetScale({ 35, 17 });
	ObjectManager::GetObjectManager()->AddObject(arena);

	return arena;
}