/*
 * Author		:Sangmin Kim
 * File			:Component_Player.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Header file Component_Player.cpp.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Component.hpp"
#include "Component_Item.h"
#include "Component_Ui.h"

class PLAYER_UI;

class Player : public Component
{
public:
	enum class Char_State
	{
		None,
		Bulk_Up,
		Regeneration,
		Throwing
	};
	
    void Init(Object* obj) override;
    void Update(float dt) override;
    void SetHPBar();
    int Get_Damage()
    {
        return damage;
    }
    void Set_This_UI_info(PLAYER_UI* ui);
    void Set_Item_State(Item::Item_Kind state);
    PLAYER_UI* Get_Ui();
    Item::Item_Kind Get_Item_State();
    float& Get_Regeneration_Timer()
    {
        return regeneration_timer;
    }
    float& Get_Bulkup_Timer()
    {
        return bulkup_timer;
    }
	void Set_Bulkup_Timer(float timer_)
    {
		bulkup_timer = timer_;
    }
	Char_State Get_Char_State()
    {
		return curr_state;
    }
	void Set_Char_State(Char_State state)
    {
		curr_state = state;
    }
    void PlayerMove(float max_velocity, float min_velocity);
private:
    Object* hp_bar = nullptr;
    Item::Item_Kind belong_item = Item::Item_Kind::None;
    int damage = 2;
    PLAYER_UI* this_ui;
    float regeneration_timer = 0.f;
    float bulkup_timer = 0.f;
	Char_State curr_state;
    vector2 velocity{};
};