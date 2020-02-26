/*
 * Author		:Suhwan Kim
 * File			:MainMenu.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Header file of MainMenu.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
    void SetMusicButton();
    void SetTestLevelButton();
    void ButtonSelector();
	
private:
    int pointer = 0;
    float button_timer = 0;
	
    Object* play_button;
    Object* play_button_hover;
    Object* music_button;
    Object* music_button_hover;
    Object* test_button;
    Object* test_button_hover;
};