/*
 * Author		:Sangmin Kim
 * File			:Application.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Application
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vector2.hpp"
#include "ObjectManager.h"
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
    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
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
    void Clear();
    void Save();
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    int GetFPS();
	GLFWwindow* Get_Window()
	{
		return window;
	}

    void TurnOnMonitorVerticalSynchronization(bool enable);

    vector2 Get_Window_Size()
    {
        return window_size;
    }
};