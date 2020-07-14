/*
 * Author		:Sangmin Kim
 * File			:Application.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Application
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Application.hpp"
#include <iostream>
#include "vector2.hpp"
#include "Input.h"
#include <sstream>
#include "ObjectManager.h"
#include "Message_Manager.h"
#include "Component_Sprite.h"
#include <fstream>
#include "Physics.h"
#include "Component_Hpbar.h"
#include "StateManager.h"
#include "State.h"
#include "Engine.hpp"
using namespace std;
Application* Application::application = nullptr;
StateManager* state = nullptr;
namespace
{
    void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void    cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    void    mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void    scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    bool    is_full = false;
    void    window_focus_callback(GLFWwindow* window, int focused);
}


void Application::Init()
{
    if (!glfwInit())
    {
        glfwTerminate();
        return;
    }

    GLenum glew_err_check;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    window = glfwCreateWindow(1280, 720, "BodyCheck", nullptr, nullptr);
    
    glfwMakeContextCurrent(window);

    if (!window)
    {
        glfwTerminate();
        return;
    }
    glew_err_check = glewInit();

    if (glew_err_check != GLEW_NO_ERROR)
    {
        glfwTerminate();
        return;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    glfwSetWindowMonitor(window, nullptr,
        200,
        200,
        static_cast<int>(1280),
        static_cast<int>(720), 0);
    window_size = { 1280, 720 };
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSwapInterval(true);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    object1.LoadFromPNG("../sprite/HP.png");
    object2.LoadFromPNG("../sprite/HP.png");
    object3.LoadFromPNG("../sprite/HP.png");
    object4.LoadFromPNG("../sprite/HP.png");
    object5.LoadFromPNG("../sprite/HP.png");
    Toggle_Fullscreen();

    state = StateManager::GetStateManager();
}

void Application::Update(float dt)
{
    input.Triggered_Reset();

    glfwSwapBuffers(window);
    glfwPollEvents();

    int w, h;
    glfwGetWindowSize(window, &w, &h);
    window_size.width = (float)w;
    window_size.height = (float)h;


    if (input.Is_Key_Triggered(GLFW_KEY_K))
    {
        Save();
    }
    if (input.Is_Key_Triggered(GLFW_KEY_R))
    {
        Clear();
    }

    
    save_dt += dt;
    if (save_dt >= 1.0f)
    {
        std::stringstream title;
        title << "BodyCheck" << " " << " [" << FPS_frame << " FPS]";
        glfwSetWindowTitle(window, title.str().c_str());
        FPS_frame = 0;
        save_dt = 0;
    }
    FPS_frame++;

    glfwSetWindowFocusCallback(window, window_focus_callback);
}

void Application::Delete()
{

}

void Application::Save()
{
}

void Application::Clear()
{
}
bool Application::IsFullScreen()
{
    return glfwGetWindowMonitor(window);
}

int Application::GetFPS()
{
    return FPS_frame;
}

void Application::TurnOnMonitorVerticalSynchronization(bool enable)
{
    get_vsync = enable;
    glfwSwapInterval(enable);
}

void Application::Toggle_Fullscreen()
{
    if (!IsFullScreen())
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        glfwGetWindowPos(window, &x_pos, &y_pos);
        glfwGetWindowSize(window, &width, &height);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        glViewport(0, 0, mode->width, mode->height);
        TurnOnMonitorVerticalSynchronization(get_vsync);
    }
    else
    {
        glfwSetWindowMonitor(window, nullptr, x_pos, y_pos, width, height, 0);
        glViewport(0, 0, width, height);
    }
    glfwSwapBuffers(window);
    glfwSwapInterval(true);
}

Application* Application::Get_Application()
{
    if (application == nullptr)
        application = new Application;

    return application;
}

namespace
{
    void mouse_button_callback(GLFWwindow* /*window*/, int button, int action, int /*mods*/)
    {
        input.Set_Mouse_Input(button, action);
    }
    void cursor_position_callback(GLFWwindow* /*window*/, double xpos, double ypos)
    {
        input.Set_Mouse_Position(xpos, ypos);
    }
    void key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
    {
        input.Set_Keyboard_Input(key, action);
    }
    void scroll_callback(GLFWwindow* /*window*/, double xoffset, double yoffset)
    {
        input.Set_Mouse_Wheel(xoffset, yoffset);
    }
    void window_focus_callback(GLFWwindow* window, int focused)
    {
        if (!focused && state->GetCurrentState()->GetStateInfo() == GameState::Game)
        {
            state->GetCurrentState()->is_pause = true;
            sound.StopAllSFX();
        }
        else if(focused && state->GetCurrentState()->GetStateInfo() == GameState::Game)
        {
            state->GetCurrentState()->is_pause = false;
        }
    }
}