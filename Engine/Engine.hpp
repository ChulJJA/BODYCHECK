/*
 * Author		:Sangmin Kim
 * File			:Engine.hpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Header file for engine.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Timer.hpp"
#include "Sound_Manager.h"

extern Sound sound;

class Engine
{
public:
    Engine() = default;

    void Init();
    void Update();
    void Delete();
    void Reset();
    void Clear();
    bool IsDone() { return is_done; }

private:
    bool is_done = false;
    float m_dt;
    Timer game_timer;
	bool showing_editor = false;

};