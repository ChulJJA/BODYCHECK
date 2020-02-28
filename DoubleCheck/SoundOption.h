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

class SoundOption : public State
{
	enum class BUTTON
	{
		MASTER,
		MUSIC,
		SFX,
		BACK
	};
public:
    SoundOption()
    {
	    current_state = GameState::Sound;
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
    void MusicVolume();
    void Mute();
    void SetInfoText();
    void SetBackButton();
    void ButtonSelector();

private:
    Object* music_icon[3];
    Object* volume_box[3];
    Object* volume_box_hover[3];
    Object* music_volume_text;
    Object* mute_button[3];
    Object* unmute_button[3];
    Object* back_button;
    Object* back_button_hover;
    Object* info_text[3];
	
    BitmapFont      font{};

    float mute_timer = 0;
    float button_timer = 0;
    int pointer = 0;
};