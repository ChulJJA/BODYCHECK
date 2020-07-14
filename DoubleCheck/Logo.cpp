/*
 * Author		:Chulseung Lee
 * File			:Logo.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for logo
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include <GLFW/glfw3.h>
#include "ObjectManager.h"
#include "Component_Text.h"
#include "StateManager.h"
#include "Object.h"
#include "Windows.h"
#include "Logo.h"
#include <Input.h>
#include "gl.hpp"
#include "Gamepad.hpp"
#include "Sound_Manager.h"
#include "Engine.hpp"

namespace
{
    ObjectManager* object_manager = nullptr;
    StateManager* state_manager = nullptr;
}

void Logo::Load()
{
    GL::set_clear_color({ 1,1,1 });
    state_manager = StateManager::GetStateManager();
    state_manager->SetPrevState(new Logo());

    digipen_logo = new Object();
    digipen_logo->Set_Name("digipen_logo");
    digipen_logo->AddComponent(new Sprite(digipen_logo, "../Sprite/DigipenLogo.png", { 0, -60 }, false, Sprite_Type::None), "logo", true);
    digipen_logo->GetTransform().SetScale({ 13, 10 });
    digipen_logo->GetMesh().Get_Is_Moved() = true;

    fmod_logo = new Object();
    fmod_logo->Set_Name("fmodLogo");
    fmod_logo->AddComponent(new Sprite(fmod_logo, "../Sprite/FMODLogo.png", { 0, 0 }, false, Sprite_Type::None), "logo2", true);
    fmod_logo->GetTransform().SetScale({ 10, 3 });

    team_logo = new Object();
    team_logo->Set_Name("teamLogo");
    team_logo->AddComponent(new Sprite(team_logo, "../Sprite/TeamLogo.png", true, 8, 8, {0, 0}, { 100,100},
		{ 255,255,255,255 }, Sprite_Type::None), "logo", true);
	team_logo->GetTransform().SetScale({ 14, 8 });
}

void Logo::Update(float dt)
{
	if(input.Is_Key_Triggered(GLFW_KEY_ENTER) || input.Is_Key_Triggered(GLFW_KEY_SPACE))
	{
        is_next = true;
        next_level = "Menu";
	}
    logo_timer += dt;

    if (!logo_on2)
    {
        digipen_logo->GetMesh().Get_Is_Moved() = true;
    }
    if (!logo_on3)
    {
        fmod_logo->GetMesh().Get_Is_Moved() = true;
    }
    if(logo_dead3)
    {
        team_logo->GetMesh().Get_Is_Moved() = true;
    }
    if (logo_on == true)
    {
        ObjectManager::GetObjectManager()->AddObject(digipen_logo);
        logo_on = false;

    }
    if (logo_timer >= 3 && logo_dead == true)
    {
        logo_on2 = true;
        logo_dead = false;
        logo_dead2 = true;
        digipen_logo->SetDeadCondition(true);
    }
    if (logo_on2 == true)
    {
        ObjectManager::GetObjectManager()->AddObject(fmod_logo);
        logo_on2 = false;
    }
    if (logo_timer >= 6 && logo_dead2 == true)
    {
        logo_on3 = true;
        logo_dead2 = false;
        logo_dead3 = true;
        fmod_logo->SetDeadCondition(true);
    }

    if (logo_on3 == true)
    {
        sound.Play(SOUND::TeamDoubleCheck);
        ObjectManager::GetObjectManager()->AddObject(team_logo);
        logo_on3 = false;

    }
    if (logo_timer >= 8.5 && logo_dead3 == true)
    {
        team_logo->SetDeadCondition(true);
        logo_dead3 = false;
        is_next = true;
        next_level = "Menu";
    }
}

void Logo::Clear()
{
}