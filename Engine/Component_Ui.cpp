/*
 * Author		:Sangmin Kim
 * File			:Component_Ui.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Component Button
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Ui.h"
#include "Player_Ui.h"
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
		if(status_info_base == Ui_Status_Base::Life)
		{
			Change_Life_Ui();
		}

		status_info_base = Ui_Status_Base::None;
		status_info_obj = Ui_Status_Obj::None;
		status_info_verb = Ui_Status_Verb::None;
	}

}

void Ui::Change_Item_Ui()
{
	Object* item_ui = ui_info->Get_Item_Info();
	Object* item_type = ui_info->Get_Info_Item_Type();

	if (status_info_verb == Ui_Status_Verb::Use)
	{
		item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::None));
		item_type->Change_Sprite(item_type->Find_Sprite_By_Type(Sprite_Type::None));
	}
	
	else if (status_info_verb == Ui_Status_Verb::Get)
	{
		if(status_info_obj == Ui_Status_Obj::Item_Bulkup)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::Item_Bulkup));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Dash)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::Item_Dash));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Hp)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::Item_Heal));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Throwing)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::Item_Throw));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Magnatic)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::Item_Magnet));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Time_Pause)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::Item_Timepause));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Reverse_Moving)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::Item_Reverse));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Missile)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::Item_Missile));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Mine)
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::Item_Mine));
		}
		else
		{
			item_ui->Change_Sprite(item_ui->Find_Sprite_By_Type(Sprite_Type::None));
		}
		item_type->Change_Sprite(item_type->Find_Sprite_By_Type(Sprite_Type::Item_Click));
	}

	
}

void Ui::Change_Life_Ui()
{
	Object* life_info = ui_info->Get_Life_Num();

	Sprite* curr_sprite = reinterpret_cast<Sprite*>(life_info->Get_Current_Sprite());

	if(curr_sprite->Get_Sprite_Type() == Sprite_Type::Num_5)
	{
		life_info->Change_Sprite(life_info->Find_Sprite_By_Type(Sprite_Type::Num_4));
	}
	else if (curr_sprite->Get_Sprite_Type() == Sprite_Type::Num_4)
	{
		life_info->Change_Sprite(life_info->Find_Sprite_By_Type(Sprite_Type::Num_3));
	}
	else if (curr_sprite->Get_Sprite_Type() == Sprite_Type::Num_3)
	{
		life_info->Change_Sprite(life_info->Find_Sprite_By_Type(Sprite_Type::Num_2));
	}
	else if (curr_sprite->Get_Sprite_Type() == Sprite_Type::Num_2)
	{
		life_info->Change_Sprite(life_info->Find_Sprite_By_Type(Sprite_Type::Num_1));
	}
	else if (curr_sprite->Get_Sprite_Type() == Sprite_Type::Num_1)
	{
		life_info->Change_Sprite(life_info->Find_Sprite_By_Type(Sprite_Type::Num_0));
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
