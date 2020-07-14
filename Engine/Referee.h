/*
 * Author		:Sangmin Kim
 * File			:Referee.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Referee
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Object.h"
#include "vector"
#include "Component_Item.h"
#include "Particle.h"

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
    void Clear_Referee();

	Object* Make_Player_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag, Object* text, vector2 scale);
	Object* Make_Item_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag, Item::Item_Kind kind);
	void Respawn_Player(Stage_Statement state, float dt);
	void Respawn_Item(float dt);
    void SetPlayerTemp();
    void SetItem();
    void Set_Kill_State();
    void Win(float dt);
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
    void Set_Curr_Sec_Player(Object* player)
    {
        curr_sec_player = player;
    }
    void Set_Curr_Third_Player(Object* player)
    {
        curr_third_player = player;
    }

    void Set_Win_State();

	int Get_Player_Life()
	{
        return player_sec_life;
	}

    Object* Get_Win_Player()
    {
        return win_player;
    }
    void Incre_Curr_Item_Field_Num()
    {
        curr_field_num++;
    }
    void Decre_Curr_Item_Field_Num()
    {
        curr_field_num--;
    }

    void Set_Timer();
    void Reset_Variables();
    void Reset_Item_Variables();
    bool isGameDone = false;

    void Set_Sec_Player_Info(vector2 pos, vector2 scale, std::string path);
    void Set_Third_Player_Info(vector2 pos, vector2 scale, std::string path);
    void Separate_Player();
    bool Get_Is_CheerUp_Mode()
    {
        return is_cheerup_mode;
    }
    void Set_CheerUp_Mode(bool toggle)
    {
        is_cheerup_mode = toggle;
    }

private:
    Referee();
    static Referee* referee;


    std::vector<Stage_Statement> stage_statements;

    float player_second_respawn_timer = 3.0f;
    float player_first_respawn_timer = 3.0f;
    float player_third_respawn_timer = 3.0f;
    float player_fourth_respawn_timer = 3.0f;

    Object** player_sec_temp = nullptr;
    Object** player_first_temp = nullptr;
    Object** player_third_temp = nullptr;
    Object** player_fourth_temp = nullptr;

    int player_first_life;
    int player_sec_life;
    int player_third_life;
    int player_fourth_life;

    int total_life_count;

    Object** item_dash = nullptr;
    Object** item_heal = nullptr;
    Object** item_bulk_up = nullptr;
    Object** item_throwing = nullptr;
    Object** item_magnetic = nullptr;
	Object** item_time_pause = nullptr;
	Object** item_reverse_moving = nullptr;
	Object** item_missile = nullptr;
    Object** item_mine = nullptr;

	Object** missile_saving = nullptr;
    float item_respawn_timer = 3.0f;
	
    int item_num = 1;
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
    int curr_field_num = 0;
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
    
    Object* curr_third_player;
    Object* curr_sec_player;
    Object* win_player = nullptr;

    bool win = false;
    float player_dance_time = 0.f;
	
	std::vector<Object*> total_item;

    ParticleGenerator* win_particle;

    vector2 player_sec_pos;
    vector2 player_sec_scale;
    std::string player_sec_sprite_path;

    vector2 player_third_pos;
    vector2 player_third_scale;
    std::string player_third_sprite_path;

    bool playOnce = false;
    bool change_once = false;
    bool aud_is_cheerup_mode_finish = false;
    std::vector<Object*> audience_vec;
    bool is_cheerup_mode = false;
};