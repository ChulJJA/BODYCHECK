/*
 * Author		:Sangmin Kim
 * File			:StateManager.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for State Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "StateManager.h"
#include <iostream>
#include "ObjectManager.h"

StateManager* StateManager::state_manager = nullptr;

StateManager* StateManager::GetStateManager()
{
	if (state_manager == nullptr)
		state_manager = new StateManager();

	return state_manager;
}

void StateManager::Init()
{
	current_state = nullptr;
	states.clear();
}

void StateManager::Update(float dt)
{
	if(!current_state->is_pause)
	{
		current_state->Update(dt);

		if (current_state->IsNextLevel())
		{
			current_state->Set_is_next(false);
			prev_state = current_state;
			std::string temp_name = current_state->GetNextLevelName();
			current_state->UnLoad();
			current_state = states.find(temp_name)->second.get();
			if(current_state->is_pause)
			{
				current_state->is_pause = false;
				
			}
			else
			{
				current_state->Load();
			}
		}
	}
	else if(current_state->is_pause)
	{
		LeaveState(dt);
	}
}

void StateManager::Delete()
{
	current_state = nullptr;
	states.clear();
}

void StateManager::AddState(std::string name, State* state)
{
	auto temp = std::make_pair(name, state);

	if (current_state == nullptr)
	{
		if (state->GetStateInfo() == GameState::Logo)
		{
			current_state = state;
			current_state->Load();
		}
	}
	states.insert(temp);
}

void StateManager::DeleteState()
{
	states.erase("Level1");
}

void StateManager::LeaveState(float dt)
{
	std::string stateName;
	prev_state = current_state;

	if(prev_state->GetStateInfo() == GameState::Game)
	{
		stateName = "PauseLevel";
	}
	else if(prev_state->GetStateInfo() == GameState::PauseLevel)
	{
		prev_state->UnLoad();
		stateName = "Option";
	}
	else
	{
		prev_state->UnLoad();
		level_state->is_pause = false;
		level_state->UnLoad();
		stateName = " MainMenu";
	}
	current_state = states.find(stateName)->second.get();
	current_state->Load();
}

void StateManager::BackToLevel()
{
	level_state->is_pause = false;
	prev_state = current_state;
	current_state->UnLoad();
	current_state = level_state;
}