/*
 * Author		:Sangmin Kim
 * File			:MessageBox.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Message Box
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include <Windows.h>
#include "Messagebox.h"
#include <iostream>

void Messagebox::Init_Box(const std::filesystem::path& file_path)
{
    int msgboxID = MessageBox(
        NULL,
        file_path.string().c_str(),
        "Check Box",
        MB_ICONEXCLAMATION | MB_OK
    );
    if (msgboxID == MB_OK)
    {
        std::cout << file_path.string() << std::endl;
    }
}