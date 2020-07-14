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

extern int life;

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

	SetBackground();
	SetMusicVolumeBox();
	SetLifeButton();
	SetMusicIcon();
	SetMuteButton();
	SetFullScreenButton();
	SetBackButton();
	SetFullBox();
	if (life != 3)
	{
		if (life < 3)
		{
			std::cout << "ck1" << std::endl;
			int diff = 3 - life;
			music_icon[2]->GetTransform().GetTranslation_Reference().x -= (diff * 420);
		}
		else
		{
			std::cout << "ck2" << std::endl;
			int diff = life - 3;
			music_icon[2]->GetTransform().GetTranslation_Reference().x += (diff * 420);
		}
	}
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
	music_icon[2]->SetDeadCondition(true);
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
	lifeButton->SetDeadCondition(true);
	lifeButtonHover->SetDeadCondition(true);
	lifeBox->SetDeadCondition(true);
	life_count->SetDeadCondition(true);
	fullBox->SetDeadCondition(true);
	fullBoxCheck->SetDeadCondition(true);
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
	const float initial_sfx_icon = sfx_volume * 4 * 420;
	const float initial_bgm_icon = bgm_volume * 4 * 420;

	music_icon[0] = new Object();
	music_icon[0]->AddComponent(new Sprite(music_icon[0], "../Sprite/icon.png", { -550 + initial_bgm_icon, -260 }, false));
	music_icon[0]->GetTransform().SetScale({ 10, 10 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[0]);

	music_icon[1] = new Object();
	music_icon[1]->AddComponent(new Sprite(music_icon[1], "../Sprite/icon.png", { -550 + initial_sfx_icon, -640 }, false));
	music_icon[1]->GetTransform().SetScale({ 10, 10 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[1]);

	music_icon[2] = new Object();
	music_icon[2]->AddComponent(new Sprite(music_icon[2], "../Sprite/icon.png", { 320, -1000 }, false));
	music_icon[2]->GetTransform().SetScale({ 10, 10 });
	ObjectManager::GetObjectManager()->AddObject(music_icon[2]);
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
	volume_box[1]->AddComponent(new Sprite(volume_box[1], "../Sprite/VolumeBox.png", { 20, -360 }, false));
	volume_box[1]->GetTransform().SetScale({ 20, 15 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[1]);


	volume_box_hover[1] = new Object();
	volume_box_hover[1]->AddComponent(new Sprite(volume_box_hover[1], "../Sprite/buttonUIhover_SFX.png", { 0, -130 }, false));
	volume_box_hover[1]->GetTransform().SetScale({ 5, 5 });
	volume_box_hover[1]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(volume_box_hover[1]);

	volume_box[2] = new Object();
	volume_box[2]->AddComponent(new Sprite(volume_box[2], "../Sprite/buttonUI_VOL.png", { 0, 250 }, false));
	volume_box[2]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[2]);

	volume_box[3] = new Object();
	volume_box[3]->AddComponent(new Sprite(volume_box[3], "../Sprite/buttonUI_SFX.png", { 0, -130 }, false));
	volume_box[3]->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(volume_box[3]);
}

void Option::ButtonBehavior()
{
	float volume;
	State* lev_state;

	if (pointer == static_cast<int>(BUTTON::FULLSCREEN))
	{
		if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)))
		{
			sound.Play(SOUND::Selected);
			app->Toggle_Fullscreen();
			if(app->IsFullScreen())
			{
				ObjectHover(fullBox, fullBoxCheck);
			}
			else if(!app->IsFullScreen())
			{
				ObjectHover(fullBoxCheck, fullBox);
			}
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
			music_icon[0]->SetTranslation({ icon_translation.x + 420, icon_translation.y });
			sound.Play(SOUND::SoundControl);

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
			sound.Play(SOUND::SoundControl);

			SetSoundVolume(-0.25, true);
			music_icon[0]->SetTranslation({ icon_translation.x - 420, icon_translation.y });

			volume_timer = 0;
		}
	}
	else if (pointer == static_cast<int>(BUTTON::MUSIC))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
		{
			std::cout << life << std::endl;
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
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
		{
			std::cout << life << std::endl;
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
	else if (pointer == static_cast<int>(BUTTON::LIFE))
	{
		if (input.Is_Key_Pressed(GLFW_KEY_RIGHT))
		{
			vector2 icon_translation = music_icon[2]->GetTransform().GetTranslation();

			if (icon_translation.x < 1100)
			{
				life++;

				switch (life)
				{
				case 1:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_1));
					break;
				case 2:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_2));
					break;
				case 3:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_3));
					break;
				case 4:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_4));
					break;
				case 5:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_5));
					break;
				}

				sound.Play(SOUND::SoundControl);
				music_icon[2]->SetTranslation({ icon_translation.x + 420, icon_translation.y });
				volume_timer = 0;
			}
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_LEFT))
		{
			vector2 icon_translation = music_icon[2]->GetTransform().GetTranslation();
			if (icon_translation.x > -520)
			{
				life--;

				switch (life)
				{
				
				case 1:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_1));
					break;
				case 2:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_2));
					break;
				case 3:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_3));
					break;
				case 4:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_4));
					break;
				case 5:
					life_count->Change_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_5));
					break;
				}

				sound.Play(SOUND::SoundControl);
				music_icon[2]->SetTranslation({ icon_translation.x - 420, icon_translation.y });
				volume_timer = 0;
			}
		}
	}
	else if (pointer == static_cast<int>(BUTTON::BACK) && state_manager->GetPrevState()->GetStateInfo() == GameState::Menu)
	{
		if (input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER))
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
		if (input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER))
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
	mute_button[0]->AddComponent(new Sprite(mute_button[0], "../Sprite/Mute.png", { 960, 50 }, false));
	mute_button[0]->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button[0]);
	unmute_button[0] = new Object();
	unmute_button[0]->AddComponent(new Sprite(unmute_button[0], "../Sprite/Unmute.png", { 960, 50 }, false));
	unmute_button[0]->GetTransform().SetScale({ 1, 1 });
	unmute_button[0]->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(unmute_button[0]);

	mute_button[1] = new Object();
	mute_button[1]->AddComponent(new Sprite(mute_button[1], "../Sprite/Mute.png", { 960, -330 }, false));
	mute_button[1]->GetTransform().SetScale({ 1, 1 });
	ObjectManager::GetObjectManager()->AddObject(mute_button[1]);
	unmute_button[1] = new Object();
	unmute_button[1]->AddComponent(new Sprite(unmute_button[1], "../Sprite/Unmute.png", { 960, -330 }, false));
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
	back_button->AddComponent(new Sprite(back_button, "../Sprite/BackButton.png", { 0, -880 }, false));
	back_button->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(back_button);

	back_button_hover = new Object();
	back_button_hover->AddComponent(new Sprite(back_button_hover, "../Sprite/BackButtonHover.png", { 0, -880 }, false));
	back_button_hover->GetTransform().SetScale({ 5, 5 });
	back_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(back_button_hover);
}

void Option::ButtonSelector()
{


	if (input.Is_Key_Pressed(GLFW_KEY_DOWN) && pointer <= static_cast<int>(BUTTON::BACK))
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
			pointer1->SetTranslation({ -320,-140 });
			pointer2->SetTranslation({ 320,-140 });
		}
		else if (pointer == static_cast<int>(BUTTON::LIFE))
		{
			sound.Play(SOUND::Click);
			ObjectHover(lifeButton, lifeButtonHover);
			ObjectHover(volume_box_hover[1], volume_box[3]);
			pointer1->SetTranslation({ -320,-500 });
			pointer2->SetTranslation({ 320,-500 });
		}
		else if (pointer == static_cast<int>(BUTTON::BACK))
		{
			sound.Play(SOUND::Click);
			ObjectHover(back_button, back_button_hover);
			ObjectHover(lifeButtonHover, lifeButton);
			pointer1->SetTranslation({ -320,-880 });
			pointer2->SetTranslation({ 320,-880 });
		}

		if (pointer > 4)
		{
			pointer = 4;
		}

		button_timer = 0;
	}
	else if (input.Is_Key_Pressed(GLFW_KEY_UP) && pointer >= static_cast<int>(BUTTON::SFX))
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
			ObjectHover(lifeButtonHover, lifeButton);
			pointer1->SetTranslation({ -320,-140 });
			pointer2->SetTranslation({ 320,-140 });
		}
		else if (pointer == static_cast<int>(BUTTON::LIFE))
		{
			sound.Play(SOUND::Click);
			ObjectHover(lifeButton, lifeButtonHover);
			ObjectHover(back_button_hover, back_button);
			pointer1->SetTranslation({ -320,-500 });
			pointer2->SetTranslation({ 320,-500 });
		}
		else if (pointer == static_cast<int>(BUTTON::BACK))
		{
			sound.Play(SOUND::Click);
			ObjectHover(back_button, back_button_hover);
			pointer1->SetTranslation({ -320,-880 });
			pointer2->SetTranslation({ 320,-880 });
		}

		if (pointer < 0)
		{
			pointer = 0;
		}

		button_timer = 0;
	}
}

void Option::SetLifeButton()
{
	lifeButton = new Object();
	lifeButton->AddComponent(new Sprite(lifeButton, "../Sprite/LivesButton.png", { 0, -500 }, false));
	lifeButton->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(lifeButton);

	lifeButtonHover = new Object();
	lifeButtonHover->AddComponent(new Sprite(lifeButtonHover, "../Sprite/LivesButtonHover.png", { 0, -500 }, false));
	lifeButtonHover->GetTransform().SetScale({ 5, 5 });
	lifeButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(lifeButtonHover);

	life_count = new Object();
	life_count->AddComponent(new Sprite(life_count, "../Sprite/UI/1.png", { 950, -680 }, false, Sprite_Type::Num_1));
	life_count->AddComponent(new Sprite(life_count, "../Sprite/UI/2.png", { 950, -680 }, false, Sprite_Type::Num_2));
	life_count->AddComponent(new Sprite(life_count, "../Sprite/UI/3.png", { 950, -680 }, false, Sprite_Type::Num_3));
	life_count->AddComponent(new Sprite(life_count, "../Sprite/UI/4.png", { 950, -680 }, false, Sprite_Type::Num_4));
	life_count->AddComponent(new Sprite(life_count, "../Sprite/UI/5.png", { 950, -680 }, false, Sprite_Type::Num_5));

	switch (life)
	{

	case 1:
		life_count->Set_Current_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_1));
		break;
	case 2:
		life_count->Set_Current_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_2));
		break;
	case 3:
		life_count->Set_Current_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_3));
		break;
	case 4:
		life_count->Set_Current_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_4));
		break;
	case 5:
		life_count->Set_Current_Sprite(life_count->Find_Sprite_By_Type(Sprite_Type::Num_5));
		break;
	}


	life_count->GetTransform().SetScale({ 2, 2 });
	ObjectManager::GetObjectManager()->AddObject(life_count);


	lifeBox = new Object();
	lifeBox->AddComponent(new Sprite(lifeBox, "../Sprite/VolumeBox.png", { 20, -720 }, false));
	lifeBox->GetTransform().SetScale({ 20, 15 });
	ObjectManager::GetObjectManager()->AddObject(lifeBox);
}

void Option::SetFullBox()
{
	fullBox = new Object();
	fullBox->AddComponent(new Sprite(fullBox, "../Sprite/FullBox.png", { 550, 500 }, false));
	fullBox->GetTransform().SetScale({ 2, 2 });
	if(app->IsFullScreen())
	{
		fullBox->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	}
	ObjectManager::GetObjectManager()->AddObject(fullBox);

	fullBoxCheck = new Object();
	fullBoxCheck->AddComponent(new Sprite(fullBoxCheck, "../Sprite/FullBoxCheck.png", { 550, 500 }, false));
	fullBoxCheck->GetTransform().SetScale({ 2, 2 });
	if (!app->IsFullScreen())
	{
		fullBoxCheck->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	}
	ObjectManager::GetObjectManager()->AddObject(fullBoxCheck);
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
