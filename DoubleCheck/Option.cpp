/*
 * Author		:Chulseung Lee
 * File			:Option.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Option
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
#include "Gamepad.hpp"
namespace
{
	ObjectManager* object_manager = nullptr;
	StateManager* state_manager = nullptr;
	Gamepad* gamepadManager = nullptr;
	Application* app = Application::Get_Application();
}

void Option::Load()
{
	state_manager = StateManager::GetStateManager();
	object_manager = ObjectManager::GetObjectManager();
	gamepadManager = Gamepad::getGamepad();
	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
	Graphic::GetGraphic()->get_need_update_sprite() = true;

	volume_timer = 0;
	button_timer = 0;
	pointer = 0;

	SetBackground();
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
	volume_box[2]->SetDeadCondition(true);
	volume_box[3]->SetDeadCondition(true);
	background->SetDeadCondition(true);
	pointer1->SetDeadCondition(true);
	pointer2->SetDeadCondition(true);
}

void Option::SetBackground()
{
	background = new Object();
	background->AddComponent(new Sprite(background, "../Sprite/OptionBackground.png", { 100.f,100.f }, false));
	background->GetTransform().SetScale({ 40.f, 22.5f });
	ObjectManager::GetObjectManager()->AddObject(background);
}

void Option::SetMusicIcon()
{
	const float sfx_volume = sound.GetSoundGroupVolume(false);
	const float bgm_volume = sound.GetSoundGroupVolume(true);
	const float initial_sfx_icon = sfx_volume * 4 * 680;
	const float initial_bgm_icon = bgm_volume * 4 * 680;

	music_icon[0] = new Object();
	music_icon[0]->AddComponent(new Sprite(music_icon[0], "../Sprite/icon.png", { -1055 + initial_bgm_icon, -260 }, false));
	music_icon[0]->GetTransform().SetScale({ 10, 10 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[0]);

	music_icon[1] = new Object();
	music_icon[1]->AddComponent(new Sprite(music_icon[1], "../Sprite/icon.png", { -1055 + initial_sfx_icon, -760 }, false));
	music_icon[1]->GetTransform().SetScale({ 10, 10 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[1]);
}

void Option::SetMusicVolumeBox()
{
	volume_box[0] = new Object();
	volume_box[0]->AddComponent(new Sprite(volume_box[0], "../Sprite/VolumeBox.png", { 20, 20 }, false));
	volume_box[0]->GetTransform().SetScale({ 20, 15 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[0]);

	volume_box_hover[0] = new Object();
	volume_box_hover[0]->AddComponent(new Sprite(volume_box_hover[0], "../Sprite/buttonUIhover_VOL.png", { 0, 250 }, false));
	volume_box_hover[0]->GetTransform().SetScale({ 5, 5 });
	volume_box_hover[0]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(volume_box_hover[0]);

	volume_box[1] = new Object();
	volume_box[1]->AddComponent(new Sprite(volume_box[1], "../Sprite/VolumeBox.png", { 20, -480 }, false));
	volume_box[1]->GetTransform().SetScale({ 20, 15 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[1]);


	volume_box_hover[1] = new Object();
	volume_box_hover[1]->AddComponent(new Sprite(volume_box_hover[1], "../Sprite/buttonUIhover_SFX.png", { 0, -200 }, false));
	volume_box_hover[1]->GetTransform().SetScale({ 5, 5 });
	volume_box_hover[1]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(volume_box_hover[1]);

	volume_box[2] = new Object();
	volume_box[2]->AddComponent(new Sprite(volume_box[2], "../Sprite/buttonUI_VOL.png", { 0, 250 }, false));
	volume_box[2]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[2]);

	volume_box[3] = new Object();
	volume_box[3]->AddComponent(new Sprite(volume_box[3], "../Sprite/buttonUI_SFX.png", { 0, -200 }, false));
	volume_box[3]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[3]);
}

void Option::ButtonBehavior()
{
	float volume;
	State* lev_state;
	float LeftThumbStateX = gamepadManager->LeftStick_X();
	bool LeftStickInDeadZone = gamepadManager->LStick_InDeadzone();

	if (pointer == static_cast<int>(BUTTON::FULLSCREEN))
	{
		if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)))
		{
			sound.Play(SOUND::Selected);
			app->Toggle_Fullscreen();
			volume_timer = 0;
		}
	}
	else if (pointer == static_cast<int>(BUTTON::SFX))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT) || (LeftStickInDeadZone == false && LeftThumbStateX > 0.5f))
		{
			const vector2 icon_translation = music_icon[0]->GetTransform().GetTranslation();
			volume = sound.GetSoundGroupVolume(true);

			if (volume >= 1)
			{
				return;
			}
			SetSoundVolume(0.25, true);
			music_icon[0]->SetTranslation({ icon_translation.x + 420, icon_translation.y });
			sound.Play(SOUND::SoundControl);

			volume_timer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT) || (LeftStickInDeadZone == false && LeftThumbStateX < -0.5f))
		{
			vector2 icon_translation = music_icon[0]->GetTransform().GetTranslation();
			volume = sound.GetSoundGroupVolume(true);

			if (volume <= 0)
			{
				return;
			}
			sound.Play(SOUND::SoundControl);

			SetSoundVolume(-0.25, true);
			music_icon[0]->SetTranslation({ icon_translation.x - 420, icon_translation.y });

			volume_timer = 0;
		}
	}
	else if (pointer == static_cast<int>(BUTTON::MUSIC))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT) || (LeftStickInDeadZone == false && LeftThumbStateX > 0.5f))
		{
			vector2 icon_translation = music_icon[1]->GetTransform().GetTranslation();
			volume = sound.GetSoundGroupVolume(false);

			if (volume >= 1)
			{
				return;
			}
			sound.Play(SOUND::SoundControl);

			SetSoundVolume(0.25, false);
			music_icon[1]->SetTranslation({ icon_translation.x + 420, icon_translation.y });

			volume_timer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT) || (LeftStickInDeadZone == false && LeftThumbStateX < -0.5f))
		{
			vector2 icon_translation = music_icon[1]->GetTransform().GetTranslation();
			volume = sound.GetSoundGroupVolume(false);

			if (volume <= 0)
			{
				return;
			}
			sound.Play(SOUND::SoundControl);

			SetSoundVolume(-0.25, false);
			music_icon[1]->SetTranslation({ icon_translation.x - 420, icon_translation.y });

			volume_timer = 0;
		}
	}
	else if (pointer == static_cast<int>(BUTTON::BACK) && state_manager->GetPrevState()->GetStateInfo() == GameState::Menu)
	{
		if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) || gamepadManager->GetButtonDown(xButtons.A))
		{
			pointer = static_cast<int>(BUTTON::MUSIC);
			sound.Play(SOUND::Selected);
			is_next = true;
			next_level = "Menu";
			Clear();
		}
	}
	else if (pointer == static_cast<int>(BUTTON::BACK) && state_manager->GetPrevState()->GetStateInfo() == GameState::PauseLevel)
	{
		if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) || gamepadManager->GetButtonDown(xButtons.A))
		{
			sound.Play(SOUND::Selected);
			is_next = true;
			next_level = "PauseLevel";
			Clear();
		}
	}
}

void Option::SetMuteButton()
{
	mute_button[0] = new Object();
	mute_button[0]->AddComponent(new Sprite(mute_button[0], "../Sprite/Mute.png", { 1000, 50 }, false));
	mute_button[0]->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button[0]);
	unmute_button[0] = new Object();
	unmute_button[0]->AddComponent(new Sprite(unmute_button[0], "../Sprite/Unmute.png", { 1000, 50 }, false));
	unmute_button[0]->GetTransform().SetScale({ 1, 1 });
	unmute_button[0]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(unmute_button[0]);

	mute_button[1] = new Object();
	mute_button[1]->AddComponent(new Sprite(mute_button[1], "../Sprite/Mute.png", { 1000, -450 }, false));
	mute_button[1]->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button[1]);
	unmute_button[1] = new Object();
	unmute_button[1]->AddComponent(new Sprite(unmute_button[1], "../Sprite/Unmute.png", { 1000, -450 }, false));
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
	full_screen_button->AddComponent(new Sprite(full_screen_button, "../Sprite/FullScreenButton.png", { 0, 500 }, false));
	full_screen_button->GetTransform().SetScale({ 5, 5 });
	full_screen_button->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(full_screen_button);

	full_screen_button_hover = new Object();
	full_screen_button_hover->AddComponent(new Sprite(full_screen_button_hover, "../Sprite/FullScreenButtonHover.png", { 0, 500 }, false));
	full_screen_button_hover->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(full_screen_button_hover);

	pointer1 = new Object();
	pointer1->Set_Name("pointer1");
	pointer1->Set_Tag("pointer");
	pointer1->AddComponent(new Sprite(pointer1, "../Sprite/Player/State/pen_purple_dance.png", true, 15, 7, { -320,500 }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Dance), "dance", true);
	pointer1->GetTransform().SetScale({ 2, 2 });
	ObjectManager::GetObjectManager()->AddObject(pointer1);

	pointer2 = new Object();
	pointer2->Set_Name("pointer2");
	pointer2->Set_Tag("pointer");
	pointer2->AddComponent(new Sprite(pointer2, "../Sprite/Player/State/pen_purple_dance.png", true, 15, 7, { 320,500 }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Dance), "dance", true);
	pointer2->GetTransform().SetScale({ 2, 2 });
	ObjectManager::GetObjectManager()->AddObject(pointer2);
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
	float LeftThumbStateY = gamepadManager->LeftStick_Y();
	bool LeftStickInDeadZone = gamepadManager->LStick_InDeadzone();

	if ((input.Is_Key_Pressed(GLFW_KEY_DOWN) || (LeftStickInDeadZone == false && LeftThumbStateY < -0.5f)) && pointer <= static_cast<int>(BUTTON::BACK))
	{
		pointer++;
		if (pointer == static_cast<int>(BUTTON::FULLSCREEN))
		{
			sound.Play(SOUND::Click);
			ObjectHover(full_screen_button, full_screen_button_hover);
			pointer1->SetTranslation({ -320,500 });
			pointer2->SetTranslation({ 320,500 });
		}
		if (pointer == static_cast<int>(BUTTON::SFX))
		{
			sound.Play(SOUND::Click);
			ObjectHover(volume_box[2], volume_box_hover[0]);
			ObjectHover(full_screen_button_hover, full_screen_button);
			pointer1->SetTranslation({ -320,250 });
			pointer2->SetTranslation({ 320,250 });
		}
		else if (pointer == static_cast<int>(BUTTON::MUSIC))
		{
			sound.Play(SOUND::Click);
			ObjectHover(volume_box[3], volume_box_hover[1]);
			ObjectHover(volume_box_hover[0], volume_box[2]);
			pointer1->SetTranslation({ -320,-200 });
			pointer2->SetTranslation({ 320,-200 });
		}
		else if (pointer == static_cast<int>(BUTTON::BACK))
		{
			sound.Play(SOUND::Click);
			ObjectHover(back_button, back_button_hover);
			ObjectHover(volume_box_hover[1], volume_box[3]);
			pointer1->SetTranslation({ -320,-700 });
			pointer2->SetTranslation({ 320,-700 });
		}

		if (pointer > 3)
		{
			pointer = 3;
		}

		button_timer = 0;
	}
	else if ((input.Is_Key_Pressed(GLFW_KEY_UP) || (LeftStickInDeadZone == false && LeftThumbStateY > 0.5f)) && pointer >= static_cast<int>(BUTTON::SFX))
	{
		pointer--;

		if (pointer == static_cast<int>(BUTTON::FULLSCREEN))
		{
			sound.Play(SOUND::Click);
			ObjectHover(full_screen_button, full_screen_button_hover);
			ObjectHover(volume_box_hover[0], volume_box[2]);
			pointer1->SetTranslation({ -320,500 });
			pointer2->SetTranslation({ 320,500 });
		}
		else if (pointer == static_cast<int>(BUTTON::SFX))
		{
			sound.Play(SOUND::Click);
			ObjectHover(volume_box[2], volume_box_hover[0]);
			ObjectHover(volume_box_hover[1], volume_box[3]);
			pointer1->SetTranslation({ -320,250 });
			pointer2->SetTranslation({ 320,250 });
		}
		else if (pointer == static_cast<int>(BUTTON::MUSIC))
		{
			sound.Play(SOUND::Click);
			ObjectHover(volume_box[3], volume_box_hover[1]);
			ObjectHover(back_button_hover, back_button);
			pointer1->SetTranslation({ -320,-200 });
			pointer2->SetTranslation({ 320,-200 });
		}
		else if (pointer == static_cast<int>(BUTTON::BACK))
		{
			sound.Play(SOUND::Click);
			ObjectHover(back_button, back_button_hover);
			pointer1->SetTranslation({ -320,-700 });
			pointer2->SetTranslation({ 320,-700 });
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