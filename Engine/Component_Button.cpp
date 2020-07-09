/*
 * Author		:Sangmin Kim
 * File			:Component_Button.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Component Button
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Button.h"

void Component_Button::Init(Object* obj)
{
	m_owner = obj;
}

void Component_Button::Update(float dt)
{
}

void Component_Button::Collided(Object* obj)
{
	if (obj != nullptr)
	{
		std::string obj_name = obj->GetName();

		if (obj_name == "second")
		{
			if (player_2 == nullptr)
			{
				player_2 = obj;
				curr_num++;
			}
		}
		else if (obj_name == "third")
		{
			if (player_3 == nullptr)
			{
				player_3 = obj;
				curr_num++;
			}
		}
		else if (obj_name == "fourth")
		{
			if (player_4 == nullptr)
			{
				player_4 = obj;
				curr_num++;
			}
		}
		else if (obj_name == "first")
		{
			if (player_1 == nullptr)
			{
				player_1 = obj;
				curr_num++;
			}
		}
	}
}

void Component_Button::Collided_Off(Object* obj)
{
	if (obj == player_1)
	{
		player_1 = nullptr;
		curr_num--;
	}
	else if (obj == player_2)
	{
		player_2 = nullptr;
		curr_num--;
	}
	else if (obj == player_3)
	{
		player_3 = nullptr;
		curr_num--;
	}
	else if (obj == player_4)
	{
		player_4 = nullptr;
		curr_num--;
	}
}
