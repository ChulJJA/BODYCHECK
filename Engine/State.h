/*
 * Author		:Sangmin Kim
 * File			:State.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for State
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <string>
#include "BitmapFont.hpp"

class Color4f;
struct vector2;
class PLAYER_UI;
class Object;

enum class GameState
{
     Logo, Menu, Game, Tutorial, Credit, Option, None, PauseLevel
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
    float Get_Trans_Timer()
    {
        return transition_timer;
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

	Object* Make_Player(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale, bool is_main_menu = false);
	PLAYER_UI* Make_Set_Ui(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale, Object* player);
	Object* Make_Set_Text(std::string name, std::string tag, vector2 pos, Object* player, Color4f color, vector2 size, BitmapFont* font);
    bool is_pause = false;

protected:
    std::string next_level;
    bool is_next = false;
    GameState current_state = GameState::None;
    float transition_timer = 0.f;

	BitmapFont      font{};
};