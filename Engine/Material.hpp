/*
 * Author		:Jeesoo Kim
 * File			:Material.hpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Material.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Color4f.hpp"
#include "matrix3.hpp"
#include <map>
#include <string>

class Shader;
class Texture;
struct [[nodiscard]] texture_uniform
{
    const Texture * texture = nullptr;
    int            textureSlot = 0;
};

struct [[nodiscard]] material
{
    Shader * shader = nullptr;
    std::map<std::string, matrix3>         matrix3Uniforms{};
    std::map<std::string, Color4f>         color4fUniforms{};
    std::map<std::string, float>           floatUniforms{};
    std::map<std::string, texture_uniform> textureUniforms{};
};