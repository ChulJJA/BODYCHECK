/*
 * Author		:Sangmin Kim
 * File			:vector3.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for vector3
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union

struct [[nodiscard]] vector3
{
    union {
        struct
        {
            float x, y, z;
        };
        struct
        {
            float r, g, b;
        };
        struct
        {
            float width, height, depth;
        };
        float elements[3];
    };

    vector3() noexcept;
    explicit vector3(float repeated_float) noexcept;
    vector3(float fx, float fy, float fz) noexcept;
};

static_assert(sizeof(vector3) == sizeof(float) * 3, "vector3 should only be three floats");

void operator+=(vector3& v, const vector3& adding_vector) noexcept;
void operator-=(vector3& v, const vector3& subtracting_vector) noexcept;
void operator*=(vector3& v, float scale) noexcept;
void operator/=(vector3& v, float divisor) noexcept;

vector3 operator-(const vector3& v) noexcept;
vector3 operator+(const vector3& v1, const vector3& v2) noexcept;
vector3 operator-(const vector3& v1, const vector3& v2) noexcept;
vector3 operator*(const vector3& v, float scale) noexcept;
vector3 operator*(float scale, const vector3& v) noexcept;
vector3 operator/(const vector3& v, float divisor) noexcept;

[[nodiscard]] bool operator==(const vector3& v1, const vector3& v2) noexcept;
[[nodiscard]] bool operator!=(const vector3& v1, const vector3& v2) noexcept;


[[nodiscard]] float dot(vector3 a, vector3 b) noexcept;
vector3             cross(vector3 a, vector3 b) noexcept;
[[nodiscard]] float magnitude_squared(vector3 a) noexcept;
[[nodiscard]] float magnitude(vector3 a) noexcept;
vector3             normalize(vector3 a) noexcept;
[[nodiscard]] float distance_between_squared(vector3 a, vector3 b) noexcept;
[[nodiscard]] float distance_between(vector3 a, vector3 b) noexcept;
[[nodiscard]] float angle_between(vector3 a, vector3 b) noexcept;
#pragma warning(pop)