/*
 * Author		:Suhwan Kim
 * File			:Logo.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Cpp for Logo.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "ObjectManager.h"
#include "Component_Text.h"
#include "StateManager.h"
#include "Object.h"
#include "Windows.h"
#include "Logo.h"
#include "gl.hpp"

namespace
{
    ObjectManager* object_manager = nullptr;
    StateManager* state_manager = nullptr;
}

void Logo::Load()
{
    GL::set_clear_color({ 1,1,1,1 });
    state_manager = StateManager::GetStateManager();
    object_manager = ObjectManager::GetObjectManager();

    Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
    Graphic::GetGraphic()->get_need_update_sprite() = true;

    digipen_logo = new Object();
    digipen_logo->Set_Name("digipen_logo");
    digipen_logo->Set_Tag("logo");
    digipen_logo->AddComponent(new Sprite(digipen_logo, "../Sprite/DigipenLogo.png", { 0, 0 }, false));
    digipen_logo->GetTransform().SetScale({ 24, 6 });

    fmod_logo = new Object();
    fmod_logo->Set_Name("play_button");
    fmod_logo->Set_Tag("button");
    fmod_logo->AddComponent(new Sprite(fmod_logo, "../Sprite/FMODLogo.png", { 0, 0 }, false));
    fmod_logo->GetTransform().SetScale({ 24, 6 });

    team_logo = new Object();
    team_logo->Set_Name("play_button");
    team_logo->Set_Tag("button");
    team_logo->AddComponent(new Sprite(team_logo, "../Sprite/TeamLogo.png", true, 8, 10.0f, { 0, 0 }, { 350,350 }));
    team_logo->GetTransform().SetScale({ 10, 6 });
}

void Logo::Update(float dt)
{
    //logo_timer += dt;

    //if (logo_on == true)
    //{
    //    ObjectManager::GetObjectManager()->AddObject(digipen_logo);
    //    logo_on = false;

    //}
    //if (logo_timer >= 3 && logo_dead == true)
    //{
    //    logo_on2 = true;
    //    logo_dead = false;
    //    logo_dead2 = true;
    //    digipen_logo->SetDeadCondition(true);
    //}
    //if (logo_on2 == true)
    //{
    //    ObjectManager::GetObjectManager()->AddObject(fmod_logo);
    //    logo_on2 = false;
    //}
    //if (logo_timer >= 6 && logo_dead2 == true)
    //{
    //    logo_on3 = true;
    //    logo_dead2 = false;
    //    logo_dead3 = true;
    //    fmod_logo->SetDeadCondition(true);
    //}

    //if (logo_on3 == true)
    //{
    //    GL::set_clear_color({ 0,0,0 });
    //    ObjectManager::GetObjectManager()->AddObject(team_logo);
    //    logo_on3 = false;z

    //}
    //if (logo_timer >= 8 && logo_dead3 == true)
    //{
    //    team_logo->SetDeadCondition(true);
    //    logo_dead3 = false;
    //    is_next = true;
    //    GL::set_clear_color({ 0.31372, 0.73725, 0.8745, 1 });
    //    next_level = "Menu";
    //}
    //
    is_next = true;
    GL::set_clear_color({ 0.31372, 0.73725, 0.8745, 1 });
    next_level = "Menu";
}

void Logo::Clear()
{
}