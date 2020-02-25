/*
 * Author		:Jeesoo Kim
 * File			:Vertices.hpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Vertices.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "VertexLayoutDescription.hpp"

class Mesh;

class [[nodiscard]] Vertices
{
public:
    Vertices() noexcept = default;
    Vertices(const Mesh & mesh, const VertexLayoutDescription & vertex_layout) noexcept;
    ~Vertices() noexcept;
    Vertices(Vertices && other) noexcept;
    void operator=(Vertices && other) noexcept;

    void InitializeWithMeshAndLayout(const Mesh & mesh, const VertexLayoutDescription & vertex_layout) noexcept;
    void UpdateVerticesFromMesh(const Mesh & mesh);

    static void        Select(const Vertices & vertices);
    constexpr unsigned GetVerticesListPattern() const noexcept { return verticesListPattern; }
    constexpr int      GetVerticesCount() const noexcept { return verticesCount; }
    static void        SelectNothing();

public:
    Vertices(const Vertices & other) = delete;
    void operator=(const Vertices & other) = delete;

private:
    void DeleteVerticesOnGPU() noexcept;
    void WriteMeshDataToVertexBuffer(const Mesh & mesh) const noexcept;

private:
    unsigned int            verticesHandle = 0;
    unsigned int            dataBufferHandle = 0;
    int                     verticesCount = 0;
    unsigned int            verticesListPattern = 0;
    int                     bufferVertexCapacity = 0;
    VertexLayoutDescription layout{};
};