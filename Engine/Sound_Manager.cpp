/*
 * Author		:Chulseung Lee
 * File			:Sound_Manager.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for implement sound manager of engine. Which control music play & stop & volume.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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

	result = FMOD_System_CreateSound(f_system, "Sounds/Crack.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Crack)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Item.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Item)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Dash.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Dash)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/HP.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::HP)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/Die.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::Die)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/BulkUp.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::BulkUp)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/CountDown.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::CountDown)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/ItemAppear.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::ItemAppear)]);
	ErrorCheck(result);

	result = FMOD_System_CreateSound(f_system, "Sounds/ItemAppear2.mp3", FMOD_DEFAULT, nullptr, &sound[static_cast<int>(SOUND::ItemAppear2)]);
	ErrorCheck(result);
	
	result = FMOD_System_CreateSoundGroup(f_system, "BGM", &bgm_group);
	ErrorCheck(result);

	result = FMOD_System_CreateSoundGroup(f_system, "SFX", &sfx_group);
	ErrorCheck(result);
}

void Sound::UnLoad()
{
	result = FMOD_System_Release(f_system);
	isInitialized = false;
}

void Sound::SetSoundGroup()
{
	for (int count = 0; count < static_cast<int>(SOUND::END); ++count)
	{
		result = FMOD_System_PlaySound(f_system, sound[count], 0, true, &channel[count]);
		ErrorCheck(result);

		if (count <= static_cast<int>(SOUND::BGM2))
		{
			result = FMOD_Sound_SetSoundGroup(sound[count], bgm_group);
			ErrorCheck(result);
			result = FMOD_Channel_Stop(channel[count]);
		}
		else if (count < static_cast<int>(SOUND::END))
		{
			result = FMOD_Sound_SetSoundGroup(sound[count], sfx_group);
			ErrorCheck(result);
		}
	}

	result = FMOD_SoundGroup_SetVolume(bgm_group, 0.5f);
	ErrorCheck(result);
	result = FMOD_SoundGroup_SetVolume(sfx_group, 0.5f);
	ErrorCheck(result);
}

void Sound::Play(SOUND sound_Num)
{
	float volume;
	result = FMOD_System_PlaySound(f_system, sound[(int)sound_Num], 0, 0, &channel[(int)sound_Num]);
	FMOD_Channel_GetVolume(channel[(int)sound_Num], &volume);
	std::cout << "sex: " << volume << std::endl;
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
		ErrorCheck(result);
	}
	else
	{
		result = FMOD_SoundGroup_SetVolume(sfx_group, volume);
		ErrorCheck(result);
	}
}