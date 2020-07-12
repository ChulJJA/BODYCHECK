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
	
	FMOD_BOOL isPlaying;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::CreditBGM)], &isPlaying);
	if (!isPlaying)
	{
		sound.Play(SOUND::CreditBGM);
	}	
}

void Credit::Update(float dt)
{
	if (input.Is_Key_Triggered(GLFW_KEY_ESCAPE))
	{
		Component* credit_current_sprite = credit->Get_Current_Sprite();
		Component* credit_first_sprite = credit->Find_Sprite_By_Type(Sprite_Type::Credit_First);
		Component* credit_second_sprite = credit->Find_Sprite_By_Type(Sprite_Type::Credit_Second);
		Component* credit_third_sprite = credit->Find_Sprite_By_Type(Sprite_Type::Credit_Third);

		if (credit_current_sprite == credit_third_sprite)
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
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit4.png", { 0, 0 }, false, Sprite_Type::Credit_First), "credit", true);
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit5.png", { 0, 0 }, false, Sprite_Type::Credit_Second), "sec", false);
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit6.png", { 0, 0 }, false, Sprite_Type::Credit_Third), "third", false);
	credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_First));
	credit->GetTransform().SetScale({ 37, 20.5 });

	ObjectManager::GetObjectManager()->AddObject(credit);
}