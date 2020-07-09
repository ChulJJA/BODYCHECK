/*
 * Author		:Sangmin Kim
 * File			:Messagebox.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message Box
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include "Texture.hpp"
class Messagebox
{
public:

    static void Init_Box(const std::filesystem::path& file_path);
    void Process(const std::string& fileName);
};