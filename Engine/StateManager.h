/*
 * Author		:Sangmin Kim
 * File			:StateManager.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for State Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "State.h"
#include <unordered_map>
#include <memory>

class StateManager
{
public:
    static StateManager* GetStateManager();
    void Init();
    void Update(float dt);
    void Delete();
    void AddState(std::string name, State* state);
    void DeleteState();
    std::unordered_map<std::string, std::shared_ptr<State>> Get_States()
    {
        return states;
    }

    State* GetCurrentState()
    {
        return current_state;
    }
    State* GetPrevState()
    {
        return prev_state;
    }
    bool is_pause = false;
    void LeaveState(float dt);
    void BackToLevel();
    void BackToMenu();
    void SetPrevState(State* state)
    {
        prev_state = state;
    }
    State* level_state = nullptr;
private:
    static StateManager* state_manager;
    std::unordered_map<std::string, std::shared_ptr<State>> states;
    State* current_state = nullptr;
	State* prev_state = nullptr;
};