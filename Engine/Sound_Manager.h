/*
 * Author		:Chulseung Lee
 * File			:Sound_Manager.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Sound_Manager.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#define SOUND_NUM 20

enum class SOUND
{
    TeamDoubleCheck = 0,
    DouDouDouDoubleCheck,
    BGM,
    Respawn,
    Click,
    BGM2,
    Crack,
    Item,
    Dash,
    HP,
    Die,
    BulkUp
};

#include "fmod.hpp"
extern float sound_timer;

class Sound {
public:
    FMOD_RESULT result;
    FMOD_SYSTEM* f_system;
    FMOD_SOUND* sound[SOUND_NUM];
    FMOD_CHANNEL* channel[SOUND_NUM];

    void initialize();
    void load();
    void play(SOUND Sound_Num);
    void volume(SOUND Channel_Num, float Volume);
    void stop(SOUND Sound_Num);

    float GetVolume(SOUND Channel_Num);
    void SetVolume(SOUND Channel_Num, float Volume);
    float GetVolumeInfo(SOUND Channel_Num);
	
private:
    float volume_info[20] = {};
};