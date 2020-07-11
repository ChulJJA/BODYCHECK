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
	background->AddComponent(new Sprite(background, "../Sprite/PauseBackground.png", { 95.f,100.f }, false));
	background->GetTransform().SetScale({ 40.f, 22.f });
	//background->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(background);
}

void PauseLevel::SetRestartButton()
{
	restartButton = new Object();
	restartButton->Set_Name("restartButton");
	restartButton->AddComponent(new Sprite(restartButton, "../Sprite/RestartButton.png", { 30, 400 }, false));
	restartButton->GetTransform().SetScale({ 15, 10 });
	restartButton->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(restartButton);
	restartButtonHover = new Object();
	restartButtonHover->Set_Name("restartButtonHover");
	restartButtonHover->AddComponent(new Sprite(restartButtonHover, "../Sprite/RestartButtonHover.png", { 30, 400 }, false));
	restartButtonHover->GetTransform().SetScale({ 15, 10 });
	ObjectManager::GetObjectManager()->AddObject(restartButtonHover);
}

void PauseLevel::SetMainMenuButton()
{
	mainMenuButton = new Object();
	mainMenuButton->Set_Name("mainMenuButton");
	mainMenuButton->AddComponent(new Sprite(mainMenuButton, "../Sprite/MainMenuButton.png", { 20, 100 }, false));
	mainMenuButton->GetTransform().SetScale({ 15, 10 });
	ObjectManager::GetObjectManager()->AddObject(mainMenuButton);
	mainMenuButtonHover = new Object();
	mainMenuButtonHover->Set_Name("mainMenuButtonHover");
	mainMenuButtonHover->AddComponent(new Sprite(mainMenuButtonHover, "../Sprite/MainMenuButtonHover.png", { 20, 100 }, false));
	mainMenuButtonHover->GetTransform().SetScale({ 15, 10 });
	mainMenuButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(mainMenuButtonHover);
}

void PauseLevel::SetOptionButton()
{
	optionButton = new Object();
	optionButton->Set_Name("optionButton");
	optionButton->AddComponent(new Sprite(optionButton, "../Sprite/MusicButton.png", { -10, -200 }, false));
	optionButton->GetTransform().SetScale({ 15, 10 });
	ObjectManager::GetObjectManager()->AddObject(optionButton);
	optionButtonHover = new Object();
	optionButtonHover->Set_Name("optionButtonHover");
	optionButtonHover->AddComponent(new Sprite(optionButtonHover, "../Sprite/MusicButtonHover.png", { -10, -200 }, false));
	optionButtonHover->GetTransform().SetScale({ 15, 10 });
	optionButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(optionButtonHover);
}

void PauseLevel::SetQuitButton()
{
	quitButton = new Object();
	quitButton->Set_Name("quitButton");
	quitButton->AddComponent(new Sprite(quitButton, "../Sprite/QuitButton.png", { 60, -500 }, false));
	quitButton->GetTransform().SetScale({ 15, 10 });
	ObjectManager::GetObjectManager()->AddObject(quitButton);
	quitButtonHover = new Object();
	quitButtonHover->Set_Name("quitButtonHover");
	quitButtonHover->AddComponent(new Sprite(quitButtonHover, "../Sprite/QuitButtonHover.png", { 60, -500 }, false));
	quitButtonHover->GetTransform().SetScale({ 15, 10 });
	quitButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(quitButtonHover);
}

void PauseLevel::SetBackButton()
{
	backButton = new Object();
	backButton->Set_Name("backButton");
	backButton->AddComponent(new Sprite(backButton, "../Sprite/BackButton.png", { 80, -800 }, false));
	backButton->GetTransform().SetScale({ 15, 10 });
	ObjectManager::GetObjectManager()->AddObject(backButton);
	backButtonHover = new Object();
	backButtonHover->Set_Name("backButtonHover");
	backButtonHover->AddComponent(new Sprite(backButtonHover, "../Sprite/BackButtonHover.png", { 80, -800 }, false));
	backButtonHover->GetTransform().SetScale({ 15, 10 });
	backButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(backButtonHover);
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
					}
				}
				else if (input.Is_Key_Triggered(GLFW_KEY_LEFT))
				{
					if (r_u_sure_current_sprite == r_u_sure_no_sprite)
					{
						make_sure_dialogue->Change_Sprite(r_u_sure_yes_sprite);
					}
				}

				if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && r_u_sure_current_sprite == r_u_sure_yes_sprite)
				{
					r_u_sure_come = false;
					r_u_sure = true;
				}
				else if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && r_u_sure_current_sprite == r_u_sure_no_sprite)
				{
					r_u_sure_come = false;
					make_sure_dialogue->Set_Need_To_Update(false);
				}
			}
		}
	}
	else
	{
		if (input.Is_Key_Pressed(GLFW_KEY_DOWN) && pointer <= static_cast<int>(BUTTON::BACK))
		{
			pointer++;
			if (pointer == static_cast<int>(BUTTON::RESTART))
			{
				sound.Play(SOUND::Click);
				ObjectHover(restartButton, restartButtonHover);
			}
			if (pointer == static_cast<int>(BUTTON::MAINMENU))
			{
				sound.Play(SOUND::Click);
				ObjectHover(mainMenuButton, mainMenuButtonHover);
				ObjectHover(restartButtonHover, restartButton);
			}
			else if (pointer == static_cast<int>(BUTTON::OPTION))
			{
				sound.Play(SOUND::Click);
				ObjectHover(optionButton, optionButtonHover);
				ObjectHover(mainMenuButtonHover, mainMenuButton);
			}
			else if (pointer == static_cast<int>(BUTTON::QUIT))
			{
				sound.Play(SOUND::Click);
				ObjectHover(quitButton, quitButtonHover);
				ObjectHover(optionButtonHover, optionButton);
			}
			else if (pointer == static_cast<int>(BUTTON::BACK))
			{
				sound.Play(SOUND::Click);
				ObjectHover(backButton, backButtonHover);
				ObjectHover(quitButtonHover, quitButton);
			}
			if (pointer > 4)
			{
				pointer = 4;
			}

			buttonTimer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_UP) && pointer >= static_cast<int>(BUTTON::RESTART))
		{
			pointer--;

			if (pointer == static_cast<int>(BUTTON::RESTART))
			{
				sound.Play(SOUND::Click);
				ObjectHover(restartButton, restartButtonHover);
				ObjectHover(mainMenuButtonHover, mainMenuButton);
			}
			else if (pointer == static_cast<int>(BUTTON::MAINMENU))
			{
				sound.Play(SOUND::Click);
				ObjectHover(mainMenuButton, mainMenuButtonHover);
				ObjectHover(optionButtonHover, optionButton);
			}
			else if (pointer == static_cast<int>(BUTTON::OPTION))
			{
				sound.Play(SOUND::Click);
				ObjectHover(optionButton, optionButtonHover);
				ObjectHover(quitButtonHover, quitButton);
			}
			else if (pointer == static_cast<int>(BUTTON::QUIT))
			{
				sound.Play(SOUND::Click);
				ObjectHover(quitButton, quitButtonHover);
				ObjectHover(backButtonHover, backButton);
			}
			else if (pointer == static_cast<int>(BUTTON::BACK))
			{
				sound.Play(SOUND::Click);
				ObjectHover(backButton, backButtonHover);
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
	const float currentBGM_Volume = sound.GetSoundGroupVolume(true);

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
			//Sleep(800);
			//exit(0);
		}
		else if (pointer == static_cast<int>(BUTTON::BACK) && (input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)))
		{
			sound.SetSoundGroupVolume(true, currentBGM_Volume * 3);
			sound.Play(SOUND::Selected);
			state_manager->BackToLevel();
			Clear();
		}
	}
	if (r_u_sure)
	{
		if (pointer == static_cast<int>(BUTTON::QUIT))
		{
			exit(0);
		}
		else if(pointer == static_cast<int>(BUTTON::RESTART))
		{
			FMOD_BOOL isPlaying;
			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &isPlaying);
			sound.SetSoundGroupVolume(true, currentBGM_Volume * 3);
			Sleep(800);
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
			Sleep(800);
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