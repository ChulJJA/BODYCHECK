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
	Sprite* ui_sprite = item_ui->GetComponentByTemplate<Sprite>();

	if(ui_sprite != nullptr)
	{
		//item_ui->DeleteComponent(ui_sprite);
		
	}

	if (status_info_verb == Ui_Status_Verb::Use)
	{
		Component* current_using_sprite = item_ui->Get_Current_Sprite();
		Component* change_to_sprite = item_ui->Find_Component_By_Name("none");
		
		if(current_using_sprite != nullptr && change_to_sprite != nullptr)
		{
			change_to_sprite->Set_Need_Update(true);
			current_using_sprite->Set_Need_Update(false);
		}
	}
	
	else if (status_info_verb == Ui_Status_Verb::Get)
	{
		vector2 pos = item_ui->GetTransform().GetTranslation();
		Component* current_using_sprite = item_ui->Get_Current_Sprite();
		Component* change_to_sprite = nullptr;
		
		if(status_info_obj == Ui_Status_Obj::Item_Bulkup)
		{
			change_to_sprite = item_ui->Find_Component_By_Name("bulkup");
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Dash)
		{
			change_to_sprite = item_ui->Find_Component_By_Name("dash");
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Hp)
		{
			change_to_sprite = item_ui->Find_Component_By_Name("heal");
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Throwing)
		{
			change_to_sprite = item_ui->Find_Component_By_Name("throwing");
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Magnatic)
		{
			change_to_sprite = item_ui->Find_Component_By_Name("magnatic");
		}
		else
		{
			change_to_sprite = item_ui->Find_Component_By_Name("none");
		}

		change_to_sprite->Set_Need_Update(true);
		current_using_sprite->Set_Need_Update(false);
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
