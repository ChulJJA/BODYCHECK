#include "PauseLevel.h"
#include "Application.hpp"
#include "StateManager.h"
#include "Graphic.h"
#include "UsefulTools.hpp"
#include <Input.h>
#include "Level1.h"
#include "Sound_Manager.h"
#include "Engine.hpp"

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

	SetRestartButton();
	SetMainMenuButton();
	SetOptionButton();
	SetQuitButton();
	SetBackButton();
	
	pointer = 0;
	buttonTimer = 0;
}

void PauseLevel::Update(float dt)
{
	buttonTimer++;
	
	if(buttonTimer >= 10)
	{
		ButtonSelector();
	}
	ButtonBehavior();
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
}

void PauseLevel::SetRestartButton()
{
	restartButton = new Object();
	restartButton->AddComponent(new Sprite(restartButton, "../Sprite/RestartButton.png", { 0, 600 }, false));
	restartButton->GetTransform().SetScale({ 5, 5 });
	restartButton->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(restartButton);
	restartButtonHover = new Object();
	restartButtonHover->AddComponent(new Sprite(restartButtonHover, "../Sprite/RestartButtonHover.png", { 0, 600 }, false));
	restartButtonHover->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(restartButtonHover);
}

void PauseLevel::SetMainMenuButton()
{
	mainMenuButton = new Object();
	mainMenuButton->AddComponent(new Sprite(mainMenuButton, "../Sprite/MainMenuButton.png", { 0, 300 }, false));
	mainMenuButton->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(mainMenuButton);
	mainMenuButtonHover = new Object();
	mainMenuButtonHover->AddComponent(new Sprite(mainMenuButtonHover, "../Sprite/MainMenuButtonHover.png", { 0, 300 }, false));
	mainMenuButtonHover->GetTransform().SetScale({ 5, 5 });
	mainMenuButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(mainMenuButtonHover);
}

void PauseLevel::SetOptionButton()
{
	optionButton = new Object();
	optionButton->AddComponent(new Sprite(optionButton, "../Sprite/MusicButton.png", { 0, 0 }, false));
	optionButton->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(optionButton);
	optionButtonHover = new Object();
	optionButtonHover->AddComponent(new Sprite(optionButtonHover, "../Sprite/MusicButtonHover.png", { 0, 0 }, false));
	optionButtonHover->GetTransform().SetScale({ 5, 5 });
	optionButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(optionButtonHover);
}

void PauseLevel::SetQuitButton()
{
	quitButton = new Object();
	quitButton->AddComponent(new Sprite(quitButton, "../Sprite/QuitButton.png", { 0, -300 }, false));
	quitButton->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(quitButton);
	quitButtonHover = new Object();
	quitButtonHover->AddComponent(new Sprite(quitButtonHover, "../Sprite/QuitButtonHover.png", { 0, -300 }, false));
	quitButtonHover->GetTransform().SetScale({ 5, 5 });
	quitButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(quitButtonHover);
}

void PauseLevel::SetBackButton()
{
	backButton = new Object();
	backButton->AddComponent(new Sprite(backButton, "../Sprite/BackButton.png", { 0, -600 }, false));
	backButton->GetTransform().SetScale({ 5, 5 });
	ObjectManager::GetObjectManager()->AddObject(backButton);
	backButtonHover = new Object();
	backButtonHover->AddComponent(new Sprite(backButtonHover, "../Sprite/BackButtonHover.png", { 0, -600 }, false));
	backButtonHover->GetTransform().SetScale({ 5, 5 });
	backButtonHover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1, 1,1, 0 };
	ObjectManager::GetObjectManager()->AddObject(backButtonHover);
}

void PauseLevel::ButtonSelector()
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

void PauseLevel::ButtonBehavior()
{
	if(pointer == static_cast<int>(BUTTON::RESTART) && input.Is_Key_Pressed(GLFW_KEY_SPACE))
	{

	}
	else if(pointer == static_cast<int>(BUTTON::MAINMENU) && input.Is_Key_Pressed(GLFW_KEY_SPACE))
	{
		is_next = true;
		next_level = "Menu";
		sound.Stop(SOUND::BGM2);
		sound.Play(SOUND::BGM);
		Clear();
	}
	else if(pointer == static_cast<int>(BUTTON::OPTION) && input.Is_Key_Pressed(GLFW_KEY_SPACE))
	{
		is_next = true;
		next_level = "Option";
		Clear();
	}
	else if(pointer == static_cast<int>(BUTTON::QUIT) && input.Is_Key_Pressed(GLFW_KEY_SPACE))
	{
		exit(0);
	}
	else if(pointer == static_cast<int>(BUTTON::BACK) && input.Is_Key_Pressed(GLFW_KEY_SPACE))
	{
		state_manager->BackToLevel();
		Clear();
	}
}