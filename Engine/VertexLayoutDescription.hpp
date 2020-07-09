/*
 * Author		:Jeesoo Kim
 * File			:VertexLayoutDescription.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Vertex Layout Description
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
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