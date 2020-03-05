#include "Component_Ui.h"
#include "Player_Ui.h"
#include "Component_Player.h"
#include "Component_Sprite.h"

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

void Ui::Set_Status_Base(Ui_Status_Base status)
{
	status_info_base = status;
}

void Ui::Set_Status_Verb(Ui_Status_Verb status)
{
	status_info_verb = status;
}

void Ui::Change_Item_Ui()
{
	Object* item_ui = ui_info->Get_Item_Info();
	Sprite* ui_sprite = item_ui->GetComponentByTemplate<Sprite>();

	if(ui_sprite != nullptr)
	{
		item_ui->DeleteComponent(ui_sprite);
	}

	if (status_info_verb == Ui_Status_Verb::Use)
	{
	}
	
	else if (status_info_verb == Ui_Status_Verb::Get)
	{
		vector2 pos = item_ui->GetTransform().GetTranslation();
		
		if(status_info_obj == Ui_Status_Obj::Item_Bulkup)
		{
			item_ui->AddComponent(new Sprite(item_ui, "../sprite/bulkup.png", pos));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Dash)
		{
			item_ui->AddComponent(new Sprite(item_ui, "../sprite/dash.png", pos));
		}
		else if (status_info_obj == Ui_Status_Obj::Item_Hp)
		{
			item_ui->AddComponent(new Sprite(item_ui, "../sprite/heal.png", pos));
		}
	}

	
}


void Ui::Set_Status_Obj(Ui_Status_Obj status)
{
	status_info_obj = status;
}
