/*
 * Author		:Jeesoo Kim
 * File			:GL.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for GL
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Color4f.hpp"

class Color4f;

struct material;
class Vertices;

namespace GL
{
    // should only be called once
    void setup() noexcept;
    // To do drawing for a frame call BeginDrawing() once at the very beginning.
    void begin_drawing() noexcept;
    // Call Draw() as many times as you need.
    void draw(const Vertices& vertices, const material& material) noexcept;
	void draw_instance(const Vertices& vertices, const material& material) noexcept;
    // Lastly call EndDrawing() once at the very end.
    void end_drawing() noexcept;

    void set_clear_color(Color4f color) noexcept;
    void set_display_area(int pixels_width, int pixels_height, int left_x = 0, int bottom_y = 0) noexcept;
    void set_line_width(float line_width) noexcept;
    void enable_multiple_sampling(bool enable_it = true) noexcept;

    void print_context_information();
}