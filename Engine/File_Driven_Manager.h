/*
 * Author		:Sangmin Kim
 * File			:File_Driven_Manager.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for File Driven Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */
#pragma once

#include "vector2.hpp"
#include "string"

class File_Driven_Manager {
public:
	void Get_Player_Info(std::string filename, vector2& pos, vector2& scale, std::string& sprite_path);

};