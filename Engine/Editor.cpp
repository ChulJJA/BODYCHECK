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
	//int item_num = 100;
	//items = new Object * [item_num];
	//`std::string eat_effect = "../Sprite/Item/item_eateffect.png";
	//`std::string spawn_effect = "../Sprite/Item/item_spawn.png";
	//`std::string sprite_path = "../Sprite/Item/fish.png";

//	for (int i = 0; i < item_num; i++)
//	{
//		items[i] = new Object();
//		//items[i]->AddComponent(new Sprite(items[i], "../Sprite/Item/Item.png", { 0.f,0.f }));
//
//		/*items[i]->AddComponent(new Sprite(items[i], spawn_effect.c_str(), true, 10, 10, { 0.f,0.f }, { 200.f,200.f },
//			{ 255,255,255,255 }, Sprite_Type::Item_Spawn_Effect), "item_spawn", true);
//*/
//
//		items[i]->AddComponent(new Sprite(items[i], sprite_path.c_str(), true, 6, 12, { 0.f,0.f }, { 200.f,200.f },
//			{ 255,255,255,255 }, Sprite_Type::Item), "item", true);
//
//		items[i]->AddComponent(new Sprite(items[i], eat_effect.c_str(), true, 3, 12, { 0.f,0.f }, { 200.f,200.f },
//			{ 255,255,255,255 }, Sprite_Type::Item_Eateffect), "item_eat", false);
//
//		items[i]->AddComponent(new Item());
//		items[i]->AddComponent(new Physics);
//		items[i]->Set_Name("item");
//		items[i]->Set_Tag("item");
//		items[i]->SetScale({ 1.f, 1.f });
//		items[i]->SetNeedCollision(true);
//		items[i]->GetComponentByTemplate<Item>()->Set_Kind(Item::Item_Kind::None);
//		items[i]->Add_Pointed_By(&items[i]);
//	}

	Setting_Display(300.f, -400.f);

	//mouse_pointer = new Object();
	//mouse_pointer->Set_Tag("mouse_pointer");
	//mouse_pointer->Set_Name("mouse_pointer");
	//mouse_pointer->SetScale(1.f);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/None.png", { 0.f,0.f }), "display", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/Item.png", { 0.f,0.f }), "item", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/bulkup.png", { 0.f,0.f }), "bulkup", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/item_dash.png", { 0.f,0.f }), "dash", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/item_heal.png", { 0.f,0.f }), "heal", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/throwing_showing.png", { 0.f,0.f }), "throwing", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/magnet.png", { 0.f,0.f }), "magnatic", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/time_pause.png", { 0.f,0.f }), "time_pause", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/reverse_moving.png", { 0.f,0.f }), "reverse_moving", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/mine.png", { 0.f,0.f }), "mine", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/Item.png", { 0.f,0.f }), "missile", false);
	//mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/mine.png", { 0.f,0.f }), "mine", false);

	/*vector2 item_trans = vector2{ 0.f, 0.f };
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/None.png", item_trans, false, Sprite_Type::Item), "display", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/item_dash.png", item_trans, false, Sprite_Type::Item_Dash), "dash", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/item_heal.png", item_trans, false, Sprite_Type::Item_Heal), "heal", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/item_bulkup.png", item_trans, false, Sprite_Type::Item_Bulkup), "bulkup", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/throwing_showing.png", item_trans, false, Sprite_Type::Item_Throw), "throwing", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/magnet.png", item_trans, false, Sprite_Type::Item_Magnet), "magnatic", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/time_pause.png", item_trans, false, Sprite_Type::Item_Timepause), "time_pause", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/reverse_moving.png", item_trans, false, Sprite_Type::Item_Reverse), "reverse_moving", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/missile_launcher_showing.png", item_trans, false, Sprite_Type::Item_Missile), "missile", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item/mine.png", item_trans, false, Sprite_Type::Item_Mine), "mine", false);
	mouse_pointer->Set_Current_Sprite(mouse_pointer->Find_Sprite_By_Name("display"));*/
}

void Editor::Setting_Display(float offset, float pos_y)
{
	float init_pos_x = -1200.f;

	display_item_bulkup = Make_Display("../Sprite/Item/item_bulkup.png", { init_pos_x,pos_y }, Item::Item_Kind::Bulkup);
	init_pos_x += offset;
	display_item_dash = Make_Display("../Sprite/Item/item_dash.png", { init_pos_x,pos_y }, Item::Item_Kind::Dash);
	init_pos_x += offset;
	/*display_item_magnetic = Make_Display("../Sprite/Item/magnet.png", { init_pos_x,pos_y }, Item::Item_Kind::Magnatic);
	init_pos_x += offset;*/
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
	display_item_mine = Make_Display("../Sprite/Item/mine.png", { init_pos_x,pos_y }, Item::Item_Kind::Mine);
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
	/*
	if (Check_Mouse_Is_In(display_item_bulkup))
	{
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Type(Sprite_Type::Item_Bulkup));
		//mouse_pointer->Set_Current_Sprite(mouse_pointer->Find_Sprite_By_Name("bulkup"));
		mouse_pointer_state = Item::Item_Kind::Bulkup;
	}
	else if (Check_Mouse_Is_In(display_item_dash))
	{
		//mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("dash"));
		//mouse_pointer->Set_Current_Sprite(mouse_pointer->Find_Sprite_By_Name("dash"));
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Type(Sprite_Type::Item_Dash));
		mouse_pointer_state = Item::Item_Kind::Dash;
	}
	else if (Check_Mouse_Is_In(display_item_recover))
	{
		//mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("heal"));
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Type(Sprite_Type::Item_Heal));
		mouse_pointer_state = Item::Item_Kind::HP;
	}
	else if (Check_Mouse_Is_In(display_item_missile))
	{
		//mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("missile"));
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Type(Sprite_Type::Item_Missile));
		mouse_pointer_state = Item::Item_Kind::Missile;
	}
	else if (Check_Mouse_Is_In(display_item_throwing))
	{
		//mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("throwing"));
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Type(Sprite_Type::Item_Throw));
		mouse_pointer_state = Item::Item_Kind::Throwing;
	}
	else if (Check_Mouse_Is_In(display_item_reverse))
	{
		//mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("reverse_moving"));
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Type(Sprite_Type::Item_Reverse));
		mouse_pointer_state = Item::Item_Kind::Reverse_Moving;
	}
	else if (Check_Mouse_Is_In(display_item_timepause))
	{
		//mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("time_pause"));
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Type(Sprite_Type::Item_Timepause));
		mouse_pointer_state = Item::Item_Kind::Time_Pause;
	}
	else if (Check_Mouse_Is_In(display_item_magnetic))
	{
		//mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("magnatic"));
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Type(Sprite_Type::Item_Magnet));
		mouse_pointer_state = Item::Item_Kind::Magnatic;
	}
	else if (Check_Mouse_Is_In(display_item_mine))
	{
		//mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("mine"));
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Type(Sprite_Type::Item_Mine));
		mouse_pointer_state = Item::Item_Kind::Mine;
	}
	if(input.Is_Mouse_Triggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		items[item_spawned_num]->SetTranslation(mouse_pointer->GetTransform().GetTranslation());
		items[item_spawned_num]->GetComponentByTemplate<Item>()->Set_Kind(mouse_pointer_state);
		ObjectManager::GetObjectManager()->AddObject(items[item_spawned_num]);
		item_spawned_num++;
		//Message_Manager::Get_Message_Manager()->Save_Message(new Message(items[item_spawned_num], nullptr, Message_Kind::Spawn_Object, 1.f));
	}*/
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
	//display_vec.push_back(display_obj);
	ObjectManager::GetObjectManager()->AddObject(display_obj);
	return display_obj;
}

//Editor* Editor::Get_Editor()
//{
//	if (editor == nullptr)
//	{
//		editor = new Editor();
//	}
//	return editor;
//}

void Editor::Set_Visible(bool toggle)
{	
	Component* bulk = display_item_bulkup->Find_Sprite_By_Name("display");
	Component* dash = display_item_dash->Find_Sprite_By_Name("display");
	Component* recover = display_item_recover->Find_Sprite_By_Name("display");
	//Component* mag = display_item_magnetic->Find_Sprite_By_Name("display");
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
	/*if (mag != nullptr)
	{
		mag->Set_Need_Update(true);
	}*/
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

	//if (toggle == true && val == 0)
	//{
	//	for (auto i : display_vec)
	//	{
	//		ObjectManager::GetObjectManager()->AddObject(i);
	//	}
	//	val++;
	//}

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
	
	
	//mouse_pointer->Set_Need_To_Update(toggle);

	if(toggle == false)
	{
		//mouse_pointer_state = Item::Item_Kind::None;
	}
}
