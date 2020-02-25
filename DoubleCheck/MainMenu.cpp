/*
 * Author		:Suhwan Kim
 * File			:MainMenu.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Cpp for main menu.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "MainMenu.h"
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
#include "UsefulTools.hpp"

GLFWgamepadstate state;

namespace
{
    ObjectManager* object_manager = nullptr;
    StateManager* state_manager = nullptr;
}

void MainMenu::Load()
{

    state_manager = StateManager::GetStateManager();
    object_manager = ObjectManager::GetObjectManager();

    Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
    Graphic::GetGraphic()->get_need_update_sprite() = true;

    button = new Object();
    button->Set_Name("play_button");
    button->AddComponent(new Sprite(button, "../Sprite/play_button.png", { 0, 400 }));
    button->GetTransform().SetScale({ 3, 3 });
    ObjectManager::GetObjectManager()->AddObject(button);

    music_button = new Object();
    music_button->Set_Name("music_button");
    music_button->AddComponent(new Sprite(music_button, "../Sprite/play_button.png", { 0, 0 }));
    music_button->GetTransform().SetScale({ 3, 3 });
    ObjectManager::GetObjectManager()->AddObject(music_button);

    test_level_button = new Object();
    test_level_button->Set_Name("music_button");
    test_level_button->AddComponent(new Sprite(test_level_button, "../Sprite/play_button.png", { 0, -400 }));
    test_level_button->GetTransform().SetScale({ 3, 3 });
    ObjectManager::GetObjectManager()->AddObject(test_level_button);
}

void MainMenu::Update(float dt)
{
    if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
    {
        if (state.buttons[GLFW_GAMEPAD_BUTTON_A])
        {
            sound.play(SOUND::Click);
            is_next = true;
            next_level = "Level1";
            Clear();
        }
    }

    if (MouseCollision(vector2{ 54, 54 }, vector2{ -54, -54 },
        vector2{ input.Get_Mouse_Pos().x, input.Get_Mouse_Pos().y }) == true)
    {
        if (input.Is_Mouse_Released(GLFW_MOUSE_BUTTON_LEFT))
        {
            sound.play(SOUND::Click);
            is_next = true;
            next_level = "Level1";
            Clear();
        }
    }

	if(input.Is_Key_Pressed(GLFW_KEY_S))
	{
        sound.play(SOUND::Click);
        is_next = true;
        next_level = "Level1";
        Clear();
	}

	if(input.Is_Key_Pressed(GLFW_KEY_M))
	{
        sound.play(SOUND::Click);
        is_next = true;
        next_level = "SoundOption";
        Clear();
	}

    if (input.Is_Key_Pressed(GLFW_KEY_T))
    {
        sound.play(SOUND::Click);
        is_next = true;
        next_level = "TestLevel";
        Clear();
    }
}

void MainMenu::Clear()
{
    button->SetDeadCondition(true);
    object_manager->Clear();
}