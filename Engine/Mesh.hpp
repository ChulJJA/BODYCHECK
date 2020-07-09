/*
 * Author		:Jeesoo Kim
 * File			:Mesh.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Mesh
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Color4ub.hpp"
#include <vector2.hpp>
#include <cstddef>
#include <vector>

enum class [[nodiscard]] PointListPattern
{
    Lines, LineStrip, LineLoop, Triangles, TriangleStrip, TriangleFan
};

class [[nodiscard]] Mesh
{
public:
    std::size_t GetPointCount() const noexcept;
    vector2     GetPoint(std::size_t index) const noexcept;
    Color4ub    GetColor(std::size_t index = 0) const noexcept;
    vector2     GetTextureCoordinate(std::size_t index) const
    noexcept;
    vector2 GetCenterPoint() const noexcept;

    PointListPattern GetPointListPattern() const noexcept;
    void             SetPointListType(PointListPattern type) noexcept;

    void AddColor(Color4ub color) noexcept;
    void AddPoint(vector2 point) noexcept;
    void AddTextureCoordinate(vector2 texture_coordinate) noexcept;

    void ClearColors() noexcept;
    bool HasMoreThanOneColor() const noexcept;

    void ClearTextureCoordinates() noexcept;
    void ClearPoints() noexcept;
    void Clear() noexcept;
    std::vector<vector2>& Get_Points();

    bool& Get_Is_Moved()
    {
        return is_moved;
    }

    void SetColor();
private:
    std::vector<vector2>  points{};
    std::vector<Color4ub> colors{};
    std::vector<vector2>  textureCoordinates{};
    PointListPattern      pointListType = PointListPattern::Lines;
    bool is_moved = false;
};

namespace MESH
{
    Mesh create_circle(float radius = 1, Color4ub color = Color4ub{ 255 }, std::size_t point_count = 30) noexcept;
    Mesh create_wire_circle(float radius = 1, Color4ub color = Color4ub{ 255 },
        std::size_t point_count = 30) noexcept;
    Mesh create_box(float dimension = 1, Color4ub color = Color4ub{ 255 }) noexcept;
    Mesh create_rectangle(float width = 1, float height = 1, Color4ub color = Color4ub{ 255 }) noexcept;
    Mesh create_wire_rectangle(float width = 1, float height = 1, Color4ub color = Color4ub{ 255 }) noexcept;
    Mesh create_wire_box(float dimension = 1, Color4ub color = Color4ub{ 255 }) noexcept;
    Mesh create_line(vector2 a = { 0, 0 }, vector2 b = { 1, 0 }, Color4ub color = Color4ub{ 255 }) noexcept;
}