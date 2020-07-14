/*
 * Author		:Chulseung Lee
 * File			:Credit.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Credit
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include <GLFW/glfw3.h>
#include "Credit.h"
#include <Input.h>
#include "Component_Button.h"
#include "Message_Manager.h"
#include "Engine.hpp"

using namespace std;

namespace
{
	ObjectManager* object_manager = nullptr;

}

void Credit::Load()
{
	FMOD_BOOL isBGMPlaying;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM)], &isBGMPlaying);
	if (isBGMPlaying)
	{
		sound.Stop(SOUND::BGM);
	}
	
	current_state = GameState::Credit;
	SetTestSprite();
	second = 3.f;
	
	FMOD_BOOL isPlaying;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::CreditBGM)], &isPlaying);
	if (!isPlaying)
	{
		sound.Play(SOUND::CreditBGM);
	}	
}

void Credit::Update(float dt)
{
	second -= dt;
	if (input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER) || second < 0.f)
	{
		second = 3.f;
		Component* credit_current_sprite = credit->Get_Current_Sprite();
		Component* credit_first_sprite = credit->Find_Sprite_By_Type(Sprite_Type::Credit_First);
		Component* credit_second_sprite = credit->Find_Sprite_By_Type(Sprite_Type::Credit_Second);
		Component* credit_third_sprite = credit->Find_Sprite_By_Type(Sprite_Type::Credit_Third);
		Component* credit_fourth_sprite = credit->Find_Sprite_By_Type(Sprite_Type::Credit_Fourth);
		Component* credit_fifth_sprite = credit->Find_Sprite_By_Type(Sprite_Type::Credit_Fifth);
		Component* credit_sixth_sprite = credit->Find_Sprite_By_Type(Sprite_Type::Credit_Sixth);

		if (credit_current_sprite == credit_sixth_sprite)
		{
			sound.Play(SOUND::Selected);

			FMOD_BOOL isPlaying;

			FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::CreditBGM)], &isPlaying);

			if(isPlaying)
			{
				sound.Stop(SOUND::CreditBGM);
			}
			is_next = true;
			next_level = "Menu";
			Clear();
		}
		else if (credit_current_sprite == credit_first_sprite)
		{
			credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_Second));
			sound.Play(SOUND::Selected);
		}
		else if (credit_current_sprite == credit_second_sprite)
		{
			credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_Third));
			sound.Play(SOUND::Selected);
		}
		else if (credit_current_sprite == credit_third_sprite)
		{
			credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_Fourth ));
			sound.Play(SOUND::Selected);
		}
		
		else if (credit_current_sprite == credit_fourth_sprite)
		{
			credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_Fifth));
			sound.Play(SOUND::Selected);
		}
		else if (credit_current_sprite == credit_fifth_sprite)
		{
			credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_Sixth));
			sound.Play(SOUND::Selected);
		}
		

	}
}

void Credit::Clear()
{
	credit->SetDeadCondition(true);
}

void Credit::SetTestSprite()
{
	credit = new Object();
	credit->Set_Name("credit");
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit1.png", { 0, 0 }, false, Sprite_Type::Credit_First), "credit", true);
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit2.png", { 0, 0 }, false, Sprite_Type::Credit_Second), "sec", false);
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit3.png", { 0, 0 }, false, Sprite_Type::Credit_Third), "third", false);
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit4.png", { 0, 0 }, false, Sprite_Type::Credit_Fourth), "fourth", false);
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit5.png", { 0, 0 }, false, Sprite_Type::Credit_Fifth), "fifth", false);
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit6.png", { 0, 0 }, false, Sprite_Type::Credit_Sixth), "sixth", false);
	credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_First));
	credit->GetTransform().SetScale({ 37, 20.5 });

	ObjectManager::GetObjectManager()->AddObject(credit);
}