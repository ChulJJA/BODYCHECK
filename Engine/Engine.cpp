/*
 * Author		:Sangmin Kim
 * File			:Engine.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Engine
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Engine.hpp"
#include "Application.hpp"
#include "ObjectManager.h"
#include "Input.h"
#include "Graphic.h"
#include "StateManager.h"
#include "MainMenu.h"
#include "Tutorial.hpp"
#include "Level1.h"
#include "Message_Manager.h"
#include "Sound_Manager.h"
#include "Windows.h"
#include <thread>
#include "Logo.h"
#include "Credit.h"
#include "Option.h"
#include "Loading_Scene.h"
#include "Editor.h"
#include "PauseLevel.h"


Sound sound;


namespace
{
    
    Application* app_ = nullptr;
    ObjectManager* object_manager = nullptr;
    StateManager* state_manager = nullptr;
    Graphic* graphic = nullptr;
    Message_Manager* msg_manager = nullptr;
	Editor* editor = nullptr;
    Gamepad* gamepadManager = nullptr;
}

void Update_App(float dt)
{
    app_->Update(dt);
}
void Update_Graphic(float dt)
{
    graphic->Update(dt);
}
void Update_Obj(float dt)
{
    object_manager->Update(dt);
}
void Update_Msg(float dt)
{
    msg_manager->Update(dt);
}

void Engine::Init()
{
    sound.Initialize();

    app_ = Application::Get_Application();
	msg_manager = Message_Manager::Get_Message_Manager();
    object_manager = ObjectManager::GetObjectManager();
    state_manager = StateManager::GetStateManager();
    graphic = Graphic::GetGraphic();
	//editor = Editor::Get_Editor();
    gamepadManager = Gamepad::getGamepad();

    app_->Init();
    object_manager->Init();
    state_manager->Init();
    graphic->Init();
    msg_manager->Init();
	//editor->Init();

    state_manager->AddState("Logo", new Logo);
    state_manager->AddState("Menu", new MainMenu);
    state_manager->AddState("Level1", new Level1);
    state_manager->AddState("Tutorial", new Tutorial);
    state_manager->AddState("Option", new Option);
    state_manager->AddState("Credit", new Credit);
	state_manager->AddState("Loading", new Loading_Scene);
    state_manager->AddState("PauseLevel", new PauseLevel);
    StateManager::GetStateManager()->level_state = state_manager->Get_States().find("Level1")->second.get();
    game_timer.Reset();
}

void Engine::Update()
{
    gamepadManager->Update();
    m_dt = game_timer.GetElapsedSeconds();
    game_timer.Reset();

	//if (input.Is_Key_Pressed(GLFW_KEY_V))
	//{
	//	editor->Update(m_dt);
	//	if (showing_editor == false)
	//	{
	//		editor->Set_Visible(true);
	//	}
	//	showing_editor = true;
	//}
	//else if (input.Is_Key_Released(GLFW_KEY_V))
	//{
	//	showing_editor = false;
	//	editor->Set_Visible(false);
	//}
	
    app_->Update(m_dt);
    graphic->Update(m_dt);
    object_manager->Update(m_dt);
	state_manager->Update(m_dt);
	msg_manager->Update(m_dt);
    sound.Update(m_dt);
	
    /*if (input.Is_Key_Triggered(GLFW_KEY_1))
    {
        state_manager->GetCurrentState()->is_pause = !state_manager->GetCurrentState()->is_pause;
    }
    if (input.Is_Key_Triggered(GLFW_KEY_N))
    {
        Clear();
        StateManager::GetStateManager()->Get_States().at("Level1").get()->Load();
    }*/

    gamepadManager->Refresh();
}

void Engine::Delete()
{
    object_manager->Delete();
    gamepadManager->Delete();
}

void Engine::Reset()
{
    if (Graphic::GetGraphic()->get_need_update_sprite())
    {
        Graphic::GetGraphic()->get_need_update_sprite() = false;
    }
}

void Engine::Clear()
{
    object_manager->Clear();
}