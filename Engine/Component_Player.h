/*
 * Author		:Sangmin Kim
 * File			:Component_Player.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Component Player
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Component.hpp"
#include "Component_Item.h"
#include "Component_Ui.h"
#include "Gamepad.hpp"
#include "angles.hpp"


class PLAYER_UI;
class Player : public Component
{
public:
	enum class Char_State
	{
		None,
		Magnatic,
		Lock_Ing,
		Time_Pause,
		Reverse_Moving,
		Missile_Ready,
		Prepare,
		Prepared,
		Mine
	};
	enum class Char_State_Additional
	{
		None,
		Chasing,
		Get_mine
	};
	enum class Char_State_By_Other
	{
		None,
	};
	enum class Item_Use_Status
	{
		None,
		Bulkup,
		Dash,
		Magnet
	};

	Player(bool need_update_hp = true)
	{
		need_update_hp_bar = need_update_hp;
	}
	
    void Init(Object* obj);
    void Update(float dt) override;
	//
    void SetHPBar();
    int Get_Damage() const;
	Item::Item_Kind Get_Item_State() const;
	void Set_Item_State(Item::Item_Kind state);
    void Set_This_UI_info(PLAYER_UI* ui);
    PLAYER_UI* Get_Ui() const;
	float& Get_Regeneration_Timer();
   
	float& Get_Bulkup_Timer();
	void Set_Bulkup_Timer(float timer_);
	Char_State Get_Char_State() const;
	void Set_Char_State(Char_State state);

	void Set_Char_State_Additional(Char_State_Additional state);
	Char_State_Additional Get_Char_State_Additional() const;

	Object* Get_Locking() const;
	void Set_Locking(Object* obj);
	Object* Get_Hp_Bar() const;
	float& Get_Stop_Timer();
	void Set_Stop_Timer(float timer_);
	void Set_Mine_Timer(float timer);
	void Set_Locking_By(Object* obj);
	void Set_Locking_Result(Object* obj);
	Object* Get_Locking_Result() const;
	float Get_Mine_Timer();
	void Func_Time_Pause(float dt);
	void Func_Reverse_Moving(float dt);

	void Func_Mine(float dt);
	void Func_Mine_Collided(float dt);

	void PlayerMovement(float max_velocity, float min_velocity);
	void SetPlayerVelocity(vector2 current_velocity);
	vector2 GetPlayerVelocity();
	vector2 GetPlayerDirection();
	void UseItem();
	void Set_Missile_Timer(float timer);
	void Change_To_Normal_State();

	void Set_Prepare_Timer(float timer);
	void Sprite_After_Preparation(Component* sprite_to_change);
	void State_After_Preparation(Char_State state);

	void Change_Weapon_Sprite(Component* weapon_sprite);

	void Check_Current_Sprite_Status(float dt);
	Item_Use_Status Get_Item_Used_Status();
	void Set_Item_Used_Status(Item_Use_Status status);

	void Set_Audience(Object* obj);
	Object* Get_Audience();


private:
    Object* hp_bar = nullptr;
    Item::Item_Kind belong_item = Item::Item_Kind::None;
    int damage = 2;
    PLAYER_UI* this_ui;
    float regeneration_timer = 0.f;
    float bulkup_timer = 0.f;
	
	Char_State curr_state;
	Char_State_Additional curr_state_additional = Char_State_Additional::None;

	Object* locking_pointer = nullptr;
	Object* locking_by = nullptr;
	bool need_update_hp_bar;
	Object* locking_result = nullptr;
	float stop_timer = 0.0f;
	float mine_timer = 0.0f;
	float missile_timer = 0.f;
	vector2 velocity{};
	vector2 direction = {0, 1};

	float prepare_sprite_timer = 0.f;
	Component* change_to_sprite = nullptr;
	Component* weapon_state = nullptr;
	
	Char_State change_to_state = Char_State::None;
	Item_Use_Status item_used = Item_Use_Status::None;
	Object* install_mine;

	Object* aud;
	Component* last_sprite;
	float sprite_check_timer = 0.f;

	float speedUpSoundTimer = 0;
	int mineCount = 0;
	matrix3 mat = MATRIX3::build_rotation(to_radians(5));
	//ParticleGenerator* speedParticle = nullptr;
};
