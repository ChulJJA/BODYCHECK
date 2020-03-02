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
#include "UsefulTools.hpp"
namespace
{
	ObjectManager* object_manager = nullptr;
	StateManager* state_manager = nullptr;
}

void SoundOption::Load()
{
	if (!font.LoadFromFile(L"../assets/malgungothic.fnt"))
	{
		std::cout << "Failed to Load Font!" << std::endl;
	}
	sound.Stop(SOUND::BGM);
	sound.Play(SOUND::BGM2);
	sound.SetVolume(SOUND::BGM2, 0.5);
	
	state_manager = StateManager::GetStateManager();	
	object_manager = ObjectManager::GetObjectManager();

	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
	Graphic::GetGraphic()->get_need_update_sprite() = true;

	SetMusicVolumeBox();
	SetMusicIcon();
	SetMuteButton();
	SetInfoText();
	SetBackButton();
}

void SoundOption::Update(float dt)
{
	mute_timer++;
	button_timer++;

	if (button_timer >= 10)
	{
		ButtonSelector();
	}
	
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
	music_icon[0]->AddComponent(new Sprite(music_icon[0], "../Sprite/icon.png", { -50, -390 }, false));
	music_icon[0]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[0]);

	music_icon[1] = new Object();
	music_icon[1]->AddComponent(new Sprite(music_icon[1], "../Sprite/icon.png", { -50, 120 }, false));
	music_icon[1]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[1]);

	music_icon[2] = new Object();
	music_icon[2]->AddComponent(new Sprite(music_icon[2], "../Sprite/icon.png", { -50, 620 }, false));
	music_icon[2]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[2]);
}

void SoundOption::SetMusicVolumeBox()
{
	volume_box[0] = new Object();
	volume_box[0]->AddComponent(new Sprite(volume_box[0], "../Sprite/VolumeBox.png", { 0, 500 }, false));
	volume_box[0]->GetTransform().SetScale({ 30, 5 });
	volume_box[0]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(volume_box[0]);
	volume_box_hover[0] = new Object();
	volume_box_hover[0]->AddComponent(new Sprite(volume_box_hover[0], "../Sprite/VolumeBoxHover.png", { 0, 500 }, false));
	volume_box_hover[0]->GetTransform().SetScale({ 30, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box_hover[0]);
	
	volume_box[1] = new Object();
	volume_box[1]->AddComponent(new Sprite(volume_box[1], "../Sprite/VolumeBox.png", { 0, 0 }, false));
	volume_box[1]->GetTransform().SetScale({ 30, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[1]);
	volume_box_hover[1] = new Object();
	volume_box_hover[1]->AddComponent(new Sprite(volume_box_hover[1], "../Sprite/VolumeBoxHover.png", { 0, 0 }, false));
	volume_box_hover[1]->GetTransform().SetScale({ 30, 5 });
	volume_box_hover[1]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(volume_box_hover[1]);
	
	volume_box[2] = new Object();
	volume_box[2]->AddComponent(new Sprite(volume_box[2], "../Sprite/VolumeBox.png", { 0, -500 }, false));
	volume_box[2]->GetTransform().SetScale({ 30, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[2]);
	volume_box_hover[2] = new Object();
	volume_box_hover[2]->AddComponent(new Sprite(volume_box_hover[2], "../Sprite/VolumeBoxHover.png", { 0, -500 }, false));
	volume_box_hover[2]->GetTransform().SetScale({ 30, 5 });
	volume_box_hover[2]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(volume_box_hover[2]);
}

void SoundOption::MusicVolume()
{
	float volume = sound.GetVolume(SOUND::BGM2);
	if (mute_timer >= 10 && pointer == static_cast<int>(BUTTON::MASTER))
	{
		
		std::cout << volume << "initial" << std::endl;

		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
		{
			vector2 icon_translation = music_icon[2]->GetTransform().GetTranslation();
			 volume = sound.GetVolume(SOUND::BGM2);
			std::cout << volume << "before" << std::endl;
			if (volume >= 1)
			{
				return;
			}

			sound.SetVolume(SOUND::BGM2, volume + 0.25f);
			music_icon[2]->SetTranslation({ icon_translation.x + 680, icon_translation.y });
			std::cout << volume << "after" << std::endl;

			mute_timer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
		{
			vector2 icon_translation = music_icon[2]->GetTransform().GetTranslation();
			volume = sound.GetVolume(SOUND::BGM2);
			std::cout << volume << "before" << std::endl;

			if (volume <= 0)
			{
				return;
			}

			sound.SetVolume(SOUND::BGM2, volume - 0.25f);
			music_icon[2]->SetTranslation({ icon_translation.x - 680, icon_translation.y });
			std::cout << volume << "after" << std::endl;

			mute_timer = 0;
		}
	}
	else if (mute_timer >= 10 && pointer == static_cast<int>(BUTTON::MUSIC))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
		{
			vector2 icon_translation = music_icon[1]->GetTransform().GetTranslation();
			volume = sound.GetVolume(SOUND::BGM2);

			if (volume >= 1)
			{
				return;
			}

			sound.SetVolume(SOUND::BGM2, volume + 0.25f);
			music_icon[1]->SetTranslation({ icon_translation.x + 680, icon_translation.y });

			mute_timer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
		{
			vector2 icon_translation = music_icon[1]->GetTransform().GetTranslation();
			volume = sound.GetVolume(SOUND::BGM2);

			if (volume <= 0)
			{
				return;
			}

			sound.SetVolume(SOUND::BGM2, volume - 0.25f);
			music_icon[1]->SetTranslation({ icon_translation.x - 680, icon_translation.y });

			mute_timer = 0;
		}
	}
	else if (mute_timer >= 10 && pointer == static_cast<int>(BUTTON::SFX))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
		{
			vector2 icon_translation = music_icon[0]->GetTransform().GetTranslation();
			volume = sound.GetVolume(SOUND::BGM2);

			if (volume >= 1)
			{
				return;
			}

			sound.SetVolume(SOUND::BGM2, volume + 0.25f);
			music_icon[0]->SetTranslation({ icon_translation.x + 680, icon_translation.y });

			mute_timer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
		{
			vector2 icon_translation = music_icon[0]->GetTransform().GetTranslation();
			volume = sound.GetVolume(SOUND::BGM2);

			if (volume <= 0)
			{
				return;
			}

			sound.SetVolume(SOUND::BGM2, volume - 0.25f);
			music_icon[0]->SetTranslation({ icon_translation.x - 680, icon_translation.y });

			mute_timer = 0;
		}
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && pointer == static_cast<int>(BUTTON::BACK))
	{
		sound.Play(SOUND::Click);
		is_next = true;
		next_level = "Menu";
		Clear();
	}

}

void SoundOption::SetMuteButton()
{
	mute_button[0] = new Object();
	mute_button[0]->AddComponent(new Sprite(mute_button[0], "../Sprite/Mute.png", { 1600, 600 }, false));
	mute_button[0]->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button[0]);
	unmute_button[0] = new Object();
	unmute_button[0]->AddComponent(new Sprite(unmute_button[0], "../Sprite/Unmute.png", { 1600, 600 }, false));
	unmute_button[0]->GetTransform().SetScale({ 1, 1 });
	unmute_button[0]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(unmute_button[0]);

	mute_button[1] = new Object();
	mute_button[1]->AddComponent(new Sprite(mute_button[1], "../Sprite/Mute.png", { 1600, 100 }, false));
	mute_button[1]->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button[1]);
	unmute_button[1] = new Object();
	unmute_button[1]->AddComponent(new Sprite(unmute_button[1], "../Sprite/Unmute.png", { 1600, 100 }, false));
	unmute_button[1]->GetTransform().SetScale({ 1, 1 });
	unmute_button[1]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(unmute_button[1]);

	mute_button[2] = new Object();
	mute_button[2]->AddComponent(new Sprite(mute_button[2], "../Sprite/Mute.png", { 1600, -400 }, false));
	mute_button[2]->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button[2]);
	unmute_button[2] = new Object();
	unmute_button[2]->AddComponent(new Sprite(unmute_button[2], "../Sprite/Unmute.png", { 1600, -400 }, false));
	unmute_button[2]->GetTransform().SetScale({ 1, 1 });
	unmute_button[2]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(unmute_button[2]);
}

void SoundOption::Mute()
{
	FMOD_BOOL is_playing;
	float volume;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &is_playing);
	
	if (input.Is_Key_Triggered(GLFW_KEY_M) && is_playing)
	{
		ObjectHover(unmute_button[0], mute_button[0]);
		
		volume = sound.GetVolume(SOUND::BGM2);
		sound.Stop(SOUND::BGM2);
		std::cout << volume / 100 << std::endl;
	}
	if (input.Is_Key_Triggered(GLFW_KEY_M) && !is_playing)
	{
		ObjectHover(mute_button[0], unmute_button[0]);
		
		volume = sound.GetVolume(SOUND::BGM2);
			std::cout << volume << std::endl;

		sound.SetVolume(SOUND::BGM2, volume);
		sound.Play(SOUND::BGM2);
		std::cout << volume << std::endl;
	}
}

void SoundOption::SetInfoText()
{
	info_text[0] = new Object();
	info_text[0]->AddComponent(new Sprite(info_text[0], "../Sprite/Master.png", { -1300, 800 }, false));
	info_text[0]->GetTransform().SetScale({ 3, 3 });
	ObjectManager::GetObjectManager()->AddObject(info_text[0]);

	info_text[1] = new Object();
	info_text[1]->AddComponent(new Sprite(info_text[1], "../Sprite/Music.png", { -1300, 300 }, false));
	info_text[1]->GetTransform().SetScale({ 3, 3 });
	ObjectManager::GetObjectManager()->AddObject(info_text[1]);

	info_text[2] = new Object();
	info_text[2]->AddComponent(new Sprite(info_text[2], "../Sprite/SFX.png", { -1300, -200 }, false));
	info_text[2]->GetTransform().SetScale({ 3, 3 });
	ObjectManager::GetObjectManager()->AddObject(info_text[2]);
}

void SoundOption::SetBackButton()
{
	back_button = new Object();
	back_button->AddComponent(new Sprite(back_button, "../Sprite/BackButton.png", { 0, -700 }, false));
	back_button->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(back_button);

	back_button_hover = new Object();
	back_button_hover->AddComponent(new Sprite(back_button_hover, "../Sprite/BackButtonHover.png", { 0, -700 }, false));
	back_button_hover->GetTransform().SetScale({ 5, 5 });
	back_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(back_button_hover);
}

void SoundOption::ButtonSelector()
{
	if (input.Is_Key_Pressed(GLFW_KEY_DOWN) && pointer <= static_cast<int>(BUTTON::BACK))
	{
		pointer++;

		if (pointer == static_cast<int>(BUTTON::MASTER))
		{
			ObjectHover(volume_box[0], volume_box_hover[0]);
		}
		else if (pointer == static_cast<int>(BUTTON::MUSIC))
		{
			ObjectHover(volume_box[1], volume_box_hover[1]);
			ObjectHover(volume_box_hover[0], volume_box[0]);
		}
		else if (pointer == static_cast<int>(BUTTON::SFX))
		{
			ObjectHover(volume_box[2], volume_box_hover[2]);
			ObjectHover(volume_box_hover[1], volume_box[1]);
		}
		else if (pointer == static_cast<int>(BUTTON::BACK))
		{
			ObjectHover(back_button, back_button_hover);
			ObjectHover(volume_box_hover[2], volume_box[2]);
		}
		else if (pointer > 3)
		{
			pointer = 3;
		}
		button_timer = 0;
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_UP) && pointer >= static_cast<int>(BUTTON::MASTER))
	{
		pointer--;

		if (pointer == static_cast<int>(BUTTON::MASTER))
		{
			ObjectHover(volume_box[0], volume_box_hover[0]);
			ObjectHover(volume_box_hover[1], volume_box[1]);
		}
		else if (pointer == static_cast<int>(BUTTON::MUSIC))
		{
			ObjectHover(volume_box[1], volume_box_hover[1]);
			ObjectHover(volume_box_hover[2], volume_box[2]);
		}
		else if (pointer == static_cast<int>(BUTTON::SFX))
		{
			ObjectHover(volume_box[2], volume_box_hover[2]);
			ObjectHover(back_button_hover, back_button);
		}
		else if (pointer == static_cast<int>(BUTTON::BACK))
		{
			ObjectHover(back_button, back_button_hover);
		}
		else if (pointer < 0)
		{
			pointer = 0;
		}
		button_timer = 0;
	}
}