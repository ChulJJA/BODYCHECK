/*
 * Author		:Chulseung Lee
 * File			:Sound_Manager.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Sound Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#define SOUND_NUM 50

enum class SOUND
{
	BGM = 0,
	BGM2,
	CreditBGM,
	MatchBGM,
	PauseBGM,
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
	Crowd,
	Win,
	Throwing,
	ThrowingHit,
	TimePause,
	Mine,
	MineBomb,
	MineAlarm,
	FingerSnap,
	DemonLaugh,
	ClockTicking,
	EditorAppear,
	SpeedUp,
	BulkUp2,
	EndBulkUp,
	GameStart,
	WinCrowd,
	Plask,
	PlaskHoming,
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
	void StopAllSFX();
	bool isInitialized;
	float mineAlarm = 60.f;
	SOUND currentBGM;
private:
	float volume_info[SOUND_NUM] = {};
	float SFX_Volume = 0.5f;
	float BGM_Volume = 0.5f;
};