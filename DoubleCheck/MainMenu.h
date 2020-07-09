/*
 * Author		:Chulseung Lee
 * File			:MainMenu.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Main Menu
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "State.h"
#include "vector2.hpp"



class Object;

class MainMenu : public State
{
    enum class BUTTON
    {
        START,
        TUTORIAL,
        MUSIC,
        TEST
    };
	
public:
    MainMenu() :State()
    {
        current_state = GameState::Menu;
    }

    virtual void Load();
    virtual void Update(float dt);
    virtual void Clear();
    virtual void UnLoad()
    {
        next_level = {};
        is_next = false;
    }

    void SetPlayButton();
    void SetTutorialButton();
    void SetMusicButton();
    void SetTestLevelButton();
    void ButtonSelector();
    void Set_Player_Button();
	
private:
    int pointer;
    float button_timer;
	
    Object* play_button;
    Object* play_button_hover;
    Object* tutorial_button;
    Object* tutorial_button_hover;
    Object* music_button;
    Object* music_button_hover;
    Object* test_button;
    Object* test_button_hover;

    Object* player_1_button;
    Object* player_2_button;
    bool p_1_selected = false;
    bool p_2_selected = false;
    Object* player_sec;
    Object* player_third;

    vector2 player_sec_pos{ -800.f, 0.f };
    vector2 player_third_pos{ 800.f, 0.f };

    Object* pointer1;
    Object* pointer2;
};