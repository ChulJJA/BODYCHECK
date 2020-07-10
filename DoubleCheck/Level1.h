/*
 * Author		:Sangmin Kim
 * File			:Level.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Level1
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "State.h"
#include "Object.h"
#include "Common_Header.h"
#include "BitmapFont.hpp"
#include <thread>

class PLAYER_UI;


class Level1 : public State
{
public:

    Level1()
    {
        current_state = GameState::Game;
    }

    virtual void Load();
    virtual void Update(float dt);
    virtual void UnLoad();


    void Pause();
    void Clear();

	
private:
    Object* player;
    Object* player_sec;
    Object* player_third;
    Object* player_forth;

    Object* arena = nullptr;

    Object* pause;
    Object* restart_button;
    Object* restart_button_hover;
    Object* mainmenu_button;
    Object* mainmenu_button_hover;
    Object* option_button;
    Object* option_button_hover;
	
    PLAYER_UI* player_first_ui;
    PLAYER_UI* player_second_ui;
    PLAYER_UI* player_third_ui;
    PLAYER_UI* player_fourth_ui;

    Object* aud;

	bool showing_editor = true;
    bool dt_refreshed = false;
    bool timer_deleted = false;
    Object* prev_timer = nullptr;

    float gameDoneTimer = 0.f;

    vector2 player_sec_pos;
    vector2 player_sec_scale;
    std::string player_sec_sprite_path;

    vector2 player_third_pos;
    vector2 player_third_scale;
    std::string player_third_sprite_path;
};