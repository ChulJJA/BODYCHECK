/*
 * Author		:Chulseung Lee
 * File			:MainMenu.cpp
 * Term			:2020 Spring
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/02/25
 * Description	:This file contains codes for main menu.
 *
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
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

    SetPlayButton();
    SetMusicButton();
    SetTestLevelButton();
}

void MainMenu::Update(float dt)
{
    std::cout << pointer << std::endl;
    std::cout << button_timer << std::endl;
    button_timer++;
	
    if (button_timer >= 10)
    {
        ButtonSelector();
    }
 //   if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
 //   {
 //       if (state.buttons[GLFW_GAMEPAD_BUTTON_A])
 //       {
 //           sound.play(SOUND::Click);
 //           is_next = true;
 //           next_level = "Level1";
 //           Clear();
 //       }
 //   }
}

void MainMenu::Clear()
{
    object_manager->Clear();
}

void MainMenu::SetPlayButton()
{
    play_button = new Object();
    play_button->Set_Name("play_button");
    play_button->AddComponent(new Sprite(play_button, "../Sprite/PlayButton.png", { 0, 400 }, false));
    play_button->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
    play_button->GetTransform().SetScale({ 5, 5});
    ObjectManager::GetObjectManager()->AddObject(play_button);

    play_button_hover = new Object();
    play_button_hover->Set_Name("play_button_hover");
    play_button_hover->AddComponent(new Sprite(play_button_hover, "../Sprite/PlayButtonHover.png", { 0, 400 }, false));
    play_button_hover->GetTransform().SetScale({ 5, 5 });
    ObjectManager::GetObjectManager()->AddObject(play_button_hover);
}

void MainMenu::SetMusicButton()
{
    music_button = new Object();
    music_button->Set_Name("music_button");
    music_button->AddComponent(new Sprite(music_button, "../Sprite/MusicButton.png", { 0, 0 }, false));
    music_button->GetTransform().SetScale({ 5, 5 });
    ObjectManager::GetObjectManager()->AddObject(music_button);

    music_button_hover = new Object();
    music_button_hover->Set_Name("music_button_hover");
    music_button_hover->AddComponent(new Sprite(music_button_hover, "../Sprite/MusicButtonHover.png", { 0, 0 }, false));
    music_button_hover->GetTransform().SetScale({ 5, 5 });
    music_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
    ObjectManager::GetObjectManager()->AddObject(music_button_hover);
}

void MainMenu::SetTestLevelButton()
{
    test_button = new Object();
    test_button->Set_Name("test_button");
    test_button->AddComponent(new Sprite(test_button, "../Sprite/TestButton.png", { 0, -400 }, false));
    test_button->GetTransform().SetScale({ 5, 5 });
    ObjectManager::GetObjectManager()->AddObject(test_button);

    test_button_hover = new Object();
    test_button_hover->Set_Name("test_button_hover");
    test_button_hover->AddComponent(new Sprite(test_button_hover, "../Sprite/TestButtonHover.png", { 0, -400 }, false));
    test_button_hover->GetTransform().SetScale({ 5, 5 });
    test_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
    ObjectManager::GetObjectManager()->AddObject(test_button_hover);
}

void MainMenu::ButtonSelector()
{
	if(input.Is_Key_Pressed(GLFW_KEY_DOWN) && pointer <= static_cast<int>(BUTTON::TEST))
	{
        pointer++;
		
        if (pointer == static_cast<int>(BUTTON::START))
        {
            ObjectHover(play_button, play_button_hover);
        }
        else if(pointer == static_cast<int>(BUTTON::MUSIC))
        {
            ObjectHover(music_button, music_button_hover);
            ObjectHover(play_button_hover, play_button);
        }
        else if(pointer == static_cast<int>(BUTTON::TEST))
        {
            ObjectHover(test_button, test_button_hover);
            ObjectHover(music_button_hover, music_button);
        }
        else if(pointer > 2)
        {
            pointer = 2;
        }
        button_timer = 0;
	}
    else if(input.Is_Key_Pressed(GLFW_KEY_UP) && pointer >= static_cast<int>(BUTTON::START))
    {
        pointer--;
    	
        if (pointer == static_cast<int>(BUTTON::START))
        {
            ObjectHover(play_button, play_button_hover);
            ObjectHover(music_button_hover, music_button);
        }
        else if (pointer == static_cast<int>(BUTTON::MUSIC))
        {
            ObjectHover(music_button, music_button_hover);
            ObjectHover(test_button_hover, test_button);
        }
        else if (pointer == static_cast<int>(BUTTON::TEST))
        {
            ObjectHover(test_button, test_button_hover);
        }
        else if(pointer < 0)
        {
            pointer = 0;
        }
        button_timer = 0;
    }

	if(input.Is_Key_Pressed(GLFW_KEY_SPACE) && pointer == static_cast<int>(BUTTON::START))
	{
        sound.play(SOUND::Click);
        is_next = true;
        next_level = "Level1";
        Clear();
	}
    else if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && pointer == static_cast<int>(BUTTON::MUSIC))
    {
        sound.play(SOUND::Click);
        is_next = true;
        next_level = "SoundOption";
        Clear();
    }
    if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && pointer == static_cast<int>(BUTTON::TEST))
    {
        sound.play(SOUND::Click);
        is_next = true;
        next_level = "TestLevel";
        Clear();
    }
}