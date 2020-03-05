/*
 * Author		:Jeesoo Kim
 * File			:VertexLayoutDescription.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for layout description which pass to shader code.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Mesh.hpp"
#include "VertexLayoutDescription.hpp"
#include "Application.hpp"
#include <cassert>

VertexLayoutDescription::VertexLayoutDescription(std::initializer_list<FieldType> fields) noexcept
{
    std::initializer_list<FieldType>::iterator it;
    for (it = fields.begin(); it != fields.end(); it++)
    {
        AddField(*it);
    }
}
void VertexLayoutDescription::AddField(FieldType field_type) noexcept
{
    field_description description = { 0,0,0,0 };
    if (field_type == FieldType::Position2WithFloats)
    {
        description.elementType = GL_FLOAT;
        description.elementCount = 2;
        description.sizeInBytes = sizeof(GL_FLOAT) * 2;
    }
    else if (field_type == FieldType::TextureCoordinates2WithFloats)
    {
        description.sizeInBytes = sizeof(GL_FLOAT) * 2;
        description.elementCount = 2;
        description.elementType = GL_FLOAT;
    }
    else if (field_type == FieldType::Color4WithUnsignedBytes)
    {
        description.sizeInBytes = sizeof(unsigned char) * 4;
        description.elementCount = 4;
        description.elementType = GL_UNSIGNED_BYTE;
        description.shouldNormalize = true;
    }
    vertexSize += description.sizeInBytes;
    fields.push_back(field_type);
    vertexDescription.push_back(description);
}

void VertexLayoutDescription::SendVertexDescriptionToOpenGL() const noexcept
{
    GLintptr offset = 0;

    for (int i = 0; i < vertexDescription.size(); i++)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,
            vertexDescription[i].elementCount,
            vertexDescription[i].elementType,
            vertexDescription[i].shouldNormalize,
            vertexSize,
            (GLvoid*)offset);
        offset += vertexDescription[i].sizeInBytes;
    }
}