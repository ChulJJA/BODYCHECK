/*
 * Author		:Suhwan Kim
 * File			:Logo.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Header file for Logo.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "State.h"

class Object;

class Logo : public State
{
public:
    Logo() :State()
    {
        current_state = GameState::Logo;
    }

    virtual void Load();
    virtual void Update(float dt);
    virtual void Clear();
    virtual void UnLoad()
    {
        next_level = {};
        is_next = false;
    }
private:
    bool logo_on = true;
    bool logo_on2 = false;
    bool logo_on3 = false;
    bool logo_dead = true;
    bool logo_dead2 = false;
    bool logo_dead3 = false;

    bool next = false;
    float logo_timer = 0;
    Object* digipen_logo;
    Object* fmod_logo;
    Object* team_logo;
};