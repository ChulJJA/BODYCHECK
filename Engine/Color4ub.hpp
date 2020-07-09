/*
 * Author		:Jeesoo Kim
 * File			:Color4ub.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Color4ub
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

class [[nodiscard]] Color4ub
{
public:
    using unsigned_byte = unsigned char;

    unsigned_byte red = 0;
    unsigned_byte green = 0;
    unsigned_byte blue = 0;
    unsigned_byte alpha = 255;

public:
    Color4ub() noexcept = default;
    explicit Color4ub(unsigned_byte grey, unsigned_byte alpha = 0xff) noexcept;
    Color4ub(unsigned_byte red, unsigned_byte green, unsigned_byte blue, unsigned_byte alpha = 0xff) noexcept;
};

static_assert(sizeof(Color4ub) == 4,
    "Color4ub should be the same as 4 bytes, so we can easily treat it as an RGBA int.");

class Color4f;
Color4ub to_color4ub(const Color4f& float_colors);

class HexColor
{
public:
    unsigned rgba = 0;

    constexpr HexColor() noexcept = default;
    constexpr HexColor(unsigned hex) noexcept : rgba(hex) {}
    constexpr HexColor(int hex) noexcept : rgba(unsigned(hex)) {}
    operator Color4ub() const noexcept
    {
        return Color4ub{ static_cast<Color4ub::unsigned_byte>((rgba & 0xff000000) >> 24),
                        static_cast<Color4ub::unsigned_byte>((rgba & 0x00ff0000) >> 16),
                        static_cast<Color4ub::unsigned_byte>((rgba & 0x0000ff00) >> 8),
                        static_cast<Color4ub::unsigned_byte>((rgba & 0x000000ff) >> 0) };
    }
};