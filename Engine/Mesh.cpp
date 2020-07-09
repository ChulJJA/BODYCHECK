/*
 * Author		:Jeesoo Kim
 * File			:Mesh.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Mesh
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Mesh.hpp"
#include "angles.hpp"
#include <cmath>

#define DIVIDE_2_FLOAT 2.0f

namespace MESH
{
    void Helper_AddText(Mesh& mesh)
    {
        mesh.AddTextureCoordinate({ 0, 1 });
        mesh.AddTextureCoordinate({ 0, 0 });
        mesh.AddTextureCoordinate({ 1, 0 });
        mesh.AddTextureCoordinate({ 1, 1 });
    }
    void Helper_Addpoint(float& width, float& height, Mesh& mesh)
    {
        const float width_value = width / DIVIDE_2_FLOAT;
        const float height_value = height / DIVIDE_2_FLOAT;
        mesh.AddPoint({ -width_value , -height_value });
        mesh.AddPoint({ -width_value , height_value });
        mesh.AddPoint({ width_value , height_value });
        mesh.AddPoint({ width_value , -height_value });
    }
    void Helper_Addpoint(float& dimension, Mesh& mesh)
    {
        const float value = dimension / DIVIDE_2_FLOAT;
        mesh.AddPoint({ -value, -value });
        mesh.AddPoint({ -value, value });
        mesh.AddPoint({ value, value });
        mesh.AddPoint({ value,-value });
    }
    void Helper_Addpoint_Circle(std::size_t& point_count, Mesh& mesh, float& radius)
    {
        float theta;
        for (int i = 1; i <= point_count + 1; i++)
        {
            theta = (TWO_PI * i) / static_cast<float>(point_count);
            mesh.AddPoint({ (radius * cosf(theta)),(radius * sinf(theta)) });
        }
    }
    Mesh create_circle(float radius, Color4ub color, std::size_t point_count) noexcept
    {
        Mesh temp_mesh;
        const vector2 origin = { 0, 0 };
        temp_mesh.AddPoint(origin);
        temp_mesh.AddColor(color);
        temp_mesh.SetPointListType(PointListPattern::TriangleFan);
        Helper_Addpoint_Circle(point_count, temp_mesh, radius);

        return temp_mesh;
    }

    Mesh create_wire_circle(float radius, Color4ub color, std::size_t point_count) noexcept
    {
        Mesh temp_mesh;
        temp_mesh.SetPointListType(PointListPattern::LineLoop);
        temp_mesh.AddColor(color);
        Helper_Addpoint_Circle(point_count, temp_mesh, radius);

        return temp_mesh;
    }

    Mesh create_box(float dimension, Color4ub color) noexcept
    {
        Mesh temp_mesh;
        temp_mesh.SetPointListType(PointListPattern::TriangleFan);
        temp_mesh.AddColor(color);
        Helper_Addpoint(dimension, temp_mesh);
        Helper_AddText(temp_mesh);

        return temp_mesh;
    }

    Mesh create_rectangle(float width, float height, Color4ub color) noexcept
    {
        Mesh temp_mesh;
        temp_mesh.SetPointListType(PointListPattern::TriangleFan);
        Helper_Addpoint(width, height, temp_mesh);
        Helper_AddText(temp_mesh);
        temp_mesh.AddColor(color);

        return temp_mesh;
    }

    Mesh create_wire_rectangle(float width, float height, Color4ub color) noexcept
    {
        Mesh temp_mesh;
        temp_mesh.SetPointListType(PointListPattern::LineLoop);
        Helper_Addpoint(width, height, temp_mesh);
        temp_mesh.AddColor(color);
        Helper_AddText(temp_mesh);

        return temp_mesh;
    }

    Mesh create_wire_box(float dimension, Color4ub color) noexcept
    {
        Mesh temp_mesh;
        temp_mesh.SetPointListType(PointListPattern::LineLoop);
        Helper_Addpoint(dimension, temp_mesh);
        temp_mesh.AddColor(color);
        Helper_AddText(temp_mesh);

        return temp_mesh;
    }

    Mesh create_line(vector2 a, vector2 b, Color4ub color) noexcept
    {
        Mesh temp_mesh;
        temp_mesh.SetPointListType(PointListPattern::Lines);
        temp_mesh.AddPoint(a);
        temp_mesh.AddColor(color);
        temp_mesh.AddPoint(b);

        return temp_mesh;
    }
}

std::size_t Mesh::GetPointCount() const noexcept { return points.size(); }

vector2 Mesh::GetPoint(std::size_t index) const noexcept
{
    if (index >= points.size())
    {
        return points.back();
    }
    return points[index];
}

Color4ub Mesh::GetColor(std::size_t index) const noexcept
{
    if (colors.empty())
    {
        return { 0, 0, 0 };
    }
    if (index >= colors.size())
    {
        return colors.back();
    }
    if (index >= 0 && GetPointCount())
    {
        return colors.at(index);
    }
    return { 0, 0, 0 };
}

vector2 Mesh::GetTextureCoordinate(std::size_t index) const noexcept
{
    if (textureCoordinates.empty())
    {
        return { 0, 0 };
    }
    if (index >= textureCoordinates.size())
    {
        return textureCoordinates.back();
    }
    if (index >= 0 && index < GetPointCount())
    {
        return textureCoordinates[index];
    }
    return { 0, 0 };
}

vector2 Mesh::GetCenterPoint() const noexcept
{
    const int mid_point = static_cast<int>(GetPointCount() / 2);

    const vector2 center_point = (points.at(0) + points.at(mid_point)) / 2.f;

    return center_point;
}

PointListPattern Mesh::GetPointListPattern() const noexcept { return pointListType; }

void Mesh::SetPointListType(PointListPattern type) noexcept { pointListType = type; }

void Mesh::AddColor(Color4ub color) noexcept { colors.push_back(color); }

void Mesh::AddPoint(vector2 point) noexcept { points.push_back(point); }

void Mesh::AddTextureCoordinate(vector2 texture_coordinate) noexcept
{
    textureCoordinates.push_back(texture_coordinate);
}

void Mesh::ClearColors() noexcept { colors.clear(); }

bool Mesh::HasMoreThanOneColor() const noexcept
{
    return colors.size() > 1;
}

void Mesh::ClearTextureCoordinates() noexcept
{
    textureCoordinates.clear();
}

void Mesh::ClearPoints() noexcept
{
    points.clear();
}

void Mesh::Clear() noexcept
{
    ClearColors();
    ClearPoints();
    ClearTextureCoordinates();
}

std::vector<vector2>& Mesh::Get_Points()
{
    return points;
}