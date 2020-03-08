/*
 * Author		:Sangmin Kim
 * File			:Engine.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:The basic engine initiailze & update, managers initialize & update is implemented in here
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
#include "TestLevel.h"
#include "SoundOption.h"
#include "Loading_Scene.h"
#include "Testing_Level.h"

Sound sound;

namespace
{
    Application* app_ = nullptr;
    ObjectManager* object_manager = nullptr;
    StateManager* state_manager = nullptr;
    Graphic* graphic = nullptr;
    Message_Manager* msg_manager = nullptr;
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
    sound.Play(SOUND::TeamDoubleCheck);
    sound.Play(SOUND::BGM);

    app_ = Application::Get_Application();
    object_manager = ObjectManager::GetObjectManager();
    state_manager = StateManager::GetStateManager();
    graphic = Graphic::GetGraphic();
    msg_manager = Message_Manager::Get_Message_Manager();
	
    app_->Init();
    object_manager->Init();
    state_manager->Init();
    graphic->Init();
    msg_manager->Init();

    state_manager->AddState("Logo", new Logo);
    state_manager->AddState("Menu", new MainMenu);
    state_manager->AddState("Level1", new Level1);
    state_manager->AddState("Tutorial", new Tutorial);
    state_manager->AddState("SoundOption", new SoundOption);
    state_manager->AddState("TestLevel", new TestLevel);
	state_manager->AddState("Testing_Level", new Testing_Level);
	state_manager->AddState("Loading", new Loading_Scene);
    game_timer.Reset();
}

void Engine::Update()
{
    m_dt = game_timer.GetElapsedSeconds();
    game_timer.Reset();

    app_->Update(m_dt);
    graphic->Update(m_dt);
	state_manager->Update(m_dt);
    object_manager->Update(m_dt);
    msg_manager->Update(m_dt);

    if (input.Is_Key_Triggered(GLFW_KEY_1))
    {
        state_manager->is_pause = !state_manager->is_pause;
    }
    if (input.Is_Key_Triggered(GLFW_KEY_N))
    {
        Clear();
        StateManager::GetStateManager()->Get_States().at("Level1").get()->Load();
    }
}

void Engine::Delete()
{
    object_manager->Delete();
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