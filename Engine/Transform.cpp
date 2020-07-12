/*
 * Author		:Jeesoo Kim
 * File			:Transform.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Transform
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Transform.hpp"

matrix3 Transform::GetModelToWorld() const noexcept
{
    matrix3 result = MATRIX3::build_identity();

    result *= MATRIX3::build_translation(GetTranslation()) * MATRIX3::build_rotation(GetRotation()) * MATRIX3::build_scale(GetScale());

    if (parent != nullptr)
    {
        return parent->GetModelToWorld() * result;
    }
    return result;
}


matrix3 Transform::GetWorldToModel() const noexcept
{
    matrix3 result = GetModelToWorld();

    double det =
        result(0, 0) * (result(1, 1) * result(2, 2) - result(2, 1) * result(1, 2)) -
        result(0, 1) * (result(1, 0) * result(2, 2) - result(1, 2) * result(2, 0)) +
        result(0, 2) * (result(1, 0) * result(2, 1) - result(1, 1) * result(2, 0));
    double inverseDet = 1.0 / det;

    matrix3 inversedMat;

    inversedMat(0, 0) = (float)((result(1, 1) * result(2, 2) - result(2, 1) * result(1, 2)) * inverseDet);
    inversedMat(0, 1) = (float)((result(0, 2) * result(2, 1) - result(0, 1) * result(2, 2)) * inverseDet);
    inversedMat(0, 2) = (float)((result(0, 1) * result(1, 2) - result(0, 2) * result(1, 1)) * inverseDet);
    inversedMat(1, 0) = (float)((result(1, 2) * result(2, 0) - result(1, 0) * result(2, 2)) * inverseDet);
    inversedMat(1, 1) = (float)((result(0, 0) * result(2, 2) - result(0, 2) * result(2, 0)) * inverseDet);
    inversedMat(1, 2) = (float)((result(1, 0) * result(0, 2) - result(0, 0) * result(1, 2)) * inverseDet);
    inversedMat(2, 0) = (float)((result(1, 0) * result(2, 1) - result(2, 0) * result(1, 1)) * inverseDet);
    inversedMat(2, 1) = (float)((result(2, 0) * result(0, 1) - result(0, 0) * result(2, 1)) * inverseDet);
    inversedMat(2, 2) = (float)((result(0, 0) * result(1, 1) - result(1, 0) * result(0, 1)) * inverseDet);

    return inversedMat;
}

float Transform::CalculateWorldDepth() const noexcept
{
    float worldDepth = GetDepth();

    if (parent != nullptr)
    {
        worldDepth += parent->CalculateWorldDepth();
    }

    return worldDepth;
}

float Transform::GetDepth() const noexcept
{
    return depth;
}

void Transform::SetDepth(float new_depth) noexcept
{

    depth = new_depth;
}

vector2 Transform::GetTranslation() const noexcept
{
    return translation;
}

void Transform::SetTranslation(const vector2 new_translation) noexcept
{
    translation.x = new_translation.x;
    translation.y = new_translation.y;
}

void Transform::AddTranslation(const vector2& translation)
{
    this->translation.x += translation.x;
    this->translation.y += translation.y;
}

vector2 Transform::Get_Save_Translation()const noexcept
{
    return save_translation;
}
vector2 Transform::GetScale() const noexcept
{
    return scale;
}

void Transform::SetScale(const float& new_scale) noexcept
{
    scale.x = new_scale;
    scale.y = new_scale;

    //original_scale.x = new_scale;
    //original_scale.y = new_scale;
}

void Transform::SetScale(const vector2& new_scale) noexcept
{
    scale.x = new_scale.x;
    scale.y = new_scale.y;


    //original_scale.x = new_scale.x;
    //original_scale.y = new_scale.y;
}

float Transform::GetRotation() const noexcept
{
    return rotation;
}

void Transform::SetRotation(float new_rotation) noexcept
{
    rotation = new_rotation;
}

const Transform* Transform::GetParent() const noexcept
{
    return parent;
}

void Transform::SetParent(const Transform* transform_parent) noexcept
{
    parent = transform_parent;
}


