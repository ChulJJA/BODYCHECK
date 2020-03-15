/*
 * Author		:Sangmin Kim
 * File			:Player_UI.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Objects which represent UI is initialized & reset in here.
 *				 In initialize, set the translation, name, scale, image.
 *
 *				 In reset, reset the color, scale, translation to initial value.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Player_Ui.h"
#include "Component_Sprite.h"
#include "ObjectManager.h"
#include "Component_Text.h"

void PLAYER_UI::Initialize()
{
	const vector2 this_trans = this->GetTransform().GetTranslation();
	
    /*info_hp_bar = new Object();
	info_hp_bar->GetTransform().SetTranslation({ this_trans.x + 350, this_trans.y});
	info_hp_bar->GetTransform().SetScale({ 4.f, 6.f });
    info_hp_bar->AddComponent(new Sprite(info_hp_bar, "../Sprite/HP.png", info_hp_bar->GetTransform().GetTranslation(), false));
    info_hp_bar->Set_Tag("hp_info");
    info_hp_bar->Set_Name(this->GetName() + "info_hp");
    ObjectManager::GetObjectManager()->AddObject(info_hp_bar);*/

    info_item = new Object();
	info_item->GetTransform().SetTranslation({ this_trans.x + 200, this_trans.y});
	info_item->GetTransform().SetScale({ 2.f, 2.f });
	info_item->Set_Tag("item_info");
	info_item->AddComponent(new Sprite(info_item, "../Sprite/None.png", { this_trans.x + 200, this_trans.y}), "none");
	info_item->AddComponent(new Sprite(info_item, "../Sprite/Item.png", { this_trans.x + 200, this_trans.y}), "item", false);
	info_item->AddComponent(new Sprite(info_item, "../Sprite/bulkup.png", { this_trans.x + 200, this_trans.y}), "bulkup", false);
	info_item->AddComponent(new Sprite(info_item, "../Sprite/dash.png", { this_trans.x + 200, this_trans.y}), "dash", false);
	info_item->AddComponent(new Sprite(info_item, "../Sprite/heal.png", { this_trans.x + 200, this_trans.y}), "heal", false);
	info_item->AddComponent(new Sprite(info_item, "../Sprite/throw.png", { this_trans.x + 200, this_trans.y}), "throwing", false);
	info_item->AddComponent(new Sprite(info_item, "../Sprite/magnet.png", { this_trans.x + 200, this_trans.y}), "magnatic", false);
	info_item->AddComponent(new Sprite(info_item, "../Sprite/time_pause.png", { this_trans.x + 200, this_trans.y}), "time_pause", false);
	info_item->AddComponent(new Sprite(info_item, "../Sprite/reverse_moving.png", { this_trans.x + 200, this_trans.y}), "reverse_moving", false);
	info_item->AddComponent(new Sprite(info_item, "../Sprite/Item.png", { this_trans.x + 200, this_trans.y}), "missile", false);

    info_item->Set_Name(this->GetName() + "info_item");
	info_item->Set_Current_Sprite(info_item->Find_Sprite_By_Name("none"));
    ObjectManager::GetObjectManager()->AddObject(info_item);
	//asd

    num_life = new Object();
	num_life->GetTransform().SetTranslation({ this_trans.x + 500, this_trans.y - 100 });
	num_life->GetTransform().SetScale({ 2.f, 2.f });
    num_life->AddComponent(new TextComp(num_life, L"5", { 1,1,1,1 }, { 200,200 }, *font));
    num_life->Set_Tag("life_info");
    num_life->Set_Name(this->GetName() + "life_info");
    num_life->GetComponentByTemplate<TextComp>()->Get_Need_To_Keep_Drawing() = true;
    ObjectManager::GetObjectManager()->AddObject(num_life);
}

void PLAYER_UI::Reset()
{
    this->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1.0f,1.0f,1.0f,1.0f };
    this->GetMesh().Get_Is_Moved() = true;
    const vector2 this_trans = this->GetTransform().GetTranslation();
	Sprite* info_item_sprite = info_item->GetComponentByTemplate<Sprite>();

	info_item->GetTransform().SetTranslation({ this_trans.x + 400, this_trans.y });
	info_item->Change_Sprite(info_item->Find_Sprite_By_Name("none"));
    info_item->GetMesh().Get_Is_Moved() = true;
}

void PLAYER_UI::Change_Ui_Info(Ui::Ui_Status_Base base, Ui::Ui_Status_Verb verb, Ui::Ui_Status_Obj obj)
{
	Ui* info_ui = GetComponentByTemplate<Ui>();

	if(info_ui != nullptr)
	{
		info_ui->Set_Status_Base(base);
		info_ui->Set_Status_Verb(verb);
		info_ui->Set_Status_Obj(obj);
		GetMesh().Get_Is_Moved() = true;
	}
}
