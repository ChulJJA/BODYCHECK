/*
 * Author		:Chulseung Lee
 * File			:PauseLevel.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Pause Level
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "PauseLevel.h"
#include "Application.hpp"
#include "StateManager.h"
#include "Graphic.h"
#include "UsefulTools.hpp"
#include <Input.h>
#include "Level1.h"
#include "Sound_Manager.h"
#include "Engine.hpp"
#include "Message_Manager.h"
#include "Gamepad.hpp"
#include "Referee.h"
namespace
{
	ObjectManager* object_manager = nullptr;
	StateManager* state_manager = nullptr;
	Application* app = Application::Get_Application();
}

void PauseLevel::Load()
{
	state_manager = StateManager::GetStateManager();
	object_manager = ObjectManager::GetObjectManager();
	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
	Graphic::GetGraphic()->get_need_update_sprite() = true;

	r_u_sure = false;
	r_u_sure_come = false;
	prev_cheerup_mode = Referee::Get_Referee()->Get_Is_CheerUp_Mode();
	Referee::Get_Referee()->Set_CheerUp_Mode(false);
	Background();
	SetRestartButton();
	SetMainMenuButton();
	SetOptionButton();
	SetQuitButton();
	SetBackButton();

	make_sure_dialogue = new Object();
	make_sure_dialogue->AddComponent(new Sprite(make_sure_dialogue, "../Sprite/rusure_yes.png", { 0.f, 0.f }, false, Sprite_Type::R_U_SURE_YES), "rusureyes", false);
	make_sure_dialogue->AddComponent(new Sprite(make_sure_dialogue, "../Sprite/rusure_no.png", { 0.f, 0.f }, false, Sprite_Type::R_U_SURE_NO), "rusureno", false);
	make_sure_dialogue->GetTransform().SetScale({ 10.f, 6.f });
	make_sure_dialogue->Set_Need_To_Update(false);
	object_manager->AddObject(make_sure_dialogue);

	pointer = 0;
	buttonTimer = 0;

	FMOD_BOOL isPlayingBGM2;
	FMOD_BOOL isMatchBGMPlaying;
	FMOD_BOOL isPauseBGMPlaying;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &isPlayingBGM2);
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::MatchBGM)], &isMatchBGMPlaying);
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::PauseBGM)], &isPauseBGMPlaying);
	if (isPlayingBGM2 == true)
	{
		sound.Stop(SOUND::BGM2);
	}
	if (isMatchBGMPlaying)
	{
		sound.Stop(SOUND::MatchBGM);
	}
	if(!isPauseBGMPlaying)
	{
		sound.Play(SOUND::PauseBGM);
	}
}

void PauseLevel::Update(float dt)
{
	buttonTimer++;

	ButtonBehavior();

	if (buttonTimer >= 10)
	{
		ButtonSelector();
	}
}

void PauseLevel::Clear()
{
	restartButton->SetDeadCondition(true);
	restartButtonHover->SetDeadCondition(true);
	mainMenuButton->SetDeadCondition(true);
	mainMenuButtonHover->SetDeadCondition(true);
	optionButton->SetDeadCondition(true);
	optionButtonHover->SetDeadCondition(true);
	quitButton->SetDeadCondition(true);
	quitButtonHover->SetDeadCondition(true);
	backButton->SetDeadCondition(true);
	backButtonHover->SetDeadCondition(true);
	background->SetDeadCondition(true);
	pointer1->SetDeadCondition(true);
	pointer2->SetDeadCondition(true);

	if (pointer == static_cast<int>(BUTTON::RESTART) || pointer == static_cast<int>(BUTTON::MAINMENU))
	{
		Message_Manager::Get_Message_Manager()->Get_Messages().clear();
		ObjectManager::GetObjectManager()->Get_Objects().clear();
	}

}

void PauseLevel::Background()
{
	background = new Object();
	background->Set_Name("background");
	background->AddComponent(new Sprite(background, "../Sprite/PauseBackground.png", { 70.f,10.f }, false));
	background->GetTransform().SetScale({ 40.f, 22.f });
	//background->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(background);
}

void PauseLevel::SetRestartButton()
{
	restartButton = new Object();
	restartButton->Set_Name("restartButton");
	restartButton->AddComponent(new Sprite(restartButton, "../Sprite/RestartButton.png", { 20, 150}, false));
	restartButton->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(restartButton);
	restartButtonHover = new Object();
	restartButtonHover->Set_Name("restartButtonHover");
	restartButtonHover->AddComponent(new Sprite(restartButtonHover, "../Sprite/RestartButtonHover.png", { 20, 150}, false));
	restartButtonHover->GetTransform().SetScale({ 5, 5 });
	restartButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(restartButtonHover);

}

void PauseLevel::SetMainMenuButton()
{
	mainMenuButton = new Object();
	mainMenuButton->Set_Name("mainMenuButton");
	mainMenuButton->AddComponent(new Sprite(mainMenuButton, "../Sprite/MainMenuButton.png", { 20, -100 }, false));
	mainMenuButton->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(mainMenuButton);
	mainMenuButtonHover = new Object();
	mainMenuButtonHover->Set_Name("mainMenuButtonHover");
	mainMenuButtonHover->AddComponent(new Sprite(mainMenuButtonHover, "../Sprite/MainMenuButtonHover.png", { 20, -100 }, false));
	mainMenuButtonHover->GetTransform().SetScale({ 5, 5 });
	mainMenuButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(mainMenuButtonHover);
}

void PauseLevel::SetOptionButton()
{
	optionButton = new Object();
	optionButton->Set_Name("optionButton");
	optionButton->AddComponent(new Sprite(optionButton, "../Sprite/MusicButton_.png", { 20, -350 }, false));
	optionButton->GetTransform().SetScale({ 5, 5});
	ObjectManager::GetObjectManager()->AddObject(optionButton);
	optionButtonHover = new Object();
	optionButtonHover->Set_Name("optionButtonHover");
	optionButtonHover->AddComponent(new Sprite(optionButtonHover, "../Sprite/MusicButtonHover_.png", { 20, -350 }, false));
	optionButtonHover->GetTransform().SetScale({ 5, 5 });
	optionButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(optionButtonHover);
}

void PauseLevel::SetQuitButton()
{
	quitButton = new Object();
	quitButton->Set_Name("quitButton");
	quitButton->AddComponent(new Sprite(quitButton, "../Sprite/QuitButton.png", { 20, -600 }, false));
	quitButton->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(quitButton);
	quitButtonHover = new Object();
	quitButtonHover->Set_Name("quitButtonHover");
	quitButtonHover->AddComponent(new Sprite(quitButtonHover, "../Sprite/QuitButtonHover.png", { 20, -600 }, false));
	quitButtonHover->GetTransform().SetScale({ 5, 5 });
	quitButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(quitButtonHover);
}

void PauseLevel::SetBackButton()
{
	backButton = new Object();
	backButton->Set_Name("backButton");
	backButton->AddComponent(new Sprite(backButton, "../Sprite/BackButton.png", { 20, 400 }, false));
	backButton->GetTransform().SetScale({ 5, 5 });
	backButton->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };

	ObjectManager::GetObjectManager()->AddObject(backButton);
	backButtonHover = new Object();
	backButtonHover->Set_Name("backButtonHover");
	backButtonHover->AddComponent(new Sprite(backButtonHover, "../Sprite/BackButtonHover.png", { 20, 400 }, false));
	backButtonHover->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(backButtonHover);

	pointer1 = new Object();
	pointer1->Set_Name("pointer1");
	pointer1->Set_Tag("pointer");
	pointer1->AddComponent(new Sprite(pointer1, "../Sprite/Player/State/pen_purple_dance.png", true, 15, 7, { -290,400 }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Dance), "dance", true);
	pointer1->GetTransform().SetScale({ 2, 2 });
	ObjectManager::GetObjectManager()->AddObject(pointer1);

	pointer2 = new Object();
	pointer2->Set_Name("pointer2");
	pointer2->Set_Tag("pointer");
	pointer2->AddComponent(new Sprite(pointer2, "../Sprite/Player/State/pen_purple_dance.png", true, 15, 7, { 350,400 }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Dance), "dance", true);
	pointer2->GetTransform().SetScale({ 2, 2 });
	ObjectManager::GetObjectManager()->AddObject(pointer2);
}

void PauseLevel::ButtonSelector()
{
	
	if (r_u_sure_come)
	{
		Component* r_u_sure_current_sprite = make_sure_dialogue->Get_Current_Sprite();
		Component* r_u_sure_yes_sprite = make_sure_dialogue->Find_Sprite_By_Type(Sprite_Type::R_U_SURE_YES);
		Component* r_u_sure_no_sprite = make_sure_dialogue->Find_Sprite_By_Type(Sprite_Type::R_U_SURE_NO);

		if (make_sure_dialogue->Get_Need_To_Update() == false)
		{
			make_sure_dialogue->Change_Sprite(make_sure_dialogue->Find_Sprite_By_Type(Sprite_Type::R_U_SURE_YES));
			make_sure_dialogue->Set_Need_To_Update(true);
		}
		else
		{
			if (r_u_sure_current_sprite != nullptr && r_u_sure_yes_sprite != nullptr && r_u_sure_no_sprite != nullptr)
			{
				if (input.Is_Key_Triggered(GLFW_KEY_RIGHT))
				{
					if (r_u_sure_current_sprite == r_u_sure_yes_sprite)
					{
						make_sure_dialogue->Change_Sprite(r_u_sure_no_sprite);
						sound.Play(SOUND::Click);
					}
				}
				else if (input.Is_Key_Triggered(GLFW_KEY_LEFT))
				{
					if (r_u_sure_current_sprite == r_u_sure_no_sprite)
					{
						make_sure_dialogue->Change_Sprite(r_u_sure_yes_sprite);
						sound.Play(SOUND::Click);
					}
				}

				if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && r_u_sure_current_sprite == r_u_sure_yes_sprite)
				{
					sound.Play(SOUND::Selected);
					r_u_sure_come = false;
					r_u_sure = true;
					sound.Stop(SOUND::PauseBGM);
				}
				else if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && r_u_sure_current_sprite == r_u_sure_no_sprite)
				{
					sound.Play(SOUND::Selected);
					r_u_sure_come = false;
					make_sure_dialogue->Set_Need_To_Update(false);
				}
			}
		}
	}
	else
	{
		if (input.Is_Key_Pressed(GLFW_KEY_DOWN) && pointer <= static_cast<int>(BUTTON::QUIT))
		{
			pointer++;
			if (pointer == static_cast<int>(BUTTON::BACK))
			{
				sound.Play(SOUND::Click);
				ObjectHover(backButton, backButtonHover);
				pointer1->SetTranslation({ -290,400 });
				pointer2->SetTranslation({ 350,400 });
			}
			if (pointer == static_cast<int>(BUTTON::RESTART))
			{
				sound.Play(SOUND::Click);
				ObjectHover(restartButton, restartButtonHover);
				ObjectHover(backButtonHover, backButton);
				pointer1->SetTranslation({ -290,150 });
				pointer2->SetTranslation({ 350,150 });
			}
			else if (pointer == static_cast<int>(BUTTON::MAINMENU))
			{
				sound.Play(SOUND::Click);
				ObjectHover(mainMenuButton, mainMenuButtonHover);
				ObjectHover(restartButtonHover, restartButton);
				pointer1->SetTranslation({ -290,-100 });
				pointer2->SetTranslation({ 350,-100 });
			}
			else if (pointer == static_cast<int>(BUTTON::OPTION))
			{
				sound.Play(SOUND::Click);
				ObjectHover(optionButton, optionButtonHover);
				ObjectHover(mainMenuButtonHover, mainMenuButton);
				pointer1->SetTranslation({ -290,-350 });
				pointer2->SetTranslation({ 350,-350 });
			}
			else if (pointer == static_cast<int>(BUTTON::QUIT))
			{
				sound.Play(SOUND::Click);
				ObjectHover(quitButton, quitButtonHover);
				ObjectHover(optionButtonHover, optionButton);
				pointer1->SetTranslation({ -290,-600 });
				pointer2->SetTranslation({ 350,-600 });
			}
			if (pointer > 4)
			{
				pointer = 4;
			}

			buttonTimer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_UP) && pointer >= static_cast<int>(BUTTON::BACK))
		{
			pointer--;

			if (pointer == static_cast<int>(BUTTON::BACK))
			{
				sound.Play(SOUND::Click);
				ObjectHover(backButton, backButtonHover);
				ObjectHover(restartButtonHover, restartButton);
				pointer1->SetTranslation({ -290,400 });
				pointer2->SetTranslation({ 350,400 });
			}
			else if (pointer == static_cast<int>(BUTTON::RESTART))
			{
				sound.Play(SOUND::Click);
				ObjectHover(restartButton, restartButtonHover);
				ObjectHover(mainMenuButtonHover, mainMenuButton);
				pointer1->SetTranslation({ -290,150 });
				pointer2->SetTranslation({ 350,150 });
			}
			else if (pointer == static_cast<int>(BUTTON::MAINMENU))
			{
				sound.Play(SOUND::Click);
				ObjectHover(mainMenuButton, mainMenuButtonHover);
				ObjectHover(optionButtonHover, optionButton);
				pointer1->SetTranslation({ -290,-100 });
				pointer2->SetTranslation({ 350,-100 });
			}
			else if (pointer == static_cast<int>(BUTTON::OPTION))
			{
				sound.Play(SOUND::Click);
				ObjectHover(optionButton, optionButtonHover);
				ObjectHover(quitButtonHover, quitButton);
				pointer1->SetTranslation({ -290,-350 });
				pointer2->SetTranslation({ 350,-350 });
			}
			else if (pointer == static_cast<int>(BUTTON::QUIT))
			{
				sound.Play(SOUND::Click);
				ObjectHover(quitButton, quitButtonHover);
				pointer1->SetTranslation({ -290,-600 });
				pointer2->SetTranslation({ 350,-600 });
			}

			if (pointer < 0)
			{
				pointer = 0;
			}

			buttonTimer = 0;
		}
	}
}

void PauseLevel::ButtonBehavior()
{
	
	if (r_u_sure_come == false)
	{

		if (pointer == static_cast<int>(BUTTON::RESTART) && (input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)))
		{
			r_u_sure_come = true;
			sound.Play(SOUND::Selected);
		}
		else if (pointer == static_cast<int>(BUTTON::MAINMENU) && (input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)))
		{
			r_u_sure_come = true;
			sound.Play(SOUND::Selected);
		}
		else if (pointer == static_cast<int>(BUTTON::OPTION) && (input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)))
		{
			is_next = true;
			next_level = "Option";
			sound.Play(SOUND::Selected);
			Clear();
		}
		else if (pointer == static_cast<int>(BUTTON::QUIT) && (input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)))
		{
			sound.Play(SOUND::Selected);
			r_u_sure_come = true;
		}
		else if (pointer == static_cast<int>(BUTTON::BACK) && (input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)))
		{
			sound.Play(SOUND::Selected);
			FMOD_BOOL isBGM;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(sound.currentBGM)], &isBGM);
			if(!isBGM)
			{
				sound.Play(sound.currentBGM);
			}
			state_manager->BackToLevel();
			Referee::Get_Referee()->Set_CheerUp_Mode(prev_cheerup_mode);
			Clear();
		}
	}
	if (r_u_sure)
	{
		if (pointer == static_cast<int>(BUTTON::QUIT))
		{
			Sleep(1000);
			exit(0);
		}
		else if(pointer == static_cast<int>(BUTTON::RESTART))
		{
			FMOD_BOOL isPlaying;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &isPlaying);
			Sleep(1000);
			if (isPlaying == true)
			{
				sound.Stop(SOUND::BGM2);
				sound.UnLoad();
			}
			object_manager->Clear();
			is_next = true;
			next_level = "Level1";
			state_manager->level_state->is_pause = false;
			Clear();
		}
		else
		{
			is_next = true;
			next_level = "Menu";
			Sleep(1000);
			FMOD_BOOL isPlaying;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &isPlaying);
			if (isPlaying == true)
			{
				sound.Stop(SOUND::BGM2);
				sound.UnLoad();
			}
			Clear();
		}
	}
}