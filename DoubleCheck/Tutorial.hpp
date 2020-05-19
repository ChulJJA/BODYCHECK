/*
 * Author		:Suhwan Kim
 * File			:Level1.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/02/22
 * Description	:Header file for Tutorial stage.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
        current_state = GameState::Tutorial;
    }

    virtual void Load();
    virtual void Update(float dt);
    virtual void UnLoad()
    {
        next_level = {};
        is_next = false;
    }

    void SetArena();
    void SetStaffAndExplanation();
    void EventCheck();

    void Pause();
    void Clear();

private:
    Object* Arena;

    Object* Player_First;
    Object* Player_Second;
    Object* Player_Third;
    Object* Player_Fourth;

    /*Object* Player_First_Text;
    Object* Player_Second_Text;
    Object* Player_Third_Text;
    Object* Player_Fourth_Text;*/

    Object* Explanation_Staff;
    /*Object* Explanation_Text_First;
    Object* Explanation_Text_Second;
    Object* Explanation_Text_Third;
    Object* Explanation_Text_Fourth;*/
    
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

    BitmapFont      font{};
    bool showing_editor = true;
};