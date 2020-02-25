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
private:
    Camera camera{};
    CameraView camera_view{};
    matrix3 ndc_matrix;
    std::vector<vector2> player_pos;
    std::vector<float> x_sorted, y_sorted;
    vector2 center, distance;
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
};