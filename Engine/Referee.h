/*
 * Author		:Sangmin Kim
 * File			:Referee.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Referee.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Object.h"
#include "vector"
#include "Component_Item.h"

class PLAYER_UI;

class Referee : public Object
{
public:
    enum Refree_Statement//
    {
    };
    enum class Stage_Statement
    {
        NONE = 99,
        PLAYER_FIRST_DIE,
        PLAYER_SECOND_DIE,
        PLAYER_THIRD_DIE,
        PLAYER_FOURTH_DIE,
    };

    static Referee* Get_Referee();
    void Init();
    void Update(float dt);
    void Delete();

	Object* Make_Player_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag, Object* text);
	Object* Make_Item_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag, Item::Item_Kind kind);
	void Respawn_Player(Stage_Statement state, float dt);
	void Respawn_Item(float dt);
    void SetPlayerTemp();
    void SetItem();
    void Set_Kill_State();
    void Win();
    Object* Get_Third_Kill();
    Object* Get_First_Kill();
    Object* Get_Second_Kill();
    Object* Get_Fourth_Kill();

    void Set_Random_Pos(vector2& pos);

	int Get_Missile_Count()
	{
		return missile_count;
	}
	Object* Return_New_Missile();

	Object* Get_Missile_From_Saving(int index)
	{
		if (missile_count > index)
		{
			missile_count++;
			return missile_saving[index];
		}
		return Return_New_Missile();
	}
	
    std::vector<Stage_Statement>& Get_Stage_Statement()
    {
        return stage_statements;
    }
    void Respawn(Stage_Statement statement);

    void Set_First_Ui(PLAYER_UI* ui)
    {
        first_ui = ui;
    }
    void Set_Second_Ui(PLAYER_UI* ui)
    {
        second_ui = ui;
    }
    void Set_Third_Ui(PLAYER_UI* ui)
    {
        third_ui = ui;
    }
    void Set_Fourth_Ui(PLAYER_UI* ui)
    {
        fourth_ui = ui;
    }

    void Set_First_Text(Object* ui)
    {
        first_text = ui;
    }
    void Set_Second_Text(Object* ui)
    {
        second_text = ui;
    }
    void Set_Third_Text(Object* ui)
    {
        third_text = ui;
    }
    void Set_Fourth_Text(Object* ui)
    {
        fourth_text = ui;
    }
    void Set_Win_State();

	int Get_Player_Life()
	{
        return player_first_life;
	}
    void Set_Timer();

private:
    Referee();
    static Referee* referee;


    std::vector<Stage_Statement> stage_statements;

    float player_second_respawn_timer = 3.0f;
    float player_first_respawn_timer = 3.0f;
    float player_third_respawn_timer = 3.0f;
    float player_fourth_respawn_timer = 3.0f;

    Object** player_sec_temp;
    Object** player_first_temp;
    Object** player_third_temp;
    Object** player_fourth_temp;

    int player_first_life;
    int player_sec_life;
    int player_third_life;
    int player_fourth_life;

    int total_life_count;

    Object** item_dash;
    Object** item_heal;
    Object** item_bulk_up;
    Object** item_throwing;
    Object** item_magnetic;
	Object** item_time_pause;
	Object** item_reverse_moving;
	Object** item_missile;
    Object** item_mine;

	Object** missile_saving;
    float item_respawn_timer = 3.0f;
	
    int item_num = 10;
    int item_num_heal = 10;
    int item_num_dash = 10;
    int item_num_bulk_up = 10;
    int item_num_throwing = 10;
    int item_num_magnetic = 10;
    int item_num_time_pause = 10;
    int item_num_reverse_moving = 10;
	int item_num_missile = 10;
	int missile_num = 50;
    int item_num_mine = 10;

    int total_item_num = 30;
	int missile_count = 0;

    PLAYER_UI* first_ui;
    PLAYER_UI* second_ui;
    PLAYER_UI* third_ui;
    PLAYER_UI* fourth_ui;

    Object* first_text;
    Object* second_text;
    Object* third_text;
    Object* fourth_text;

    Object* first_win;
    Object* second_win;
    Object* third_win;
    Object* fourth_win;

    Object* first_kill;
    Object* second_kill;
    Object* third_kill;
    Object* fourth_kill;

    Object* timer_1;
    Object* timer_2;
    Object* timer_3;
    Object* timer_erase;
    Object* timer_start;

    bool win = false;
	
	std::vector<Object*> total_item;
};