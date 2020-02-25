/*
 * Author		:Minseok Sung
 * File			:Messagebox.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Messagebox.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include "Texture.hpp"
class Messagebox
{
public:

    static void Init_Box(const std::filesystem::path& file_path);
    void Process(const std::string& fileName);
};