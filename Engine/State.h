/*
 * Author		:Sangmin Kim
 * File			:State.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for State.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <string>
#include "BitmapFont.hpp"

struct vector2;
class PLAYER_UI;
class Object;

enum class GameState
{
    Logo, Menu, Game, Credit, Sound, None, TestLevel
};

class State
{
public:
    virtual void Load() = 0;
    virtual void Update(float dt) = 0;
    virtual void UnLoad() = 0;
    bool IsNextLevel()
    {
        return is_next;
    }
    void MoveLevel(std::string name)
    {
        next_level = name;
    }
    std::string GetNextLevelName()
    {
        return next_level;
    }
    GameState GetStateInfo()
    {
        return current_state;
    }

    void Set_is_next(bool set_is_next)
    {
        is_next = set_is_next;
    }
    bool Get_is_next()
    {
        return is_next;
    }

    void Set_next_level(std::string set_next_level)
    {
        next_level = set_next_level;
    }
    std::string Get_next_level()
    {
        return next_level;
    }


	Object* Make_Player(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);
	PLAYER_UI* Make_Set_Ui(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale, Object* player);
	
protected:
    std::string next_level;
    bool is_next = false;
    GameState current_state = GameState::None;
	BitmapFont      font{};
};