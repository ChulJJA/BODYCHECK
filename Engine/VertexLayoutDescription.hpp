/*
 * Author		:Jeesoo Kim
 * File			:VertexLayoutDescription.hpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for VertexLayoutDescription.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <vector>

class [[nodiscard]] VertexLayoutDescription
{
public:
    enum FieldType
    {
        Position2WithFloats,
        TextureCoordinates2WithFloats,
        Color4WithUnsignedBytes
    };

    constexpr VertexLayoutDescription() noexcept = default;
    VertexLayoutDescription(std::initializer_list<FieldType> fields) noexcept;


    void                                    AddField(FieldType field_type) noexcept;
    void                                    SendVertexDescriptionToOpenGL() const noexcept;
    constexpr unsigned                      GetVertexSize() const noexcept { return vertexSize; }
    constexpr const std::vector<FieldType>& GetFieldTypes() const noexcept { return fields; }

private:
    struct field_description
    {
        unsigned elementType = 0;
        unsigned elementCount = 0;
        unsigned sizeInBytes = 0;
        bool     shouldNormalize = false;
    };
    unsigned                       vertexSize = 0;
    std::vector<field_description> vertexDescription{};
    std::vector<FieldType>         fields{};
};