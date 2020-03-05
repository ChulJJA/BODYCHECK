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

class PLAYER_UI : public Object
{
public:
    void Initialize();
    Object* Get_Hp_Info()
    {
        return info_hp_bar;
    }
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
private:

    Object* info_hp_bar = nullptr;
    Object* info_item = nullptr;
    Object* num_life = nullptr;
    BitmapFont* font = nullptr;
};