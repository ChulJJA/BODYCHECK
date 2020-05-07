/*
 * Author		:Minseok Sung
 * File			:Applicaion.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for creating window, getting input.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
using namespace std;
Application* Application::application = nullptr;

namespace
{
    void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void    cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    void    mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void    scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    bool    is_full = false;
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

    window = glfwCreateWindow(1280, 720, "sangministhebest", nullptr, nullptr);

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

    object1.LoadFromPNG("../sprite/HP.png");
    object2.LoadFromPNG("../sprite/HP.png");
    object3.LoadFromPNG("../sprite/HP.png");
    object4.LoadFromPNG("../sprite/HP.png");
    object5.LoadFromPNG("../sprite/HP.png");

}

//void Application::Imgui_Init()
//{
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    ImGui::StyleColorsDark();
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    const char* glsl_version = "#version 130";
//    ImGui_ImplOpenGL3_Init(glsl_version);
//}

void Application::Update(float dt)
{
    input.Triggered_Reset();

    glfwSwapBuffers(window);
    glfwPollEvents();

    int w, h;
    glfwGetWindowSize(window, &w, &h);
    window_size.width = (float)w;
    window_size.height = (float)h;
    GLFWgamepadstate state;

    if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
    {
        if (state.buttons[GLFW_GAMEPAD_BUTTON_B])
        {
            Toggle_Fullscreen();
        }
    }
    if (input.Is_Key_Triggered(GLFW_KEY_F))
    {
        Toggle_Fullscreen();
    }

    if (input.Is_Key_Triggered(GLFW_KEY_K))
    {
        Save();
    }
    if (input.Is_Key_Triggered(GLFW_KEY_R))
    {
        Clear();
    }


    int status = glfwJoystickPresent(GLFW_JOYSTICK_1);

    //if (status == true)
	if (status)
    {
        int axesCount;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    }
    
    save_dt += dt;
    if (save_dt >= 1.0f)
    {
        std::stringstream title;
        title << "DoubleCheck" << " " << " [" << FPS_frame << " FPS]";
        glfwSetWindowTitle(window, title.str().c_str());
        FPS_frame = 0;
        save_dt = 0;
    }
    FPS_frame++;
    
    if (input.Is_Key_Triggered(GLFW_KEY_ESCAPE))
    {
        exit(0);
    }
    if (input.Is_Mouse_Double_Clicked(GLFW_MOUSE_BUTTON_LEFT))
    {
        std::cout << "aaa" << std::endl;
    }
}

//
//
//void Application::Imgui_Update()
//{
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplGlfw_NewFrame();
//    ImGui::NewFrame();
//    static vector2 origin_mouse_pos;
//    ImGui::Begin("IMGUI");
//
//    for (int i = 0; i < ObjectManager::GetObjectManager()->GetObjectManagerContainer().size(); i++)
//    {
//        Object* this_obj = ObjectManager::GetObjectManager()->GetObjectManagerContainer_Value()[i].get();
//        this_obj->Get_Is_Debugmode();
//        if (ImGui::TreeNode(this_obj->Get_Name().c_str()))
//        {
//            ImGui::TextWrapped("IMGUI");
//            ImGui::SliderFloat("translation_x", &this_obj->GetTransform().GetTranslation_Reference().x, -1.0f, 150.0f);
//            ImGui::SliderFloat("translation_y", &this_obj->GetTransform().GetTranslation_Reference().y, -1.0f, 1.0f);
//            if (ImGui::SliderFloat("scale_x", &this_obj->GetTransform().GetScale_Reference().x, -2.0f, 2.0f))
//            {
//                if (this_obj->GetComponentByTemplate<Hp_Bar>() != nullptr)
//                {
//                    this_obj->GetComponentByTemplate<Hp_Bar>()->Get_Set_Offset() = 0;
//                }
//            }
//            ImGui::SliderFloat("scale_y", &this_obj->GetTransform().GetScale_Reference().y, -2.0f, 2.0f);
//
//            if (this_obj->GetComponentByTemplate<Physics>() != nullptr)
//            {
//                ImGui::SliderFloat("acceleration_x", &this_obj->GetComponentByTemplate<Physics>()->GetAcceleration_Reference().x, -2.0f, 2.0f);
//                ImGui::SliderFloat("acceleration_y", &this_obj->GetComponentByTemplate<Physics>()->GetAcceleration_Reference().y, -2.0f, 2.0f);
//            }
//            if (ImGui::InputText("name", this_obj->name_buf, 64, ImGuiInputTextFlags_EnterReturnsTrue))
//            {
//                this_obj->Set_Name(this_obj->name_buf);
//            }
//
//            ImGui::Checkbox("select", &this_obj->Get_Is_Selected());
//
//            if (ImGui::Button("Delete Object"))
//            {
//                this_obj->SetDeadCondition(true);
//            }
//
//            if (this_obj->Get_Is_Selected())
//            {
//                if (input.Is_Mouse_Pressed(GLFW_MOUSE_BUTTON_RIGHT))
//                {
//                    this_obj->GetTransform().SetTranslation(input.Get_Mouse_Pos());
//
//                    vector3 converting;
//                    vector2 mouse = input.Get_Mouse_Pos();
//
//                    converting.x = input.Get_Mouse_Pos().x;
//                    converting.y = input.Get_Mouse_Pos().y;
//                    converting.z = 1.0f;
//
//                    converting = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform() * converting;
//                    converting = Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera() * converting;
//                    converting.x *= 640;
//                    converting.y *= 360;
//
//                    vector2 result;
//                    result.x = converting.x;
//                    result.y = converting.y;
//
//                    this_obj->Get_Is_Need_Convert_Translation() = true;
//                    this_obj->Get_Convert_Translation() = { mouse.x - result.x, mouse.y - result.y };
//
//                    float zoom = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetZoom();
//                    float zoom_converted = zoom - 1.f;
//                    float zoom_finish = 1.f - zoom_converted;
//                    vector2 converted = { mouse.x - result.x, mouse.y - result.y };
//                    this_obj->GetMesh().Get_Is_Moved() = true;
//                    this_obj->GetTransform().SetTranslation({ mouse.x + (zoom_finish * (mouse.x - result.x)), mouse.y + (zoom_finish * (mouse.y - result.y)) });
//                }
//            }
//
//            if (ImGui::Checkbox("Component_physics", &this_obj->Get_Component_Info_Reference().component_info_physics))
//            {
//                if (this_obj->Get_Component_Info_Reference().component_info_physics)
//                {
//                    this_obj->AddComponent(new Physics());
//                }
//            }
//            if (ImGui::Checkbox("Component_sprite", &this_obj->Get_Component_Info_Reference().component_info_sprite))
//            {
//                if (this_obj->Get_Component_Info_Reference().component_info_sprite)
//                {
//                }
//            }
//
//            ImGui::TreePop();
//        }
//    }
//    static const char* names[5] = { "JISOO", "Chulseong", "Sangmin", "min seok" , "Su whan" };
//    ImGuiIO& io = ImGui::GetIO();
//
//    float my_tex_w = (float)io.Fonts->TexWidth;
//    float my_tex_h = (float)io.Fonts->TexHeight;
//
//    if (ImGui::TreeNode("Drag and Drop"))
//    {
//        for (int i = 0; i < IM_ARRAYSIZE(names); i++)
//        {
//            ImGui::PushID(i);
//            if ((i % 3) != 0)
//                ImGui::SameLine();
//            int frame_padding = -1 + i;     // -1 = uses default padding
//
//            if (i == 0)
//            {
//                ImGui::ImageButton(reinterpret_cast<void*>(object1.GetTextureHandle()), ImVec2(100, 100), ImVec2(0, 0));
//            }
//            else if (i == 1)
//            {
//                ImGui::ImageButton(reinterpret_cast<void*>(object2.GetTextureHandle()), ImVec2(100, 100), ImVec2(0, 0));
//            }
//            else if (i == 2)
//            {
//                ImGui::ImageButton(reinterpret_cast<void*>(object3.GetTextureHandle()), ImVec2(100, 100), ImVec2(0, 0));
//            }
//            else if (i == 3)
//            {
//                ImGui::ImageButton(reinterpret_cast<void*>(object4.GetTextureHandle()), ImVec2(100, 100), ImVec2(0, 0));
//            }
//            else if (i == 4)
//            {
//                ImGui::ImageButton(reinterpret_cast<void*>(object5.GetTextureHandle()), ImVec2(100, 100), ImVec2(0, 0));
//            }
//
//            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
//            {
//                ImGui::SetDragDropPayload("DND_DEMO_CELL", &i, sizeof(int));        // Set payload to carry the index of our item (could be anything)
//                ImGui::EndDragDropSource();
//                which_one_to_make = names[i];
//                is_drag_and_drop_mode = true;
//            }
//            if (ImGui::BeginDragDropTarget())
//            {
//                ImGui::EndDragDropTarget();
//            }
//            ImGui::PopID();
//        }
//        ImGui::Unindent();
//        ImGui::TreePop();
//    }
//    if (is_drag_and_drop_mode)
//    {
//        if (input.Is_Mouse_Released(GLFW_MOUSE_BUTTON_LEFT))
//        {
//            vector2 this_pos = input.Get_Mouse_Pos();
//
//            Object* new_obj = new Object();
//
//            if (which_one_to_make == names[0])
//            {
//                new_obj->Set_Name(names[0]);
//                new_obj->AddComponent(new Sprite(new_obj, "../sprite/dicksean.png", { 60,60 }));
//            }
//            else if (which_one_to_make == names[1])
//            {
//                new_obj->Set_Name(names[1]);
//                new_obj->AddComponent(new Sprite(new_obj, "../sprite/kingchulseong.png", { 60,60 }));
//            }
//            else if (which_one_to_make == names[2])
//            {
//                new_obj->Set_Name(names[2]);
//                new_obj->AddComponent(new Sprite(new_obj, "../sprite/waterpunch.png", { 60,60 }));
//            }
//            else if (which_one_to_make == names[3])
//            {
//                new_obj->Set_Name(names[3]);
//                new_obj->AddComponent(new Sprite(new_obj, "../sprite/temp.png", { 60,60 }));
//            }
//            else if (which_one_to_make == names[4])
//            {
//                new_obj->Set_Name(names[4]);
//                new_obj->AddComponent(new Sprite(new_obj, "../sprite/maknae.png", { 60,60 }));
//            }
//            new_obj->SetTranslation(this_pos);
//            new_obj->AddComponent(new Physics);
//            new_obj->GetMesh().Get_Is_Moved() = true;
//            ObjectManager::GetObjectManager()->AddObject(new_obj);
//
//            is_drag_and_drop_mode = false;
//        }
//    }
//
//    ImGui::End();
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//}

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
}