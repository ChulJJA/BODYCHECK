/*
 * Author		:Sangmin Kim
 * File			:Engine.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Engine
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
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