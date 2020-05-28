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
#define SOUND_NUM 30

enum class SOUND
{
	BGM = 0,
	BGM2,
	TeamDoubleCheck,
	DouDouDouDoubleCheck,
	Respawn,
	Click,
	Crack,
	Item,
	Dash,
	HP,
	Die,
	BulkUp,
	CountDown,
	ItemAppear,
	ItemAppear2,
	Selected,
	Missile,
	MissileShoot,
	MissilePrepare,
	WallCrack,
	SoundControl,
	END
};

#include "fmod.hpp"
extern float sound_timer;

class Sound {

public:
	FMOD_RESULT result;
	FMOD_SYSTEM* f_system;
	FMOD_SOUND* sound[SOUND_NUM];
	FMOD_CHANNEL* channel[SOUND_NUM];
	FMOD_SOUNDGROUP* bgm_group, * sfx_group;

	void ErrorCheck(FMOD_RESULT result);
	void Initialize();
	void LoadSound();
	void UnLoad();
	void Update(float dt);
	void SetSoundGroup();
	void Play(SOUND sound_Num);
	void Stop(SOUND sound_Num);
	float GetVolume(SOUND channel_Num);
	void SetVolume(SOUND channel_Num, float volume);
	float GetSoundGroupVolume(bool is_bgm);
	void SetSoundGroupVolume(bool is_bgm, float volume);
	bool isInitialized;
private:
	float volume_info[SOUND_NUM] = {};
	float SFX_Volume = 1.f;
	float BGM_Volume = 0.25f;
};