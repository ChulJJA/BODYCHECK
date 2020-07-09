/*
 * Author		:Jeesoo Kim
 * File			:Color.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Color
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Color4f.hpp"
#include "Color4ub.hpp"

#define COLOR_ATTRIBUTE_VAL 255


Color4ub::Color4ub(unsigned_byte grey, unsigned_byte alpha) noexcept
{
    this->red = grey;
    this->green = grey;
    this->blue = grey;
    this->alpha = alpha;
}
Color4ub::Color4ub(unsigned_byte red, unsigned_byte green, unsigned_byte blue, unsigned_byte alpha) noexcept
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}
Color4ub to_color4ub(const Color4f& float_colors)
{
    Color4ub color_val;
    float    color_red = float_colors.red;
    float    color_green = float_colors.red;
    float    color_blue = float_colors.red;
    float    color_alpha = float_colors.red;
    if (color_red > 1.0f)
    {
        color_red = 1.0f;
    }
    else if (color_red < 0.0f)
    {
        color_red = 0.0f;
    }
    if (color_green > 1.0f)
    {
        color_green = 1.0f;
    }
    else if (color_green < 0.0f)
    {
        color_green = 0.0f;
    }
    if (color_blue > 1.0f)
    {
        color_blue = 1.0f;
    }
    else if (color_blue < 0.0f)
    {
        color_blue = 0.0f;
    }
    if (color_alpha > 1.0f)
    {
        color_alpha = 1.0f;
    }
    else if (color_alpha < 0.0f)
    {
        color_alpha = 0.0f;
    }
    color_val.green = static_cast<Color4ub::unsigned_byte>(color_green)* COLOR_ATTRIBUTE_VAL;
    color_val.red = static_cast<Color4ub::unsigned_byte>(color_red)* COLOR_ATTRIBUTE_VAL;

    color_val.blue = static_cast<Color4ub::unsigned_byte>(color_blue)* COLOR_ATTRIBUTE_VAL;
    color_val.alpha = static_cast<Color4ub::unsigned_byte>(color_alpha)* COLOR_ATTRIBUTE_VAL;

    if (color_val.red + 0.5f <= color_red * COLOR_ATTRIBUTE_VAL)
    {
        color_val.red += static_cast<Color4ub::unsigned_byte>(1.0f);
    }
    if (color_val.green + 0.5f <= color_green * COLOR_ATTRIBUTE_VAL)
    {
        color_val.green += static_cast<Color4ub::unsigned_byte>(1.0f);
    }
    if (color_val.blue + 0.5f <= color_blue * COLOR_ATTRIBUTE_VAL)
    {
        color_val.blue += static_cast<Color4ub::unsigned_byte>(1.0f);
    }
    if (color_val.alpha + 0.5f <= color_alpha * COLOR_ATTRIBUTE_VAL)
    {
        color_val.alpha += static_cast<Color4ub::unsigned_byte>(1.0f);
    }

    return color_val;
}
Color4f::Color4f(float grey, float alpha) noexcept
{
    this->red = grey;
    this->green = grey;
    this->blue = grey;
    this->alpha = alpha;
}
Color4f::Color4f(float red, float green, float blue, float alpha) noexcept
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}
Color4f to_color4f(const Color4ub& eight_bit_color)
{
    Color4f color_val_float;
    color_val_float.red = static_cast<float>(eight_bit_color.red) / COLOR_ATTRIBUTE_VAL;
    color_val_float.green = static_cast<float>(eight_bit_color.green) / COLOR_ATTRIBUTE_VAL;
    color_val_float.blue = static_cast<float>(eight_bit_color.blue) / COLOR_ATTRIBUTE_VAL;
    color_val_float.alpha = static_cast<float>(eight_bit_color.alpha) / COLOR_ATTRIBUTE_VAL;

    return color_val_float;
}