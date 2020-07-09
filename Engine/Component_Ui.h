/*
 * Author		:Sangmin Kim
 * File			:Component_Ui.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Component UI
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Component.hpp"

class PLAYER_UI;

class Ui : public Component
{

public:

	Ui(PLAYER_UI* ui)
	{
		ui_info = ui;
	}
	
	enum class Ui_Status_Base
	{
		None,
		Hp,
		Item,
		Image,
		Life,
	};
	enum class Ui_Status_Verb
	{
		None,
		Get,
		Use
	};
	
	enum class Ui_Status_Obj
	{
		None,

		Hp_Regenerating,
		Hp_Decreasing,

		Item_Dash,
		Item_Hp,
		Item_Bulkup,
		Item_Throwing,
		Item_Magnatic,
		Item_Time_Pause,
		Item_Reverse_Moving,
		Item_Missile,
		Item_Mine
	};

	void Init(Object* obj) override;
	void Update(float dt) override;

	void Set_Status_Base(Ui_Status_Base status);
	void Set_Status_Obj(Ui_Status_Obj status);
	void Set_Status_Verb(Ui_Status_Verb status);

	void Change_Item_Ui();
	void Change_Life_Ui();
	
	
private:
	PLAYER_UI* ui_info;
	Ui_Status_Base status_info_base;
	Ui_Status_Obj status_info_obj;
	Ui_Status_Verb status_info_verb;
	};