#include "Editor.h"
#include "Object.h"
#include "Component_Item.h"
#include "Physics.h"
#include "Input.h"
#include "Component_Sprite.h"
#include "ObjectManager.h"
#include "Graphic.h"
#include <GLFW/glfw3.h>

Editor* Editor::editor = nullptr;

void Editor::Init()
{
	int item_num = 100;
	items = new Object * [item_num];

	for (int i = 0; i < item_num; i++)
	{
		items[i] = new Object();
		items[i]->AddComponent(new Sprite(items[i], "../Sprite/Item.png", { 0.f,0.f }));
		items[i]->AddComponent(new Item());
		items[i]->AddComponent(new Physics);
		items[i]->Set_Name("item");
		items[i]->Set_Tag("item");
		items[i]->SetScale({ 1.f, 1.f });
		items[i]->GetComponentByTemplate<Item>()->Set_Kind(Item::Item_Kind::None);
		items[i]->Add_Pointed_By(&items[i]);
	}

	Setting_Display(200.f, -400.f);

	mouse_pointer = new Object();
	mouse_pointer->Set_Tag("mouse_pointer");
	mouse_pointer->Set_Name("mouse_pointer");
	mouse_pointer->SetScale(1.f);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/None.png", { 0.f,0.f }), "display", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item.png", { 0.f,0.f }), "item", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/bulkup.png", { 0.f,0.f }), "bulkup", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/dash.png", { 0.f,0.f }), "dash", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/heal.png", { 0.f,0.f }), "heal", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/throw.png", { 0.f,0.f }), "throwing", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/magnet.png", { 0.f,0.f }), "magnatic", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/time_pause.png", { 0.f,0.f }), "time_pause", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/reverse_moving.png", { 0.f,0.f }), "reverse_moving", false);
	mouse_pointer->AddComponent(new Sprite(mouse_pointer, "../Sprite/Item.png", { 0.f,0.f }), "missile", false);
	mouse_pointer->Set_Current_Sprite(mouse_pointer->Find_Sprite_By_Name("display"));
}

void Editor::Setting_Display(float offset, float pos_y)
{
	float init_pos_x = -800.f;

	display_item_bulkup = Make_Display("../Sprite/bulkup.png", { init_pos_x,pos_y });
	init_pos_x += offset;
	display_item_dash = Make_Display("../Sprite/dash.png", { init_pos_x,pos_y });
	init_pos_x += offset;
	display_item_magnetic = Make_Display("../Sprite/magnet.png", { init_pos_x,pos_y });
	init_pos_x += offset;
	display_item_timepause = Make_Display("../Sprite/time_pause.png", { init_pos_x,pos_y });
	init_pos_x += offset;
	display_item_missile = Make_Display("../Sprite/item.png", { init_pos_x,pos_y });
	init_pos_x += offset;
	display_item_recover = Make_Display("../Sprite/heal.png", { init_pos_x,pos_y });
	init_pos_x += offset;
	display_item_reverse = Make_Display("../Sprite/reverse_moving.png", { init_pos_x,pos_y });
	init_pos_x += offset;
	display_item_throwing = Make_Display("../Sprite/throw.png", { init_pos_x,pos_y });
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
	mouse_pointer->SetTranslation({ input.Get_Mouse_Pos().x * 3.f, input.Get_Mouse_Pos().y * 3.f });

	if (Check_Mouse_Is_In(display_item_bulkup))
	{
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("bulkup"));
		mouse_pointer->Set_Current_Sprite(mouse_pointer->Find_Sprite_By_Name("bulkup"));
		mouse_pointer_state = Item::Item_Kind::Bulkup;
	}
	else if (Check_Mouse_Is_In(display_item_dash))
	{
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("dash"));
		mouse_pointer->Set_Current_Sprite(mouse_pointer->Find_Sprite_By_Name("dash"));
		mouse_pointer_state = Item::Item_Kind::Dash;
	}
	else if (Check_Mouse_Is_In(display_item_recover))
	{
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("heal"));
		mouse_pointer_state = Item::Item_Kind::HP;
	}
	else if (Check_Mouse_Is_In(display_item_missile))
	{
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("missile"));
		mouse_pointer_state = Item::Item_Kind::Missile;
	}
	else if (Check_Mouse_Is_In(display_item_throwing))
	{
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("throwing"));
		mouse_pointer_state = Item::Item_Kind::Throwing;
	}
	else if (Check_Mouse_Is_In(display_item_reverse))
	{
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("reverse_moving"));
		mouse_pointer_state = Item::Item_Kind::Reverse_Moving;
	}
	else if (Check_Mouse_Is_In(display_item_timepause))
	{
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("time_pause"));
		mouse_pointer_state = Item::Item_Kind::Time_Pause;
	}
	else if (Check_Mouse_Is_In(display_item_magnetic))
	{
		mouse_pointer->Change_Sprite(mouse_pointer->Find_Sprite_By_Name("magnatic"));
		mouse_pointer_state = Item::Item_Kind::Magnatic;
	}

	if(input.Is_Mouse_Triggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		items[item_spawned_num]->SetTranslation(mouse_pointer->GetTransform().GetTranslation());
		items[item_spawned_num]->GetComponentByTemplate<Item>()->Set_Kind(mouse_pointer_state);
		ObjectManager::GetObjectManager()->AddObject(items[item_spawned_num]);
		item_spawned_num++;
	}
}

Object* Editor::Make_Display(std::string path, vector2 trans)
{
	std::string path_selected = "../Sprite/item.png";

	Object* display_obj = new Object();
	display_obj->Set_Tag("display");
	display_obj->Set_Name("display");
	display_obj->SetScale({ 2.f,2.f, });
	display_obj->SetTranslation(trans);
	display_obj->AddComponent(new Sprite(display_obj, path.c_str(), trans), "display", false);
	display_obj->Set_Current_Sprite(display_obj->Find_Sprite_By_Name("display"));
	display_vec.push_back(display_obj);
	return display_obj;
}

Editor* Editor::Get_Editor()
{
	if (editor == nullptr)
	{
		editor = new Editor();
	}
	return editor;
}

void Editor::Set_Visible(bool toggle)
{	
	display_item_bulkup->Find_Sprite_By_Name("display")->Set_Need_Update(toggle);
	display_item_dash->Find_Sprite_By_Name("display")->Set_Need_Update(toggle);
	display_item_recover->Find_Sprite_By_Name("display")->Set_Need_Update(toggle);
	display_item_reverse->Find_Sprite_By_Name("display")->Set_Need_Update(toggle);
	display_item_magnetic->Find_Sprite_By_Name("display")->Set_Need_Update(toggle);
	display_item_missile->Find_Sprite_By_Name("display")->Set_Need_Update(toggle);
	display_item_throwing->Find_Sprite_By_Name("display")->Set_Need_Update(toggle);
	display_item_timepause->Find_Sprite_By_Name("display")->Set_Need_Update(toggle);
	mouse_pointer->Find_Sprite_By_Name("display")->Set_Need_Update(toggle);
	mouse_pointer->Set_Current_Sprite(mouse_pointer->Find_Sprite_By_Name("display"));

	if (toggle == true && val == 0)
	{
		for (auto i : display_vec)
		{
			ObjectManager::GetObjectManager()->AddObject(i);
		}
		ObjectManager::GetObjectManager()->AddObject(mouse_pointer);
		val++;
	}

	display_item_bulkup->Set_Need_To_Update(toggle);
	display_item_dash->Set_Need_To_Update(toggle);
	display_item_recover->Set_Need_To_Update(toggle);
	display_item_reverse->Set_Need_To_Update(toggle);
	display_item_magnetic->Set_Need_To_Update(toggle);
	display_item_missile->Set_Need_To_Update(toggle);
	display_item_throwing->Set_Need_To_Update(toggle);
	display_item_timepause->Set_Need_To_Update(toggle);
	mouse_pointer->Set_Need_To_Update(toggle);

	if(toggle == false)
	{
		mouse_pointer_state = Item::Item_Kind::None;
	}
}
