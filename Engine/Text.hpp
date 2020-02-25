/*
 * Author		:Jeesoo Kim
 * File			:Text.hpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Text.cpp
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include <string>
#include <unordered_map>
#include "Vertices.hpp"
#include "Texture.hpp"
#include "Component_Sprite.h"
#include "CameraView.hpp"
#include "BitmapFont.hpp"

class CameraView;
class Transform;
class BitmapFont;
class Color4f;

class [[nodiscard]] Text
{
public:
    Text() noexcept = default;
    Text(std::wstring text_string, const BitmapFont & text_font) noexcept;

    std::vector<std::pair<Vertices*, const Texture*>> GetVerticesWithMatchingTextures() const noexcept;
    std::wstring                                            GetString() const noexcept;
    void                                                    SetString(const std::wstring & text_string) noexcept;
    const BitmapFont* GetFont() const noexcept;
    void                                                    SetFont(const BitmapFont & text_font) noexcept;

private:
    void InitializeWithEmptyVertices() const noexcept;
    void BuildNewMeshesIfNeeded() const noexcept;

private:
    std::wstring                              string{};
    const BitmapFont* font = nullptr;
    mutable std::unordered_map<int, Vertices> vertices{};
    mutable bool                              needNewMeshes = true;
    material textMaterial{};
    vector2 position;
    CameraView view{};
    int width = 1280, height = 720;
};