/*
 * Author		:Sangmin Kim
 * File			:vector2.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for vector2
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
struct [[nodiscard]] vector2
{
    union {
        struct
        {
            float x, y;
        };
        struct
        {
            float u, v;
        };
        struct
        {
            float width, height;
        };
        float elements[2];
    };

    vector2() noexcept;
    explicit vector2(float repeated_float) noexcept;
    vector2(float fx, float fy) noexcept;
};

static_assert(sizeof(vector2) == sizeof(float) * 2, "vector2 should only be two floats");

void operator+=(vector2& v, const vector2& adding_vector) noexcept;
void operator-=(vector2& v, const vector2& subtracting_vector) noexcept;
void operator*=(vector2& v, float scale) noexcept;
void operator/=(vector2& v, float divisor) noexcept;

vector2 operator-(const vector2& v) noexcept;

vector2 operator+(const vector2& v1, const vector2& v2) noexcept;
vector2 operator-(const vector2& v1, const vector2& v2) noexcept;
vector2 operator*(const vector2& v, float scale) noexcept;
vector2 operator*(float scale, const vector2& v) noexcept;
vector2 operator/(const vector2& v, float divisor) noexcept;

[[nodiscard]] bool operator==(const vector2& v1, const vector2& v2) noexcept;
[[nodiscard]] bool operator!=(const vector2& v1, const vector2& v2) noexcept;


[[nodiscard]] float dot(vector2 a, vector2 b) noexcept;
vector2             perpendicular_to(vector2 a) noexcept;
[[nodiscard]] float magnitude_squared(vector2 a) noexcept;
[[nodiscard]] float magnitude(vector2 a) noexcept;
vector2             normalize(vector2 a) noexcept;
[[nodiscard]] float distance_between_squared(vector2 a, vector2 b) noexcept;
[[nodiscard]] float distance_between(vector2 a, vector2 b) noexcept;
[[nodiscard]] float angle_between(vector2 a, vector2 b) noexcept;
vector2             rotate_by(float angle_in_radians, vector2 v) noexcept;
#pragma warning(pop)