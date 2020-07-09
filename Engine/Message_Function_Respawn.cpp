/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Respawn.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Function Respawn
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Respawn.h"
#include "Referee.h"
#include "Engine.hpp"
#include "Message.h"

void Msg_Func_Respawn::Init()
{
}

void Msg_Func_Respawn::Update(float dt)
{
	if (m_from->GetName() == "second")
	{
		std::cout << "second die!" << std::endl;
		sound.Play(SOUND::Die);
		sound.Play(SOUND::Crowd);
		Referee::Get_Referee()->Get_Stage_Statement().push_back(Referee::Stage_Statement::PLAYER_SECOND_DIE);
	}
	if (m_from->GetName() == "first")
	{
		sound.Play(SOUND::Die);
		sound.Play(SOUND::Crowd);
		std::cout << "first die!" << std::endl;
		Referee::Get_Referee()->Get_Stage_Statement().push_back(Referee::Stage_Statement::PLAYER_FIRST_DIE);
	}
	if (m_from->GetName() == "third")
	{
		sound.Play(SOUND::Die);
		sound.Play(SOUND::Crowd);
		std::cout << "third die!" << std::endl;

		Referee::Get_Referee()->Get_Stage_Statement().push_back(Referee::Stage_Statement::PLAYER_THIRD_DIE);
	}
	if (m_from->GetName() == "fourth")
	{
		sound.Play(SOUND::Die);
		sound.Play(SOUND::Crowd);
		std::cout << "forth die!" << std::endl;
		Referee::Get_Referee()->Get_Stage_Statement().push_back(Referee::Stage_Statement::PLAYER_FOURTH_DIE);
	}

	msg->Set_Should_Delete(true);
}
