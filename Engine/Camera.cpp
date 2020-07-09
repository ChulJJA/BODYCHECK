/*
 * Author		:Sangmin Kim
 * File			:Camera.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Camera
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Camera.hpp"

matrix3 Helper_build_world_to_camera(vector2 center_vec, vector2 up_vec, vector2 right_vec)
{
    return{
        right_vec.x,right_vec.y, (-right_vec.x * center_vec.x) + (-right_vec.y * center_vec.y),
        up_vec.x, up_vec.y, (-up_vec.x * center_vec.x) + (-up_vec.y * center_vec.y),
        0,0,1
    };
}

matrix3 helper_inverse_camera(matrix3 model_to_world)
{
    double det = model_to_world(0, 0) * (model_to_world(1, 1) * model_to_world(2, 2) - model_to_world(2, 1) * model_to_world(1, 2)) -
        model_to_world(0, 1) * (model_to_world(1, 0) * model_to_world(2, 2) - model_to_world(1, 2) * model_to_world(2, 0)) +
        model_to_world(0, 2) * (model_to_world(1, 0) * model_to_world(2, 1) - model_to_world(1, 1) * model_to_world(2, 0));

    double invdet = 1 / det;

    matrix3 minv;
    minv(0, 0) = static_cast<float>((model_to_world(1, 1) * model_to_world(2, 2) - model_to_world(2, 1) * model_to_world(1, 2)) * invdet);
    minv(0, 1) = static_cast<float>((model_to_world(0, 2) * model_to_world(2, 1) - model_to_world(0, 1) * model_to_world(2, 2)) * invdet);
    minv(0, 2) = static_cast<float>((model_to_world(0, 1) * model_to_world(1, 2) - model_to_world(0, 2) * model_to_world(1, 1)) * invdet);
    minv(1, 0) = static_cast<float>((model_to_world(1, 2) * model_to_world(2, 0) - model_to_world(1, 0) * model_to_world(2, 2)) * invdet);
    minv(1, 1) = static_cast<float>((model_to_world(0, 0) * model_to_world(2, 2) - model_to_world(0, 2) * model_to_world(2, 0)) * invdet);
    minv(1, 2) = static_cast<float>((model_to_world(1, 0) * model_to_world(0, 2) - model_to_world(0, 0) * model_to_world(1, 2)) * invdet);
    minv(2, 0) = static_cast<float>((model_to_world(1, 0) * model_to_world(2, 1) - model_to_world(2, 0) * model_to_world(1, 1)) * invdet);
    minv(2, 1) = static_cast<float>((model_to_world(2, 0) * model_to_world(0, 1) - model_to_world(0, 0) * model_to_world(2, 1)) * invdet);
    minv(2, 2) = static_cast<float>((model_to_world(0, 0) * model_to_world(1, 1) - model_to_world(1, 0) * model_to_world(0, 1)) * invdet);

    return minv;
}
Camera::Camera(vector2 camera_center, vector2 camera_up) noexcept
{
    center = camera_center;
    up = camera_up;
    right = -perpendicular_to(up);

}

void Camera::ResetUp(vector2 camera_up) noexcept
{
    up = camera_up;
    right = -perpendicular_to(up);
}

void Camera::MoveUp(float distance) noexcept
{
    SetCenter({ center.x, center.y + distance });
}

void Camera::MoveRight(float distance) noexcept
{
    SetCenter({ center.x + distance, center.y });
}

void Camera::Rotate(float angle_radians) noexcept
{
    up = rotate_by(angle_radians, up);
    right = rotate_by(angle_radians, right);
}

matrix3 Camera::CameraToWorld() const noexcept
{
    matrix3 camera_to_world_matrix = WorldToCamera();
    camera_to_world_matrix = helper_inverse_camera(camera_to_world_matrix);

    return camera_to_world_matrix;
}

matrix3 Camera::WorldToCamera() const noexcept
{
    matrix3 world_to_camera_matrix = Helper_build_world_to_camera(center, up, right);

    world_to_camera_matrix = MATRIX3::transpose(world_to_camera_matrix);

    return world_to_camera_matrix;
}