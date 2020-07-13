/*
 * Author		:Suhwan Kim
 * File			:Tutorial.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Tutorial
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "State.h"
#include "Object.h"
#include "Common_Header.h"
#include "BitmapFont.hpp"

class PLAYER_UI;

class Tutorial : public State
{
public:
    
    Tutorial()
    {
    }

    virtual void Load();
    virtual void Update(float dt);
    virtual void UnLoad();
   /* {
        next_level = {};
        is_next = false;
    }*/

    void SetArena();
    void SetStaffAndExplanation();
    void EventCheck();

    void BackToMenu();
    void Clear();

private:
    Object* Arena = nullptr;

    Object* Player_First;
    Object* Player_Second;
    Object* Player_Third;
    Object* Player_Fourth;

    Object* description_second;
    Object* description_third;


    Object* Explanation_Staff_sec;
    Object* Explanation_Staff_third;

    
    PLAYER_UI* Player_First_UI;
    PLAYER_UI* Player_Second_UI;
    PLAYER_UI* Player_Third_UI;
    PLAYER_UI* Player_Fourth_UI;

    Object* pause;
    Object* restart_button;
    Object* restart_button_hover;
    Object* mainmenu_button;
    Object* mainmenu_button_hover;
    Object* option_button;
    Object* option_button_hover;
    Object* esc_indicator;

    bool showing_editor = true;
    bool dt_refreshed = false;
    bool timer_deleted = false;
    Object* prev_timer = nullptr;

    Object* make_sure_dialogue;
    bool r_u_sure = false;
    bool r_u_sure_come = false; 
    bool isClickPlayed = false;
};