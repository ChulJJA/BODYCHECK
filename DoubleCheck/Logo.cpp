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

namespace
{
    ObjectManager* object_manager = nullptr;
    StateManager* state_manager = nullptr;
}

void Logo::Load()
{
    //GL::set_clear_color({ 0,0,0 });
    //state_manager = StateManager::GetStateManager();
    //object_manager = ObjectManager::GetObjectManager();

    //Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
    //Graphic::GetGraphic()->get_need_update_sprite() = true;

    digipen_logo = new Object();
    digipen_logo->Set_Name("digipen_logo");
    digipen_logo->AddComponent(new Sprite(digipen_logo, "../Sprite/DigipenLogo.png", { 0, 0 }, false, Sprite_Type::None), "logo", true);
    digipen_logo->GetTransform().SetScale({ 24, 6 });
    digipen_logo->Set_Need_To_Update(true); 

    fmod_logo = new Object();
    fmod_logo->Set_Name("fmodLogo");
    fmod_logo->AddComponent(new Sprite(fmod_logo, "../Sprite/FMODLogo.png", { 0, 0 }, false, Sprite_Type::None), "logo2", true);
    fmod_logo->GetTransform().SetScale({ 24, 6 });

    team_logo = new Object();
    team_logo->Set_Name("teamLogo");
    team_logo->AddComponent(new Sprite(team_logo, "../Sprite/TeamLogo.png", true, 14, 8, {0, 0}, { 350,350},
		{ 255,255,255,255 }, Sprite_Type::None), "logo", true);
    team_logo->AddComponent(new Sprite(team_logo, "../Sprite/TeamLogo.png", { 0,0 }, false, Sprite_Type::None), "logo3", false);
	team_logo->GetTransform().SetScale({ 10, 6 });
}

void Logo::Update(float dt)
{
	if(input.Is_Key_Triggered(GLFW_KEY_ENTER) || input.Is_Key_Triggered(GLFW_KEY_SPACE))
	{
        is_next = true;
        next_level = "Menu";
	}
    logo_timer += dt;

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
        ObjectManager::GetObjectManager()->AddObject(team_logo);
        logo_on3 = false;

    }
    if (logo_timer >= 8 && logo_dead3 == true)
    {
        //team_logo->SetDeadCondition(true);
        logo_dead3 = false;
        is_next = true;
        GL::set_clear_color({ 0.31372, 0.73725, 0.8745, 1 });
        next_level = "Menu";
    }
   
}

void Logo::Clear()
{
}