/*
 * Author		:Sangmin Kim
 * File			:Input.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Input
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Input.h"
#include "Application.hpp"
#include <assert.h>
#include <chrono>

Input input;

void Input::Init()
{
    key_pressed.reset();
    key_released.set();
    key_triggered.reset();

    mouse_triggered.reset();
    mouse_released.set();
    mouse_double_clicked.reset();
    mouse_pressed.reset();

    x_offset = 0.0;
    y_offset = 0.0;
}

bool Input::Is_Key_Triggered(int key)
{
    return key_triggered[key];
}

bool Input::Is_Key_Released(int key)
{
    return key_released[key];
}

bool Input::Is_Key_Pressed(int key)
{
    return key_pressed[key];
}

bool Input::Is_Mouse_Triggered(int button)
{
    return mouse_triggered[button];
}

bool Input::Is_Mouse_Pressed(int button)
{
    return mouse_pressed[button];
}

bool Input::Is_Mouse_Released(int button)
{
    return mouse_released[button];
}

bool Input::Is_Mouse_Double_Clicked(int button)
{
    return mouse_double_clicked[button];
}

double Input::Mouse_Wheel_Scroll()
{
    return y_offset;
}

vector2 Input::Get_Mouse_Pos()
{
    return mouse_position;
}

void Input::Triggered_Reset()
{
    key_triggered.reset();
    mouse_triggered.reset();
    mouse_double_clicked.reset();
    mouse_released.reset();
}

void Input::Set_Keyboard_Input(int key, int action)
{
    if(key <= -1 || key >= GLFW_KEY_LAST)
    {
        return;
    }

    switch (action)
    {
    case GLFW_PRESS:
        key_triggered.set(key);
        key_pressed.set(key);
        key_released.reset(key);
        break;

    case GLFW_RELEASE:
        key_triggered.reset(key);
        key_pressed.reset(key);
        key_released.set(key);
        break;

    default:
        break;
    }
}

void Input::Set_Mouse_Input(int button, int action)
{
    assert(button > -1 && button < GLFW_MOUSE_BUTTON_LAST);

    switch (action)
    {
    case GLFW_PRESS:
        mouse_triggered.set(button);
        mouse_pressed.set(button);
        mouse_released.reset(button);
        break;

    case GLFW_RELEASE:
    {
        static auto before = std::chrono::system_clock::now();
        auto now = std::chrono::system_clock::now();
        double diff_ms = std::chrono::duration<double, std::milli>(now - before).count();
        before = now;

        if (diff_ms > 10 && diff_ms < 200)
        {
            mouse_double_clicked.set(button);
        }
        else
        {
            mouse_double_clicked.reset(button);
        }
        mouse_triggered.reset(button);
        mouse_pressed.reset(button);
        mouse_released.set(button);
    }
    break;

    default:
        break;
    }
}

void Input::Set_Mouse_Position(double x, double y)
{
    float w = Application::Get_Application()->Get_Window_Size().x;
    float h = Application::Get_Application()->Get_Window_Size().y;

    mouse_position.x = static_cast<float>(-(w / 2.f - x));
    mouse_position.y = static_cast<float>(h / 2.f - y);
}

void Input::Set_Mouse_Wheel(double x, double y)
{
    x_offset = x;
    y_offset = y;
}