#pragma once
/*
 * Author		:Chulseung Lee
 * File			:PauseLevel.h
 * Term			:2020 Winter
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/04/30
 * Description	:Header file of SoundOption.cpp
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
        RESTART,
    	MAINMENU,
    	OPTION,
    	QUIT,
    	BACK
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

    int pointer;
    float buttonTimer;
};