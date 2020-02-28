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
#include "Messagebox.h"

float sound_timer = 0;

void Sound::Initialize()
{
    result = FMOD_System_Create(&f_system);
    result = FMOD_System_Init(f_system, 30, FMOD_INIT_NORMAL, 0);
}

void Sound::Load()
{
    result = FMOD_System_CreateSound(f_system, "Sounds/TeamDoubleCheck.mp3", FMOD_DEFAULT, nullptr, &sound[0]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/TeamDoubleCheck.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/DouDouDouDoubleCheck.mp3", FMOD_DEFAULT, nullptr, &sound[1]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/DouDouDouDoubleCheck.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/BGM.mp3", FMOD_LOOP_NORMAL, nullptr, &sound[2]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/BGM.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/Respawn.mp3", FMOD_DEFAULT, nullptr, &sound[3]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/Respawn.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/Click.mp3", FMOD_DEFAULT, nullptr, &sound[4]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/Click.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/BGM2.mp3", FMOD_LOOP_NORMAL, nullptr, &sound[5]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/BGM2.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/Crack.mp3", FMOD_DEFAULT, nullptr, &sound[6]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/Crack.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/Item.mp3", FMOD_DEFAULT, nullptr, &sound[7]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/Item.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/Dash.mp3", FMOD_DEFAULT, nullptr, &sound[8]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/Dash.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/HP.mp3", FMOD_DEFAULT, nullptr, &sound[9]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/HP.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/Die.mp3", FMOD_DEFAULT, nullptr, &sound[10]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/Die.mp3");
    }
    result = FMOD_System_CreateSound(f_system, "Sounds/BulkUp.mp3", FMOD_DEFAULT, nullptr, &sound[11]);
    if (result != FMOD_OK)
    {
        Messagebox::Init_Box("Sounds/BulkUp.mp3");
    }
}

/* Playing specific sound */
void Sound::Play(SOUND Sound_Num)
{
    result = FMOD_System_PlaySound(f_system, sound[(int)Sound_Num], 0, 0, &channel[(int)Sound_Num]);
    result = FMOD_System_Update(f_system);
    if (result != FMOD_OK)
    {
        return;
    }
}

void Sound::Stop(SOUND Sound_Num)
{
    result = FMOD_Channel_Stop(channel[static_cast<int>(Sound_Num)]);
}

float Sound::GetVolume(SOUND Channel_Num)
{
    float volume;
    result = FMOD_Channel_GetVolume(channel[static_cast<int>(Channel_Num)], &volume);

    return volume;
}

void  Sound::SetVolume(SOUND Channel_Num, float Volume)
{
    result = FMOD_Channel_SetVolume(channel[static_cast<int>(Channel_Num)], Volume);
    if (result != FMOD_OK)
    {
        return;
    }

    volume_info[static_cast<int>(Channel_Num)] = Volume;
}

float Sound::GetVolumeInfo(SOUND Channel_Num)
{
    return volume_info[static_cast<int>(Channel_Num)];
}
