/*
 * Author		:Sangmin Kim
 * File			:Component_HpBar.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Component HP Bar
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */


#pragma once
#include "Component.hpp"

class Player;

class Hp_Bar : public Component
{
public:

	
	enum class Hp_Bar_State
	{
		None,
		Recovering,
		Damaging
	};
	
	Hp_Bar() :offset(0), curr_state(Hp_Bar_State::None), timer(0.f)
	{

	}
	
    void Init(Object* obj) override;
    void Update(float dt) override;
    void Decrease(float dmg);
	
    int& Get_Set_Offset();

	void Recovering(float dt);
	void Damaging(float dt);
	
	Hp_Bar_State Get_Hp_Bar_State()
	{
		return curr_state;
	}
	void Set_Hp_Bar_State(Hp_Bar_State state)
	{
		curr_state = state;
	}
	void Set_Timer(float timer_)
	{
		timer = timer_;
	}

private:
    int offset;
	Hp_Bar_State curr_state;
	float timer;
	Object* hp_owner = nullptr;
	Player* info_player;
};