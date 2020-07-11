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

using namespace std;

namespace
{
	ObjectManager* object_manager = nullptr;

}

void Credit::Load()
{
	current_state = GameState::Credit;
	SetTestSprite();
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
			is_next = true;
			next_level = "Menu";
			Clear();
		}
		else if (credit_current_sprite == credit_first_sprite)
		{
			credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_Second));
		}
		else if (credit_current_sprite == credit_second_sprite)
		{
			credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_Third));
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
	credit->AddComponent(new Sprite(credit, "../Sprite/Credit.png", { 0, 0 }, false, Sprite_Type::Credit_First), "credit", true);
	credit->AddComponent(new Sprite(credit, "../Sprite/ExplanationStaff.png", { 0, 0 }, false, Sprite_Type::Credit_Second), "sec", false);
	credit->AddComponent(new Sprite(credit, "../Sprite/HowToPlay.png", { 0, 0 }, false, Sprite_Type::Credit_Third), "third", false);
	credit->Change_Sprite(credit->Find_Sprite_By_Type(Sprite_Type::Credit_First));
	credit->GetTransform().SetScale({ 37, 20.5 });

	ObjectManager::GetObjectManager()->AddObject(credit);
}