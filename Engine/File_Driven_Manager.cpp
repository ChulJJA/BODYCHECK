/*
 * Author		:Sangmin Kim
 * File			:File_Driven_Manager.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for File Driven Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include <fstream>
#include <sstream>

#include "File_Driven_Manager.h"

void File_Driven_Manager::Get_Player_Info(std::string filename, vector2& pos, vector2& scale, std::string& sprite_path)
{
	std::ifstream readFile(filename);

	if (readFile.is_open())
	{
		std::string line;
		std::string type;
		while (std::getline(readFile, line))
		{
			std::stringstream keystream(line);
			keystream >> type;

			if (type == "Sprite:")
			{
				keystream >> sprite_path;
			}
			else if (type == "Position:")
			{
				keystream >> pos.x;
				keystream >> pos.y;
			}
			else if (type == "Scale:")
			{
				keystream >> scale.x;
				keystream >> scale.y;
			}
		}
	}
}
