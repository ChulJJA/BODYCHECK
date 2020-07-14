/*
 * Author		:Sangmin Kim
 * File			:Editor.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Editor
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Editor.h"
#include "Object.h"
#include "Component_Item.h"
#include "Physics.h"
#include "Input.h"
#include "Component_Sprite.h"
#include "ObjectManager.h"
#include "Graphic.h"
#include <GLFW/glfw3.h>
#include "Message_Manager.h"
#include "Message.h"

//Editor* Editor::editor = nullptr;

void Editor::Init()
{
	val = 0;
	item_spawned_num = 0;
	Setting_Display(300.f, -400.f);
}

void Editor::Setting_Display(float offset, float pos_y)
{
	float init_pos_x = -1200.f;

	display_item_bulkup = Make_Display("../Sprite/Item/item_bulkup.png", { init_pos_x,pos_y }, Item::Item_Kind::Bulkup);
	init_pos_x += offset;
	display_item_dash = Make_Display("../Sprite/Item/item_dash.png", { init_pos_x,pos_y }, Item::Item_Kind::Dash);
	init_pos_x += offset;
	display_item_timepause = Make_Display("../Sprite/Item/time_pause.png", { init_pos_x,pos_y }, Item::Item_Kind::Time_Pause);
	init_pos_x += offset;
	display_item_missile = Make_Display("../Sprite/Item/missile_launcher_showing.png", { init_pos_x,pos_y }, Item::Item_Kind::Missile);
	init_pos_x += offset;
	display_item_recover = Make_Display("../Sprite/Item/item_heal.png", { init_pos_x,pos_y }, Item::Item_Kind::HP);
	init_pos_x += offset;
	display_item_reverse = Make_Display("../Sprite/Item/reverse_moving.png", { init_pos_x,pos_y }, Item::Item_Kind::Reverse_Moving);
	init_pos_x += offset;
	display_item_throwing = Make_Display("../Sprite/Item/throwing_showing.png", { init_pos_x,pos_y }, Item::Item_Kind::Throwing);
	init_pos_x += offset;
	display_item_mine = Make_Display("../Sprite/Item/mine_.png", { init_pos_x,pos_y }, Item::Item_Kind::Mine);
	init_pos_x += offset;
}

bool Editor::Check_Mouse_Is_In(Object* obj)
{
	if (obj != nullptr)
	{
		if (mouse_pointer->GetTransform().GetTranslation().x >= obj->GetTransform().GetTranslation().x - 50 &&
			mouse_pointer->GetTransform().GetTranslation().x <= obj->GetTransform().GetTranslation().x + 50 &&
			mouse_pointer->GetTransform().GetTranslation().y >= obj->GetTransform().GetTranslation().y - 50 &&
			mouse_pointer->GetTransform().GetTranslation().y <= obj->GetTransform().GetTranslation().y + 50)
		{
			return true;
		}
	}

	return false;
}

void Editor::Change_Other_Sprite(Object* obj)
{
	std::vector<Object*> display_obj = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("display");

	for (auto i : display_obj)
	{
		if (i != obj)
		{
			i->Change_Sprite(i->Find_Sprite_By_Name("display"));
		}
	}
}


void Editor::Update(float dt)
{

}

Object* Editor::Make_Display(std::string path, vector2 trans, Item::Item_Kind kind)
{
	std::string path_selected = "../Sprite/Item/item.png";

	Object* display_obj = new Object();
	display_obj->Set_Tag("display");
	display_obj->Set_Name("display");
	display_obj->SetScale({ 2.f,2.f, });
	display_obj->SetTranslation(trans);
	display_obj->AddComponent(new Sprite(display_obj, path.c_str(), trans), "display", false);
	display_obj->AddComponent(new Physics());
	display_obj->AddComponent(new Item());
	display_obj->GetComponentByTemplate<Item>()->Set_Kind(kind);
	display_obj->SetNeedCollision(true);
	display_obj->Set_Current_Sprite(display_obj->Find_Sprite_By_Name("display"));
	display_vec.push_back(display_obj);
	return display_obj;
}

void Editor::Set_Visible(bool toggle)
{	
	Component* bulk = display_item_bulkup->Find_Sprite_By_Name("display");
	Component* dash = display_item_dash->Find_Sprite_By_Name("display");
	Component* recover = display_item_recover->Find_Sprite_By_Name("display");
	Component* missile = display_item_missile->Find_Sprite_By_Name("display");
	Component* throwing = display_item_throwing->Find_Sprite_By_Name("display");
	Component* time = display_item_timepause->Find_Sprite_By_Name("display");
	Component* mine = display_item_mine->Find_Sprite_By_Name("display");
	Component* reverse = display_item_reverse->Find_Sprite_By_Name("display");

	if (bulk != nullptr)
	{
		bulk->Set_Need_Update(true);
	}
	if (dash != nullptr)
	{
		dash->Set_Need_Update(true);
	}
	if (recover != nullptr)
	{
		recover->Set_Need_Update(true);
	}

	if (missile != nullptr)
	{
		missile->Set_Need_Update(true);
	}
	if (throwing != nullptr)
	{
		throwing->Set_Need_Update(true);
	}
	if (time != nullptr)
	{
		time->Set_Need_Update(true);
	}
	if (mine != nullptr)
	{
		mine->Set_Need_Update(true);
	}
	if (reverse != nullptr)
	{
		reverse->Set_Need_Update(true);
	}

	if (toggle == true && val == 0)
	{
		for (auto i : display_vec)
		{
			ObjectManager::GetObjectManager()->AddObject(i);
		}
		val++;
	}

	if (display_item_bulkup != nullptr)
	{
		display_item_bulkup->Set_Need_To_Update(toggle);
	}
	if (display_item_dash != nullptr)
	{
		display_item_dash->Set_Need_To_Update(toggle);
	}
	if (display_item_recover != nullptr)
	{
		display_item_recover->Set_Need_To_Update(toggle);
	}
	if (display_item_reverse != nullptr)
	{
		display_item_reverse->Set_Need_To_Update(toggle);
	}
	if (display_item_magnetic != nullptr)
	{
		display_item_magnetic->Set_Need_To_Update(toggle);
	}
	if (display_item_missile != nullptr)
	{
		display_item_missile->Set_Need_To_Update(toggle);
	}
	if (display_item_throwing != nullptr)
	{
		display_item_throwing->Set_Need_To_Update(toggle);
	}
	if (display_item_timepause != nullptr)
	{
		display_item_timepause->Set_Need_To_Update(toggle);
	}
	if (display_item_mine != nullptr)
	{
		display_item_mine->Set_Need_To_Update(toggle);
	}
	
	if(toggle == false)
	{
	}
}
