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
#include "Application.hpp"
#include "Object.h"
#include "Transform.hpp"
#include "Engine.hpp"
#include "Sound_Manager.h"
#include "Windows.h"
#include <GLFW/glfw3.h>
#include "Option.h"
#include "UsefulTools.hpp"
#include "StateManager.h"
namespace
{
	ObjectManager* object_manager = nullptr;
	StateManager* state_manager = nullptr;
	Application* app = Application::Get_Application();
}

void Option::Load()
{
	state_manager = StateManager::GetStateManager();
	object_manager = ObjectManager::GetObjectManager();
	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
	Graphic::GetGraphic()->get_need_update_sprite() = true;

	volume_timer = 0;
	button_timer = 0;
	pointer = 0;

	SetMusicVolumeBox();
	SetMusicIcon();
	SetMuteButton();
	SetFullScreenButton();
	SetBackButton();
}

void Option::Update(float dt)
{
	volume_timer++;
	button_timer++;

	Mute();
	if (button_timer >= 10)
	{
		ButtonSelector();
	}
	if (volume_timer >= 10)
	{
		ButtonBehavior();
	}
}

void Option::Clear()
{
	music_icon[0]->SetDeadCondition(true);
	music_icon[1]->SetDeadCondition(true);
	volume_box[0]->SetDeadCondition(true);
	volume_box[1]->SetDeadCondition(true);
	volume_box_hover[0]->SetDeadCondition(true);
	volume_box_hover[1]->SetDeadCondition(true);
	mute_button[0]->SetDeadCondition(true);
	mute_button[1]->SetDeadCondition(true);
	unmute_button[0]->SetDeadCondition(true);
	unmute_button[1]->SetDeadCondition(true);
	back_button->SetDeadCondition(true);
	back_button_hover->SetDeadCondition(true);
	full_screen_button->SetDeadCondition(true);
	full_screen_button_hover->SetDeadCondition(true);
}

void Option::SetMusicIcon()
{
	const float sfx_volume = sound.GetSoundGroupVolume(false);
	const float bgm_volume = sound.GetSoundGroupVolume(true);
	const float initial_sfx_icon = sfx_volume * 4 * 680;
	const float initial_bgm_icon = bgm_volume * 4 * 680;

	music_icon[0] = new Object();
	music_icon[0]->AddComponent(new Sprite(music_icon[0], "../Sprite/icon.png", { -1410 + initial_sfx_icon, 120 }, false));
	music_icon[0]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[0]);

	music_icon[1] = new Object();
	music_icon[1]->AddComponent(new Sprite(music_icon[1], "../Sprite/icon.png", { -1410 + initial_bgm_icon, -390 }, false));
	music_icon[1]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[1]);
}

void Option::SetMusicVolumeBox()
{
	volume_box[0] = new Object();
	volume_box[0]->AddComponent(new Sprite(volume_box[0], "../Sprite/VolumeBox.png", { 0, 0 }, false));
	volume_box[0]->GetTransform().SetScale({ 30, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[0]);
	volume_box_hover[0] = new Object();
	volume_box_hover[0]->AddComponent(new Sprite(volume_box_hover[0], "../Sprite/VolumeBoxHover.png", { 0, 0 }, false));
	volume_box_hover[0]->GetTransform().SetScale({ 30, 5 });
	volume_box_hover[0]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(volume_box_hover[0]);

	volume_box[1] = new Object();
	volume_box[1]->AddComponent(new Sprite(volume_box[1], "../Sprite/VolumeBox.png", { 0, -500 }, false));
	volume_box[1]->GetTransform().SetScale({ 30, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[1]);
	volume_box_hover[1] = new Object();
	volume_box_hover[1]->AddComponent(new Sprite(volume_box_hover[1], "../Sprite/VolumeBoxHover.png", { 0, -500 }, false));
	volume_box_hover[1]->GetTransform().SetScale({ 30, 5 });
	volume_box_hover[1]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(volume_box_hover[1]);
}

void Option::ButtonBehavior()
{
	float volume;

	if (pointer == static_cast<int>(BUTTON::FULLSCREEN))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE))
		{
			app->Toggle_Fullscreen();
			volume_timer = 0;
		}
	}
	else if (pointer == static_cast<int>(BUTTON::SFX))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
		{
			const vector2 icon_translation = music_icon[0]->GetTransform().GetTranslation();
			volume = sound.GetSoundGroupVolume(true);
			if (volume >= 1)
			{
				return;
			}
			SetSoundVolume(0.25, true);
			music_icon[0]->SetTranslation({ icon_translation.x + 680, icon_translation.y });

			volume_timer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
		{
			vector2 icon_translation = music_icon[0]->GetTransform().GetTranslation();
			volume = sound.GetSoundGroupVolume(true);
			if (volume <= 0)
			{
				return;
			}

			SetSoundVolume(-0.25, true);
			music_icon[0]->SetTranslation({ icon_translation.x - 680, icon_translation.y });

			volume_timer = 0;
		}
	}
	else if (pointer == static_cast<int>(BUTTON::MUSIC))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
		{
			vector2 icon_translation = music_icon[1]->GetTransform().GetTranslation();
			volume = sound.GetSoundGroupVolume(false);
			if (volume >= 1)
			{
				return;
			}

			SetSoundVolume(0.25, false);
			music_icon[1]->SetTranslation({ icon_translation.x + 680, icon_translation.y });

			volume_timer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
		{
			vector2 icon_translation = music_icon[1]->GetTransform().GetTranslation();
			volume = sound.GetSoundGroupVolume(false);
			if (volume <= 0)
			{
				return;
			}

			SetSoundVolume(-0.25, false);
			music_icon[1]->SetTranslation({ icon_translation.x - 680, icon_translation.y });

			volume_timer = 0;
		}
	}
	else if (pointer == static_cast<int>(BUTTON::BACK) && state_manager->GetPrevState()->GetStateInfo() == GameState::Menu)
	{
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE))
		{
			pointer = static_cast<int>(BUTTON::MUSIC);
			sound.Play(SOUND::Click);
			is_next = true;
			next_level = "Menu";
			Clear();
		}

	}
	else if (pointer == static_cast<int>(BUTTON::BACK) && state_manager->GetPrevState()->GetStateInfo() == GameState::Game)
	{
		if (input.Is_Key_Pressed(GLFW_KEY_SPACE))
		{
			pointer = static_cast<int>(BUTTON::MUSIC);
			sound.Play(SOUND::Click);
			state_manager->BackToLevel();
			Clear();
		}

	}
}

void Option::SetMuteButton()
{
	mute_button[0] = new Object();
	mute_button[0]->AddComponent(new Sprite(mute_button[0], "../Sprite/Mute.png", { 1600, 100 }, false));
	mute_button[0]->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button[0]);
	unmute_button[0] = new Object();
	unmute_button[0]->AddComponent(new Sprite(unmute_button[0], "../Sprite/Unmute.png", { 1600, 100 }, false));
	unmute_button[0]->GetTransform().SetScale({ 1, 1 });
	unmute_button[0]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(unmute_button[0]);

	mute_button[1] = new Object();
	mute_button[1]->AddComponent(new Sprite(mute_button[1], "../Sprite/Mute.png", { 1600, -400 }, false));
	mute_button[1]->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button[1]);
	unmute_button[1] = new Object();
	unmute_button[1]->AddComponent(new Sprite(unmute_button[1], "../Sprite/Unmute.png", { 1600, -400 }, false));
	unmute_button[1]->GetTransform().SetScale({ 1, 1 });
	unmute_button[1]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(unmute_button[1]);
}

void Option::Mute()
{
	float bgm_volume = sound.GetSoundGroupVolume(true);
	float sfx_volume = sound.GetSoundGroupVolume(false);

	if (bgm_volume <= 0)
	{
		ObjectHover(unmute_button[0], mute_button[0]);
	}
	else if (bgm_volume > 0)
	{
		ObjectHover(mute_button[0], unmute_button[0]);
	}

	if (sfx_volume <= 0)
	{
		ObjectHover(unmute_button[1], mute_button[1]);
	}
	else if (sfx_volume > 0)
	{
		ObjectHover(mute_button[1], unmute_button[1]);
	}
}

void Option::SetFullScreenButton()
{
	full_screen_button = new Object();
	full_screen_button->AddComponent(new Sprite(full_screen_button, "../Sprite/FullScreenButton.png", { 0, 800 }, false));
	full_screen_button->GetTransform().SetScale({ 5, 5 });
	full_screen_button->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(full_screen_button);

	full_screen_button_hover = new Object();
	full_screen_button_hover->AddComponent(new Sprite(full_screen_button_hover, "../Sprite/FullScreenButtonHover.png", { 0, 800 }, false));
	full_screen_button_hover->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(full_screen_button_hover);
}

void Option::SetBackButton()
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

void Option::ButtonSelector()
{
	if (input.Is_Key_Pressed(GLFW_KEY_DOWN) && pointer <= static_cast<int>(BUTTON::BACK))
	{
		pointer++;
		if(pointer == static_cast<int>(BUTTON::FULLSCREEN))
		{
			ObjectHover(full_screen_button, full_screen_button_hover);
		}
		if (pointer == static_cast<int>(BUTTON::SFX))
		{
			ObjectHover(volume_box[0], volume_box_hover[0]);
			ObjectHover(full_screen_button_hover, full_screen_button);
		}
		else if (pointer == static_cast<int>(BUTTON::MUSIC))
		{
			ObjectHover(volume_box[1], volume_box_hover[1]);
			ObjectHover(volume_box_hover[0], volume_box[0]);
		}
		else if (pointer == static_cast<int>(BUTTON::BACK))
		{
			ObjectHover(back_button, back_button_hover);
			ObjectHover(volume_box_hover[1], volume_box[1]);
		}

		if (pointer > 3)
		{
			pointer = 3;
		}

		button_timer = 0;
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_UP) && pointer >= static_cast<int>(BUTTON::SFX))
	{
		pointer--;

		if(pointer == static_cast<int>(BUTTON::FULLSCREEN))
		{
			ObjectHover(full_screen_button, full_screen_button_hover);
			ObjectHover(volume_box_hover[0], volume_box[0]);
		}
		else if (pointer == static_cast<int>(BUTTON::SFX))
		{
			ObjectHover(volume_box[0], volume_box_hover[0]);
			ObjectHover(volume_box_hover[1], volume_box[1]);
		}
		else if (pointer == static_cast<int>(BUTTON::MUSIC))
		{
			ObjectHover(volume_box[1], volume_box_hover[1]);
			ObjectHover(back_button_hover, back_button);
		}
		else if (pointer == static_cast<int>(BUTTON::BACK))
		{
			ObjectHover(back_button, back_button_hover);
		}

		if (pointer < 0)
		{
			pointer = 0;
		}

		button_timer = 0;
	}
}

void Option::SetSoundVolume(float value, bool isBGM)
{
	float volume;

	if (isBGM == true)
	{
		volume = sound.GetSoundGroupVolume(true);
		sound.SetSoundGroupVolume(true, volume + value);
	}
	else if (isBGM == false)
	{
		volume = sound.GetSoundGroupVolume(false);
		sound.SetSoundGroupVolume(false, volume + value);
	}
}