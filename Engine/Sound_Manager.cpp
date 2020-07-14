/*
 * Author		:Chulseung Lee
 * File			:Sound_Manager.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Sound Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Sound_Manager.h"
#include "fmod_errors.h"
#include "Messagebox.h"
#include <cassert>
#include <iostream>

float sound_timer = 0;

void Sound::ErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		Messagebox::Init_Box(FMOD_ErrorString(result));
		assert(result == 0);
	}
}

void Sound::Initialize()
{
	result = FMOD_System_Create(&f_system);
	ErrorCheck(result);
	result = FMOD_System_Init(f_system, SOUND_NUM, FMOD_INIT_NORMAL, nullptr);
	ErrorCheck(result);
	isInitialized = true;
	LoadSound();
	SetSoundGroup();
}

void Sound::LoadSound()
{
	result = FMOD_System_CreateSound(f_system, "Sounds/TeamDoubleCheck.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::TeamDoubleCheck)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/DouDouDouDoubleCheck.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::DouDouDouDoubleCheck)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/BGM.mp3", FMOD_LOOP_NORMAL, nullptr, &sound[static_cast<int>(SOUND::BGM)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Respawn.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Respawn)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Click.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Click)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/BGM2.mp3", FMOD_LOOP_NORMAL, nullptr, &sound[static_cast<int>(SOUND::BGM2)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Crack.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Crack)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Item.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Item)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Dash.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Dash)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/HP.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::HP)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Die.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Die)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/BulkUp.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::BulkUp)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/CountDown.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::CountDown)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/ItemAppear.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::ItemAppear)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/ItemAppear2.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::ItemAppear2)]);
	ErrorCheck(result);
	
	result = FMOD_System_CreateSound(f_system, "Sounds/Selected.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Selected)]);
	ErrorCheck(result);
	
	result = FMOD_System_CreateSound(f_system, "Sounds/Missile.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Missile)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/MissileShoot.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::MissileShoot)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/MissilePrepare.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::MissilePrepare)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/WallCrack.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::WallCrack)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/SoundControl.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::SoundControl)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Crowd.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Crowd)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Win.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Win)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Throwing.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Throwing)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/ThrowingHit.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::ThrowingHit)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/TimePause.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::TimePause)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Mine.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Mine)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/MineBomb.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::MineBomb)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/MineAlarm.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::MineAlarm)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/FingerSnap.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::FingerSnap)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/DemonLaugh.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::DemonLaugh)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/ClockTicking.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::ClockTicking)]);
	ErrorCheck(result);
	
	result = FMOD_System_CreateSound(f_system, "Sounds/EditorAppear.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::EditorAppear)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/SpeedUp.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::SpeedUp)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/BulkUp2.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::BulkUp2)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/EndBulkUp.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::EndBulkUp)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/CreditBGM.wav", FMOD_LOOP_NORMAL, nullptr, &sound[static_cast<int>(SOUND::CreditBGM)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/GameStart.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::GameStart)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/MatchBGM.wav", FMOD_LOOP_NORMAL, nullptr, &sound[static_cast<int>(SOUND::MatchBGM)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/PauseBGM.wav", FMOD_LOOP_NORMAL, nullptr, &sound[static_cast<int>(SOUND::PauseBGM)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/WinCrowd.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::WinCrowd)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Plask.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Plask)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/PlaskHoming.wav", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::PlaskHoming)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSoundGroup(f_system, "BGM", &bgm_group);
	ErrorCheck(result);
	
	result = FMOD_System_CreateSoundGroup(f_system, "SFX", &sfx_group);
	ErrorCheck(result);
}

void Sound::UnLoad()
{
	for(int count = 0; count < static_cast<int>(SOUND::END); ++count)
	{
		result = FMOD_Sound_Release(sound[count]);
	}
	result = FMOD_System_Release(f_system);
	isInitialized = false;
}

void Sound::Update(float dt)
{
	result = FMOD_System_Update(f_system);
	--mineAlarm;
}

void Sound::SetSoundGroup()
{
	for (int count = 0; count < static_cast<int>(SOUND::END); ++count)
	{
		result = FMOD_System_PlaySound(f_system, sound[count], 0, true, &channel[count]);
		ErrorCheck(result);

		if (count <= static_cast<int>(SOUND::PauseBGM))
		{
			result = FMOD_Sound_SetSoundGroup(sound[count], bgm_group);
			ErrorCheck(result);
			result = FMOD_Channel_Stop(channel[count]);
			ErrorCheck(result);
		}
		else if (count < static_cast<int>(SOUND::END))
		{
			result = FMOD_Sound_SetSoundGroup(sound[count], sfx_group);
			ErrorCheck(result);
		}
	}

	result = FMOD_SoundGroup_SetVolume(bgm_group, BGM_Volume);
	ErrorCheck(result);
	result = FMOD_SoundGroup_SetVolume(sfx_group, SFX_Volume);
	ErrorCheck(result);
}

void Sound::Play(SOUND sound_Num)
{
	result = FMOD_System_PlaySound(f_system, sound[(int)sound_Num], 0, 0, &channel[(int)sound_Num]);
	ErrorCheck(result);
}

void Sound::Stop(SOUND sound_Num)
{
	result = FMOD_Channel_Stop(channel[static_cast<int>(sound_Num)]);
	ErrorCheck(result);
}

float Sound::GetVolume(SOUND channel_Num)
{
	float volume;
	result = FMOD_Channel_GetVolume(channel[static_cast<int>(channel_Num)], &volume);
	ErrorCheck(result);

	return volume;
}

void  Sound::SetVolume(SOUND channel_Num, float Volume)
{
	result = FMOD_Channel_SetVolume(channel[static_cast<int>(channel_Num)], Volume);
	ErrorCheck(result);

	volume_info[static_cast<int>(channel_Num)] = Volume;
}

float Sound::GetSoundGroupVolume(bool is_bgm)
{
	float volume;
	
	if(is_bgm == true)
	{
		result = FMOD_SoundGroup_GetVolume(bgm_group, &volume);
		ErrorCheck(result);
	}
	else
	{
		result = FMOD_SoundGroup_GetVolume(sfx_group, &volume);
		ErrorCheck(result);
	}

	return volume;
}

void Sound::SetSoundGroupVolume(bool is_bgm, float volume)
{
	if(is_bgm == true)
	{
		result = FMOD_SoundGroup_SetVolume(bgm_group, volume);
		BGM_Volume = volume;
		ErrorCheck(result);
	}
	else
	{
		result = FMOD_SoundGroup_SetVolume(sfx_group, volume);
		SFX_Volume = volume;
		ErrorCheck(result);
	}
}

void Sound::StopAllSFX()
{
	for (int count = static_cast<int>(SOUND::PauseBGM) + 1; count < static_cast<int>(SOUND::END); ++count)
	{
		FMOD_BOOL isSFXPlaying;
		FMOD_Channel_IsPlaying(channel[count], &isSFXPlaying);
		if(isSFXPlaying)
		{
			Stop(static_cast<SOUND>(count));
		}
	}
}
