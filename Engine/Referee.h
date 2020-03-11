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
    enum Refree_Statement
    {
    };
    enum class Stage_Statement
    {
        NONE = 99,
        PLAYER_FIRST_DIE = 100,
        PLAYER_SECOND_DIE = 101,
        PLAYER_THIRD_DIE = 102,
        PLAYER_FOURTH_DIE = 103
    };

    static Referee* Get_Referee();
    void Init();
    void Update(float dt);
    void Delete();

	Object* Make_Player_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag, Object* text);
	Object* Make_Item_Pool(std::string sprite_path, vector2 pos, std::string name, std::string tag, Item::Item_Kind kind);
	void Respawn_Player(Stage_Statement state, float dt);
	void Respawn_Item(float dt);

	
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

private:
    Referee() {}
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

    int player_first_life = 5;
    int player_sec_life = 5;
    int player_third_life = 5;
    int player_fourth_life = 5;

    Object** item_save;
    Object** item_save_hp;
    Object** item_bulk_up;

	Object** item_time_pause;
	Object** item_reverse_moving;
	
    float item_respawn_timer = 0.0f;
	
    int item_num = 10;
    int item_num_hp = 10;
    int item_num_dash = 10;
    int item_num_bulk_up = 10;

    int total_item_num = 30;

    PLAYER_UI* first_ui;
    PLAYER_UI* second_ui;
    PLAYER_UI* third_ui;
    PLAYER_UI* fourth_ui;

    Object* first_text;
    Object* second_text;
    Object* third_text;
    Object* fourth_text;

	std::vector<Object*> total_item;
};