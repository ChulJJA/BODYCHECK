/*
 * Author		:Sangmin Kim
 * File			:Player_Ui.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Player_Ui.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Object.h"
#include "BitmapFont.hpp"
#include "Component_Ui.h"
#include "Component_Item.h"

class PLAYER_UI : public Object
{
public:
    void Initialize();
    //Object* Get_Hp_Info()
    //{
    //    return info_hp_bar;
    //}
    Object* Get_Item_Info()
    {
        return info_item;
    }
    void Set_Bitmap_Font(BitmapFont* font)
    {
        this->font = font;
    }
    Object* Get_Life_Num()
    {
        return num_life;
    }
    void Reset();
	void Change_Ui_Info(Ui::Ui_Status_Base base, Ui::Ui_Status_Verb verb, Ui::Ui_Status_Obj obj);
    void Change_Ui_Info(Ui::Ui_Status_Base base, Ui::Ui_Status_Verb verb, Item::Item_Kind item_kind);


    void Set_Name(std::string name)
    {
        player_name = name;
    }
    Object* Get_Info_Item_Type()
    {
        return info_item_type;
    }
	
private:
    void Set_Life_Ui();

	
    //Object* info_hp_bar = nullptr;
    Object* info_item = nullptr;
    Object* info_item_type = nullptr;
    Object* num_life = nullptr;
    BitmapFont* font = nullptr;

    std::string player_name;
};