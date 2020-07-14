/*
 * Author		:Chulseung Lee
 * File			:Credit.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Test Level
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "State.h"
#include "Object.h"
#include "Common_Header.h"
#include "BitmapFont.hpp"

class Object;

class Credit : public State
{
public:

    Credit()
    {
	    current_state = GameState::Credit;
    }

    virtual void Load();
    virtual void Update(float dt);
    virtual void Clear();
    virtual void UnLoad()
    {
        next_level = {};
        is_next = false;
    }

    void SetTestSprite();

private:
    Object* credit;
    float second = 0.f;
};