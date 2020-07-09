/*
 * Author		:Sangmin Kim
 * File			:Vertices.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Vertices
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Mesh.hpp"
#include "VertexLayoutDescription.hpp"
#include "Vertices.hpp"
#include "Application.hpp"
#include <cassert>
#include <mutex>

std::mutex mutex_;

Vertices::Vertices(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept
{
    InitializeWithMeshAndLayout(mesh, vertex_layout);
}

Vertices::~Vertices() noexcept
{
    DeleteVerticesOnGPU();
}

Vertices::Vertices(Vertices&& other) noexcept
{
    verticesHandle = other.verticesHandle;
    dataBufferHandle = other.dataBufferHandle;
    verticesCount = other.verticesCount;
    verticesListPattern = other.verticesListPattern;
    layout = other.layout;
    bufferVertexCapacity = other.bufferVertexCapacity;
    other.verticesHandle = 0;
    other.dataBufferHandle = 0;
    other.verticesCount = 0;
    other.bufferVertexCapacity = 0;
}

void Vertices::operator=(Vertices&& other) noexcept
{
    if (this == &other)
        return;
    DeleteVerticesOnGPU();
    verticesHandle = other.verticesHandle;
    dataBufferHandle = other.dataBufferHandle;
    verticesCount = other.verticesCount;
    verticesListPattern = other.verticesListPattern;
    layout = other.layout;
    bufferVertexCapacity = other.bufferVertexCapacity;
    other.verticesHandle = 0;
    other.dataBufferHandle = 0;
    other.verticesCount = 0;
    other.bufferVertexCapacity = 0;
}

void Vertices::InitializeWithMeshAndLayout(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept
{
    switch (mesh.GetPointListPattern())
    {
    case PointListPattern::Lines:
        verticesListPattern = GL_LINES;
        break;
    case PointListPattern::LineStrip:
        verticesListPattern = GL_LINE_STRIP;
        break;
    case PointListPattern::LineLoop:
        verticesListPattern = GL_LINE_LOOP;
        break;
    case PointListPattern::Triangles:
        verticesListPattern = GL_TRIANGLES;
        break;
    case PointListPattern::TriangleStrip:
        verticesListPattern = GL_TRIANGLE_STRIP;
        break;
    case PointListPattern::TriangleFan:
        verticesListPattern = GL_TRIANGLE_FAN;
        break;
    }

    glGenVertexArrays(1, &verticesHandle);
    glGenBuffers(1, &dataBufferHandle);
    Select(*this);
    glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle);
    bufferVertexCapacity = static_cast<int>(mesh.GetPointCount());
    verticesCount = static_cast<int>(mesh.GetPointCount());
    layout = vertex_layout;
    glBufferData(GL_ARRAY_BUFFER, bufferVertexCapacity * vertex_layout.GetVertexSize(), NULL, GL_STATIC_DRAW);
    vertex_layout.SendVertexDescriptionToOpenGL();
    WriteMeshDataToVertexBuffer(mesh);

}

void Vertices::UpdateVerticesFromMesh(const Mesh& mesh)
{
    if (mesh.GetPointCount() < bufferVertexCapacity)
    {
        verticesCount = static_cast<unsigned int>(mesh.GetPointCount());
        WriteMeshDataToVertexBuffer(mesh);
    }
    else
    {
        verticesCount = static_cast<int>(mesh.GetPointCount());
        bufferVertexCapacity = static_cast<int>((mesh.GetPointCount()));
        DeleteVerticesOnGPU();
        glGenVertexArrays(1, &verticesHandle);
        glGenBuffers(1, &dataBufferHandle);
        Select(*this);
        glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle);
        layout.SendVertexDescriptionToOpenGL();
        glBufferData(GL_ARRAY_BUFFER, bufferVertexCapacity * layout.GetVertexSize(), NULL, GL_STATIC_DRAW);
        WriteMeshDataToVertexBuffer(mesh);
    }
}

void Vertices::Select(const Vertices& vertices)
{
    glBindVertexArray(vertices.verticesHandle);
}

void Vertices::SelectNothing()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Vertices::DeleteVerticesOnGPU() noexcept
{
    glDeleteVertexArrays(1, &verticesHandle);
    glDeleteBuffers(1, &dataBufferHandle);
}

void Vertices::WriteMeshDataToVertexBuffer(const Mesh& mesh) const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle);
    Select(*this);
    void* ptr_buffer;
    int   buffer_offset = 0;
    std::vector<VertexLayoutDescription::FieldType> temp_field = layout.GetFieldTypes();
    vector2 temp_point, temp_text;
    Color4ub temp_color;
    ptr_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    for (int i = 0; i < mesh.GetPointCount(); i++)
    {
        for (int j = 0; j < temp_field.size(); j++)
        {
            switch (temp_field[j])
            {
            case VertexLayoutDescription::Color4WithUnsignedBytes:
                temp_color = mesh.GetColor(i);
                std::memcpy(reinterpret_cast<char*>(ptr_buffer) + buffer_offset, &temp_color, sizeof(temp_color));
                buffer_offset += sizeof(Color4ub);
                break;
            case VertexLayoutDescription::Position2WithFloats:
                temp_point = mesh.GetPoint(i);
                std::memcpy(reinterpret_cast<char*>(ptr_buffer) + buffer_offset, &temp_point, sizeof(temp_point));
                buffer_offset += sizeof(vector2);
                break;
            case VertexLayoutDescription::TextureCoordinates2WithFloats:
                temp_text = mesh.GetTextureCoordinate(i);
                std::memcpy(reinterpret_cast<char*>(ptr_buffer) + buffer_offset, &temp_text, sizeof(temp_text));
                buffer_offset += sizeof(vector2);
                break;
            }
        }
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    SelectNothing();
}