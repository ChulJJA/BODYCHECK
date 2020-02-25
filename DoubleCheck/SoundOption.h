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
        next_level = {};
        is_next = false;
    }

    void SetMusicIcon();
    void SetMusicVolumeBox();
    void SetMusicText();
    void SetMuteButton();
    void MusicVolume();
    void Mute();
    void SetInfoText();

private:
    Object* music_icon[3];
    Object* volume_box[3];
    Object* music_volume_text;
    Object* mute_button;
    Object* unmute_button;
    Object* info_text;
    BitmapFont      font{};

    float mute_timer = 0;
};