/*
 * Author		:Chulseung Lee
 * File			:TestLevel.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/02/15
 * Description	:Header file for TestLevl.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "State.h"
#include "Object.h"
#include "Common_Header.h"
#include "BitmapFont.hpp"

class PLAYER_UI;

class TestLevel : public State
{
public:

    TestLevel(): first_player(nullptr), second_player(nullptr), third_player(nullptr), fourth_player(nullptr),
                 a(nullptr), b(nullptr),
                 c(nullptr), d(nullptr),
                 text(nullptr), arena(nullptr),
                 player_first_ui(nullptr),
                 player_second_ui(nullptr),
                 player_third_ui(nullptr),
                 player_fourth_ui(nullptr)
    {
	    current_state = GameState::TestLevel;
    }

    virtual void Load();
    virtual void Update(float dt);
    virtual void UnLoad()
    {
        next_level = {};
        is_next = false;
    }

    void SetArena();
    void SetFirstPlayer();
    void SetSecondPlayer();
    void SetThirdPlayer();
    void SetFourthPlayer();

private:
    Object* first_player;
    Object* second_player;
    Object* third_player;
    Object* fourth_player;
    Object* a;
    Object* b;
    Object* c;
    Object* d;


    Object* text;
    Object* arena;

    PLAYER_UI* player_first_ui;
    PLAYER_UI* player_second_ui;
    PLAYER_UI* player_third_ui;
    PLAYER_UI* player_fourth_ui;

    BitmapFont      font{};
};