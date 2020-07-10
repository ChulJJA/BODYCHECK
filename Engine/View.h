/*
 * Author		:Jeesoo Kim
 * File			:View.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for View
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Camera.hpp"
#include "CameraView.hpp"
#include <vector>

class Object;

class View
{
public:
    enum class Shake_Status
    {
	    None,
    	To_Left,
    	To_Right,
    	To_Up,
    	To_Down,
    	Done,
    };
private:

    Camera camera{};
    CameraView camera_view{};
    matrix3 ndc_matrix;
    std::vector<vector2> player_pos;
    std::vector<float> x_sorted, y_sorted;
    vector2 center, distance;
    Shake_Status status = Shake_Status::None;
    float force = 10.f;
    int shake_num;
    bool is_zoom_end = false;
	
public:
    void Init();
    void Update(float dt);
    void Set_Is_Zoom_End_False()
    {
        is_zoom_end = false;
    }
    Camera& Get_Camera()
    {
        return camera;
    }
    CameraView& Get_Camera_View()
    {
        return camera_view;
    }
    matrix3 Get_Ndc_Matrix()
    {
        return ndc_matrix;
    }
    void Convert_Cam_Zoom();
    void Screen_Shake();
	Shake_Status& Get_Shake_Status()
	{
        return status;
	}
	float& Get_Force()
	{
        return force;
	}
    void Win_Zoom(float dt);
    Object* win_player = nullptr;
    bool is_ended = false;
    void Active_Screen_Shake(float force, int how_many = 1);

    float setting_zoom = 0.35f;
};