/*
 * Author		:Suwhan Kim
 * File			:Input.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Input.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include <bitset>
#include "vector2.hpp"
#define NEW_GLFW_KEY_LAST_ 348
#define NEW_GLFW_MOUSE_BUTTON_LAST_ 7

class Input
{
private:
    std::bitset<NEW_GLFW_KEY_LAST_> key_pressed;
    std::bitset<NEW_GLFW_KEY_LAST_> key_released;
    std::bitset<NEW_GLFW_KEY_LAST_> key_triggered;

    std::bitset<NEW_GLFW_MOUSE_BUTTON_LAST_> mouse_triggered;
    std::bitset<NEW_GLFW_MOUSE_BUTTON_LAST_> mouse_released;
    std::bitset<NEW_GLFW_MOUSE_BUTTON_LAST_> mouse_double_clicked;
    std::bitset<NEW_GLFW_MOUSE_BUTTON_LAST_> mouse_pressed;

    vector2 mouse_position{};
    double x_offset = 0.0;
    double y_offset = 0.0;

public:
    void Triggered_Reset();
    void Set_Keyboard_Input(int key, int action);
    void Set_Mouse_Input(int button, int action);
    void Set_Mouse_Position(double x, double y);
    void Set_Mouse_Wheel(double x, double y);
    void Init();

    bool Is_Key_Triggered(int key);
    bool Is_Key_Released(int key);
    bool Is_Key_Pressed(int key);

    bool Is_Mouse_Triggered(int button);
    bool Is_Mouse_Pressed(int button);
    bool Is_Mouse_Released(int button);
    bool Is_Mouse_Double_Clicked(int button);
    double Mouse_Wheel_Scroll();
    vector2 Get_Mouse_Pos();

};

extern Input input;