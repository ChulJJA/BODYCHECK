#pragma once
#include <string>
#include <vector>
#include "Component_Item.h"

struct vector2;
class Object;

class Editor
{
public:
	void Init();
	void Update(float dt);
	Object* Make_Display(std::string path, vector2 trans);

	static Editor* Get_Editor();
	void Set_Visible(bool toggle);
	void Setting_Display(float offset, float pos_y);
	bool Check_Mouse_Is_In(Object* obj);
	void Change_Other_Sprite(Object* obj);
	
private:
	Editor()
	{
		
	}
	Object** items;

	Object* display_item_dash;
	Object* display_item_recover;
	Object* display_item_bulkup;
	Object* display_item_missile;
	Object* display_item_throwing;
	Object* display_item_reverse;
	Object* display_item_timepause;
	Object* display_item_magnetic;
	Object* display_item_mine;

	Object* mouse_pointer;
	std::vector<Object*> display_vec;
	static Editor* editor;
	Item::Item_Kind mouse_pointer_state = Item::Item_Kind::None;
	int val = 0;
	int item_spawned_num = 0;
};