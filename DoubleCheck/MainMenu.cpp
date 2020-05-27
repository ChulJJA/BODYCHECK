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
#include <GLFW/glfw3.h>
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
#include "Gamepad.hpp"
#include "Level1.h"


namespace
{
    ObjectManager* object_manager = nullptr;
    StateManager* state_manager = nullptr;
    Gamepad* gamepadManager = nullptr;
}

void MainMenu::Load()
{
	if(sound.isInitialized == false)
	{
        sound.Initialize();
	}
    FMOD_BOOL isPlaying;
    FMOD_Channel_IsPlaying(sound.channel[0], &isPlaying);
	if(isPlaying == false)
	{
        sound.Play(SOUND::BGM);
	}
    state_manager = StateManager::GetStateManager();
    object_manager = ObjectManager::GetObjectManager();
    gamepadManager = Gamepad::getGamepad();

    Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
    Graphic::GetGraphic()->get_need_update_sprite() = true;

    pointer = 0;
    button_timer = 0;

    Object* back = new Object();

    back->AddComponent(new Sprite(back, "../Sprite/menu_background.png", false, 2, 8, {0.f, 0.f}, { 50.f,50.f },
        { 255,255,255,255 }, Sprite_Type::None), "none", true);
    back->GetTransform().SetScale({ 40.f, 22.f });
    object_manager->AddObject(back);
    SetPlayButton();
    SetTutorialButton();
    SetMusicButton();
    SetTestLevelButton();
}

void MainMenu::Update(float dt)
{

    button_timer++;
	
    if (button_timer >= 10)
    {
        ButtonSelector();
    }
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

void MainMenu::SetTutorialButton()
{
    tutorial_button = new Object();
    tutorial_button->Set_Name("tutorial_button");
    tutorial_button->AddComponent(new Sprite(tutorial_button, "../Sprite/TutorialButton.png", { 0, 150 }, false));
    tutorial_button->GetTransform().SetScale({ 5, 5 });
    ObjectManager::GetObjectManager()->AddObject(tutorial_button);

    tutorial_button_hover = new Object();
    tutorial_button_hover->Set_Name("tutorial_button_hover");
    tutorial_button_hover->AddComponent(new Sprite(tutorial_button_hover, "../Sprite/TutorialButtonHover.png", { 0, 150 }, false));
    tutorial_button_hover->GetTransform().SetScale({ 5, 5 });
    tutorial_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
    ObjectManager::GetObjectManager()->AddObject(tutorial_button_hover);
}

void MainMenu::SetMusicButton()
{
    music_button = new Object();
    music_button->Set_Name("music_button");
    music_button->AddComponent(new Sprite(music_button, "../Sprite/MusicButton.png", { 0, -100 }, false));
    music_button->GetTransform().SetScale({ 5, 5 });
    ObjectManager::GetObjectManager()->AddObject(music_button);

    music_button_hover = new Object();
    music_button_hover->Set_Name("music_button_hover");
    music_button_hover->AddComponent(new Sprite(music_button_hover, "../Sprite/MusicButtonHover.png", { 0, -100 }, false));
    music_button_hover->GetTransform().SetScale({ 5, 5 });
    music_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
    ObjectManager::GetObjectManager()->AddObject(music_button_hover);
}

void MainMenu::SetTestLevelButton()
{
    test_button = new Object();
    test_button->Set_Name("test_button");
    test_button->AddComponent(new Sprite(test_button, "../Sprite/TestButton.png", { 0, -350 }, false));
    test_button->GetTransform().SetScale({ 5, 5 });
    ObjectManager::GetObjectManager()->AddObject(test_button);

    test_button_hover = new Object();
    test_button_hover->Set_Name("test_button_hover");
    test_button_hover->AddComponent(new Sprite(test_button_hover, "../Sprite/TestButtonHover.png", { 0, -350 }, false));
    test_button_hover->GetTransform().SetScale({ 5, 5 });
    test_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
    ObjectManager::GetObjectManager()->AddObject(test_button_hover);
}

void MainMenu::ButtonSelector()
{
    float LeftThumbStateY = gamepadManager->LeftStick_Y();

	if((input.Is_Key_Pressed(GLFW_KEY_DOWN) || (LeftThumbStateY < 0)) && pointer <= static_cast<int>(BUTTON::TEST))
	{
        pointer++;
		
        if (pointer == static_cast<int>(BUTTON::START))
        {
            sound.Play(SOUND::Click);
            ObjectHover(play_button, play_button_hover);
        }
        else if (pointer == static_cast<int>(BUTTON::TUTORIAL))
        {
            sound.Play(SOUND::Click);
            ObjectHover(tutorial_button, tutorial_button_hover);
            ObjectHover(play_button_hover, play_button);
        }
        else if(pointer == static_cast<int>(BUTTON::MUSIC))
        {
            sound.Play(SOUND::Click);
            ObjectHover(music_button, music_button_hover);
            ObjectHover(tutorial_button_hover, tutorial_button);
        }
        else if(pointer == static_cast<int>(BUTTON::TEST))
        {
            sound.Play(SOUND::Click);
            ObjectHover(test_button, test_button_hover);
            ObjectHover(music_button_hover, music_button);
        }
        else if(pointer > 3)
        {
            pointer = 3;
        }
        button_timer = 0;
	}
    else if((input.Is_Key_Pressed(GLFW_KEY_UP) || LeftThumbStateY > 0)&& pointer >= static_cast<int>(BUTTON::START))
    {
        pointer--;
    	
        if (pointer == static_cast<int>(BUTTON::START))
        {
            sound.Play(SOUND::Click);
            ObjectHover(play_button, play_button_hover);
            ObjectHover(tutorial_button_hover, tutorial_button);
        }
        else if (pointer == static_cast<int>(BUTTON::TUTORIAL))
        {
            sound.Play(SOUND::Click);
            ObjectHover(tutorial_button, tutorial_button_hover);
            ObjectHover(music_button_hover, music_button);
        }
        else if (pointer == static_cast<int>(BUTTON::MUSIC))
        {
            sound.Play(SOUND::Click);
            ObjectHover(music_button, music_button_hover);
            ObjectHover(test_button_hover, test_button);
        }
        else if (pointer == static_cast<int>(BUTTON::TEST))
        {
            sound.Play(SOUND::Click);
            ObjectHover(test_button, test_button_hover);
        }
        else if(pointer < 0)
        {
            pointer = 0;
        }
        button_timer = 0;
    }

	if((input.Is_Key_Pressed(GLFW_KEY_SPACE) || gamepadManager->GetButtonDown(xButtons.A))&& pointer == static_cast<int>(BUTTON::START))
	{
        pointer = static_cast<int>(BUTTON::START);
		sound.Play(SOUND::Selected);
        StateManager::GetStateManager()->level_state->is_pause = false;
        is_next = true;
        next_level = "Level1";
        Sleep(500);
        sound.UnLoad();
        Clear();
	}
    else if ((input.Is_Key_Pressed(GLFW_KEY_SPACE) || gamepadManager->GetButtonDown(xButtons.A)) && pointer == static_cast<int>(BUTTON::TUTORIAL))
    {
        sound.Play(SOUND::Selected);
        is_next = true;
            next_level = "Tutorial";
        Clear();
    }
    else if ((input.Is_Key_Pressed(GLFW_KEY_SPACE) || gamepadManager->GetButtonDown(xButtons.A)) && pointer == static_cast<int>(BUTTON::MUSIC))
    {
        pointer = static_cast<int>(BUTTON::START);
        sound.Play(SOUND::Selected);
        is_next = true;
        next_level = "Option";
        Clear();
    }
    else if ((input.Is_Key_Pressed(GLFW_KEY_SPACE) || gamepadManager->GetButtonDown(xButtons.A)) && pointer == static_cast<int>(BUTTON::TEST))
    {
        pointer = static_cast<int>(BUTTON::START);
        sound.Play(SOUND::Selected);
        is_next = true;
        next_level = "TestLevel";
        Clear();
    }
}