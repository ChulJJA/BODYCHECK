#pragma once
#include "Object.h"

Object* SetObject(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);

Object* SetArena(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);
Object* SetPauseText(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);
Object* SetRestartButton(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);
Object* SetMainMenuButton(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);
Object* SetOptionButton(std::string name, std::string tag, std::string sprite_path, vector2 pos, vector2 scale);