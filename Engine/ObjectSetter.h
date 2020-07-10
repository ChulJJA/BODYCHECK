/*
 * Author		:Sangmin Kim
 * File			:ObjectSetter.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Object Setter
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Object.h"

Object* SetObject(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);

Object* SetArena(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);
Object* SetPauseText(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);
Object* SetRestartButton(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);
Object* SetMainMenuButton(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);
Object* SetOptionButton(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);