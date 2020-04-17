#pragma once
/*
 * Author		:Chulseung Lee
 * File			:SoundOption.h
 * Term			:2020 Winter
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/02/11
 * Description	:Header file of SoundOption.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "State.h"
#include "vector2.hpp"

class Object;

class Option : public State
{
    int MUSIC;
    int SFX;
    int FULLSCREEN;
    int GAMESPEED;
	
    enum class BUTTON
    {
        FULLSCREEN,
        SFX,
		MUSIC,
		BACK,
	};
public:
    Option()
    {
	    current_state = GameState::Option;
    }

    virtual void Load();
    virtual void Update(float dt);
    virtual void Clear();
    virtual void UnLoad()
    {
        is_next = false;
        next_level = {};
    }

    void SetMusicIcon();
    void SetMusicVolumeBox();
    void SetMuteButton();
    void ButtonBehavior();
    void Mute();
    void SetFullScreenButton();
    void SetBackButton();
    void ButtonSelector();
    void SetSoundVolume(float value, bool isBGM = true);
private:
    Object* music_icon[2];
    Object* volume_box[2];
    Object* volume_box_hover[2];
    Object* mute_button[2];
    Object* unmute_button[2];
    Object* back_button;
    Object* back_button_hover;
    Object* full_screen_button;
    Object* full_screen_button_hover;
	
    BitmapFont      font{};

    float volume_timer;
    float button_timer;
    int pointer;
};