/*
 * Author		:Minseok Sung
 * File			:Application.hpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for application.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "vector2.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Graphic.h"
#include "ObjectManager.h"
#include "Application.hpp"
#include "Component_Sprite.h"

class Application
{
private:
    Application() {}
    static Application* application;

    GLFWwindow* window;
    bool get_vsync;
    int x_pos, y_pos;
    int width, height;

    float save_dt = 0.0f;
    int FPS_frame = 0;

    vector2 window_size{};
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    std::string which_one_to_make;
    bool is_drag_and_drop_mode = false;
    Texture object1;
    Texture object2;
    Texture object3;
    Texture object4;
    Texture object5;

public:
    static Application* Get_Application();
    void Init();
    void Update(float dt);
    void Delete();
    bool IsFullScreen();
    void Toggle_Fullscreen();
    void Imgui_Init();
    void Imgui_Update();
    void Clear();
    void Save();
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    int GetFPS();

    void TurnOnMonitorVerticalSynchronization(bool enable);

    vector2 Get_Window_Size()
    {
        return window_size;
    }
};