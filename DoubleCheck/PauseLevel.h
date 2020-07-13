/*
 * Author		:Chulseung Lee
 * File			:PauseLevel.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Pause Level
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */
#pragma once
#include "State.h"
#include "vector2.hpp"

class Object;

class PauseLevel : public State
{
    enum class BUTTON
    {
    	BACK,
        RESTART,
    	MAINMENU,
    	OPTION,
    	QUIT
    };
public:
    PauseLevel()
    {
        current_state = GameState::PauseLevel;
    }

    virtual void Load();
    virtual void Update(float dt);
    virtual void Clear();
    virtual void UnLoad()
    {
        is_next = false;
        next_level = {};
    }

    void SetRestartButton();
    void SetMainMenuButton();
    void SetOptionButton();
    void SetQuitButton();
    void SetBackButton();
    void ButtonSelector();
    void ButtonBehavior();
    void Background();

private:
    Object* background;
    Object* restartButton;
    Object* restartButtonHover;
    Object* mainMenuButton;
    Object* mainMenuButtonHover;
    Object* optionButton;
    Object* optionButtonHover;
    Object* quitButton;
    Object* quitButtonHover;
    Object* backButton;
    Object* backButtonHover;

    Object* pointer1;
    Object* pointer2;

    int pointer;
    float buttonTimer;

    Object* make_sure_dialogue;
    bool r_u_sure = false;
    bool r_u_sure_come = false;
    bool prev_cheerup_mode;
    //bool is_end_selected;
};