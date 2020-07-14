/*
 * Author		:Chulseung Lee
 * File			:Option.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Option
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
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
    	LIFE,
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

    void SetBackground();
    void SetMusicIcon();
    void SetMusicVolumeBox();
    void SetMuteButton();
    void ButtonBehavior();
    void Mute();
    void SetFullScreenButton();
    void SetBackButton();
    void ButtonSelector();
    void SetLifeButton();
    void SetFullBox();
    void SetSoundVolume(float value, bool isBGM = true);
private:
    Object* background;
    Object* music_icon[3];
    Object* volume_box[4];
    Object* volume_box_hover[2];
    Object* mute_button[2];
    Object* unmute_button[2];
    Object* back_button;
    Object* back_button_hover;
    Object* full_screen_button;
    Object* full_screen_button_hover;
    Object* lifeButton;
    Object* lifeButtonHover;

    Object* life_count;
    Object* lifeBox;
    Object* fullBox;
    Object* fullBoxCheck;
	
    Object* pointer1;
    Object* pointer2;
	
    BitmapFont      font{};

    float volume_timer;
    float button_timer;
    int pointer;
};