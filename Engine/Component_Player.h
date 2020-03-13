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
		Throwing,
		Magnatic,
		Lock_Ready,
		Lock_Ing,
		Time_Pause,
		Reverse_Moving,
		Missile_Ready,
		Missile_Shoot
	};
	enum class Char_State_Additional
	{
		None,
		Chasing,
		Chasing_stop
	};
	enum class Char_State_By_Other
	{
		None,
		Locked
	};

	Player(bool need_update_hp = true)
	{
		need_update_hp_bar = need_update_hp;
	}
	
    void Init(Object* obj);
    void Update(float dt) override;
	//
    void SetHPBar();
    int Get_Damage();
	Item::Item_Kind Get_Item_State();
	void Set_Item_State(Item::Item_Kind state);
    void Set_This_UI_info(PLAYER_UI* ui);
    PLAYER_UI* Get_Ui();
	float& Get_Regeneration_Timer();
   
	float& Get_Bulkup_Timer();
	void Set_Bulkup_Timer(float timer_);
	Char_State Get_Char_State();
	void Set_Char_State(Char_State state);

	void Set_Char_State_Additional(Char_State_Additional state);
	Char_State_Additional Get_Char_State_Additional();
	
	Char_State_By_Other Get_Char_State_By_Other();
	void Set_Char_State_By_Other(Char_State_By_Other state);

	Object* Get_Locking();
	void Set_Locking(Object* obj);
	Object* Get_Hp_Bar();
	float& Get_Stop_Timer();
	void Set_Stop_Timer(float timer_);

	void Set_Locking_By(Object* obj);
	void Set_Locking_Result(Object* obj);
	Object* Get_Locking_Result();
	void Func_Bulk_Up(float dt);
	void Func_Bulk_Throwing(float dt);
	void Func_Lock_Ready(float dt);
	void Func_Magnatic(float dt);
	void Func_Time_Pause(float dt);
	void Func_Reverse_Moving(float dt);
	void Func_Missile_Shoot(float dt);

	
	void PlayerMovement(float max_velocity, float min_velocity);
	void SetPlayerVelocity(vector2 current_velocity);
	vector2 GetPlayerVelocity();
	void PlayerDirecting();
	vector2 GetPlayerDirection();
	void UseItem();
	void Set_Missile_Timer(float timer);
	void Change_To_Normal_State();

	
private:
    Object* hp_bar = nullptr;
    Item::Item_Kind belong_item = Item::Item_Kind::None;
    int damage = 2;
    PLAYER_UI* this_ui;
    float regeneration_timer = 0.f;
    float bulkup_timer = 0.f;
	Char_State curr_state;
	Char_State_By_Other curr_state_by_other;
	Object* locking_pointer = nullptr;
	Object* locking_by = nullptr;
	bool need_update_hp_bar;
	float mag_angle;
	Char_State_Additional curr_state_additional = Char_State_Additional::None;
	Object* locking_result = nullptr;
	float stop_timer = 0.0f;
	float missile_timer = 0.f;

	
	vector2 velocity{};
	vector2 direction = {0, 1};
};