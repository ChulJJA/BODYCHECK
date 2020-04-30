/*
 * Author		:Jeesoo Kim
 * File			:View.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for View.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Camera.hpp"
#include "CameraView.hpp"
#include <vector>

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
	
public:
    void Init();
    void Update(float dt);

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
    void Active_Screen_Shake(float force);
};