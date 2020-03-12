#include "Component_Ui.h"
#include "Player_Ui.h"
#include "Component_Player.h"
#include "Component_Sprite.h"
#include "Component.hpp"

void Ui::Init(Object* obj)
{
	m_owner = obj;
}

void Ui::Update(float dt)
{
	if (status_info_base != Ui_Status_Base::None)
	{
		if (status_info_base == Ui_Status_Base::Item)
		{
			Change_Item_Ui();
		}

		status_info_base = Ui_Status_Base::None;
		status_info_obj = Ui_Status_Obj::None;
		status_info_verb = Ui_Status_Verb::None;
	}

}

void Ui::Change_Item_Ui()
{
	Object* item_ui = ui_info->Get_Item_Info();

	if (status_info_verb == Ui_Status_Verb::Use)
	{
		item_ui->Change_Sprite(item_ui->Find_Sprite_By_Name("none"));
	}
	
	else if (status_info_verb == Ui_Status_Verb::Get)
	{
		if(status_info_obj == Ui_Status_Obj::Item_Bulkup)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Name("bulkup"));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Dash)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Name("dash"));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Hp)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Name("heal"));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Throwing)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Name("throwing"));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Magnatic)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Name("magnatic"));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Time_Pause)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Name("time_pause"));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Reverse_Moving)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Name("reverse_moving"));
		}
		else
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Name("none"));
		}
	}

	
}

void Ui::Set_Status_Base(Ui_Status_Base status)
{
	status_info_base = status;
}

void Ui::Set_Status_Verb(Ui_Status_Verb status)
{
	status_info_verb = status;
}

void Ui::Set_Status_Obj(Ui_Status_Obj status)
{
	status_info_obj = status;
}
