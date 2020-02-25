/*
 * Author		:Minseok Sung
 * File			:Messagebox.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for message error box.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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