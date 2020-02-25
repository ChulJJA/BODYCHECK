/*
 * Author		:ChulSeung Lee
 * File			:SoundOption.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2019/02/18
 * Description	:Cpp for main menu.
 *
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Input.h"
#include "ObjectManager.h"
#include "Component_Text.h"
#include "StateManager.h"
#include "Object.h"
#include "Transform.hpp"
#include "Engine.hpp"
#include "Sound_Manager.h"
#include "Windows.h"
#include <GLFW/glfw3.h>
#include "SoundOption.h"

namespace
{
	ObjectManager* object_manager = nullptr;
	StateManager* state_manager = nullptr;
}

void SoundOption::Load()
{
	sound.stop(SOUND::BGM);
	sound.play(SOUND::BGM2);
	sound.SetVolume(SOUND::BGM2, 0.3);

	state_manager = StateManager::GetStateManager();
	object_manager = ObjectManager::GetObjectManager();

	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
	Graphic::GetGraphic()->get_need_update_sprite() = true;
	if (!font.LoadFromFile(L"../assets/malgungothic.fnt"))
	{
		std::cout << "Failed to Load Font!" << std::endl;
	}
	SetMusicVolumeBox();
	SetMusicIcon();
	SetMusicText();
	SetMuteButton();
	SetInfoText();
}

void SoundOption::Update(float dt)
{
	mute_timer++;
	MusicVolume();
	Mute();
}

void SoundOption::Clear()
{
	object_manager->Clear();
}

void SoundOption::SetMusicIcon()
{
	music_icon[0] = new Object();
	music_icon[0]->AddComponent(new Sprite(music_icon[0], "../Sprite/icon.png", { -1400, -390 }, false));
	music_icon[0]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[0]);

	music_icon[1] = new Object();
	music_icon[1]->AddComponent(new Sprite(music_icon[1], "../Sprite/icon.png", { -1400, 120 }, false));
	music_icon[1]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[1]);

	music_icon[2] = new Object();
	music_icon[2]->AddComponent(new Sprite(music_icon[2], "../Sprite/icon.png", { -1400, 620 }, false));
	music_icon[2]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[2]);
}

void SoundOption::SetMusicVolumeBox()
{
	volume_box[0] = new Object();
	volume_box[0]->AddComponent(new Sprite(volume_box[0], "../Sprite/VolumeBox.png", { 0, 500 }, false));
	volume_box[0]->GetTransform().SetScale({ 30, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[0]);

	volume_box[1] = new Object();
	volume_box[1]->AddComponent(new Sprite(volume_box[1], "../Sprite/VolumeBox.png", { 0, 0 }, false));
	volume_box[1]->GetTransform().SetScale({ 30, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[1]);

	volume_box[2] = new Object();
	volume_box[2]->AddComponent(new Sprite(volume_box[2], "../Sprite/VolumeBox.png", { 0, -500 }, false));
	volume_box[2]->GetTransform().SetScale({ 30, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[2]);
}

void SoundOption::SetMusicText()
{
	music_volume_text = new Object();
	music_volume_text->SetTranslation({ 0,500 });
	music_volume_text->AddComponent(new TextComp(music_volume_text, L"", { 0,0,0,1 }, { 150,150 }, font));
	music_volume_text->GetComponentByTemplate<TextComp>()->Get_Need_To_Keep_Drawing() = true;
	ObjectManager::GetObjectManager()->AddObject(music_volume_text);
}

void SoundOption::MusicVolume()
{
	if (input.Is_Key_Pressed(GLFW_KEY_RIGHT) && mute_timer >= 30)
	{
		vector2 icon_translation = music_icon[0]->GetTransform().GetTranslation();
		float volume = sound.GetVolume(SOUND::BGM2);

		if(volume >= 1)
		{
			return;
		}
		
		sound.SetVolume(SOUND::BGM2, volume + 0.1);
		music_icon[0]->SetTranslation({ icon_translation.x + 30, icon_translation.y });

		mute_timer = 0;
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_LEFT) && mute_timer >= 30)
	{
		vector2 icon_translation = music_icon[0]->GetTransform().GetTranslation();
		float volume = sound.GetVolume(SOUND::BGM2);

		if(volume <= 0)
		{
			return;
		}
		
		sound.SetVolume(SOUND::BGM2, volume - 0.1);
		music_icon[0]->SetTranslation({ icon_translation.x - 30, icon_translation.y });

		mute_timer = 0;
	}
}

void SoundOption::SetMuteButton()
{
	mute_button = new Object();
	mute_button->AddComponent(new Sprite(mute_button, "../Sprite/Mute.png", { 500, 500 }, false));
	mute_button->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button);

	unmute_button = new Object();
	unmute_button->AddComponent(new Sprite(unmute_button, "../Sprite/Unmute.png", { 500, 500 }, false));
	unmute_button->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(unmute_button);
}

void SoundOption::Mute()
{
	FMOD_BOOL is_playing;
	float volume;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &is_playing);
	
	if (input.Is_Key_Triggered(GLFW_KEY_M) && is_playing)
	{
		mute_button->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,1 };
		unmute_button->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
		
		volume = sound.GetVolumeInfo(SOUND::BGM2) * 100;
		sound.stop(SOUND::BGM2);
		music_volume_text->GetComponentByTemplate<TextComp>()->GetText().SetString(std::to_wstring(volume));
		std::cout << volume / 100 << std::endl;
	}
	if (input.Is_Key_Triggered(GLFW_KEY_M) && !is_playing)
	{
		mute_button->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
		unmute_button->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,1};
		
		volume = sound.GetVolumeInfo(SOUND::BGM2);
		std::cout << volume << std::endl;

		sound.SetVolume(SOUND::BGM2, volume);
		sound.play(SOUND::BGM2);
		std::cout << volume << std::endl;
	}
}

void SoundOption::SetInfoText()
{
	//info_text = new Object();
	//info_text->SetTranslation({ -300,800 });
	//info_text->AddComponent(new TextComp(info_text, L"", { 0,0,0,1 }, { 150,150 }, font));
	//info_text->GetComponentByTemplate<TextComp>()->GetText().SetString();
	//info_text->GetComponentByTemplate<TextComp>()->Get_Need_To_Keep_Drawing() = true;
	//ObjectManager::GetObjectManager()->AddObject(info_text);

	//info_text[1] = new Object();
	//info_text[1]->SetTranslation({ -1000,700 });
	//info_text[1]->AddComponent(new TextComp(info_text[1], L"Master Volume", { 0,0,0,1 }, { 150,150 }, font));
	//info_text[1]->GetComponentByTemplate<TextComp>()->Get_Need_To_Keep_Drawing() = true;
	//ObjectManager::GetObjectManager()->AddObject(info_text[1]);

	//info_text[2] = new Object();
	//info_text[2]->SetTranslation({ -1000,200 });
	//info_text[2]->AddComponent(new TextComp(info_text[2], L"Music Volume", { 0,0,0,1 }, { 150,150 }, font));
	//info_text[2]->GetComponentByTemplate<TextComp>()->Get_Need_To_Keep_Drawing() = true;
	//ObjectManager::GetObjectManager()->AddObject(info_text[2]);

	//info_text[3] = new Object();
	//info_text[3]->SetTranslation({ -1000,-300 });
	//info_text[3]->AddComponent(new TextComp(info_text[3], L"SFX Volume", { 0,0,0,1 }, { 150,150 }, font));
	//info_text[3]->GetComponentByTemplate<TextComp>()->Get_Need_To_Keep_Drawing() = true;
	//ObjectManager::GetObjectManager()->AddObject(info_text[3]);
}
