#pragma once

#include "vector2.hpp"
#include "string"

class File_Driven_Manager {
public:
	void Get_Player_Info(std::string filename, vector2& pos, vector2& scale, std::string& sprite_path);

};