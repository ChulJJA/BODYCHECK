/*
 * Author		:Sangmin Kim
 * File			:matrix3.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for matrix3
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "vector3.hpp"
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
 /**
  * \brief Column first 3x3 matrix class
  */
struct [[nodiscard]] matrix3
{
public:
    union {
        float elements[3][3]{};
        struct
        {
            vector3 column0;
            vector3 column1;
            vector3 column2;
        };
    };

public:
    matrix3() noexcept;
    matrix3(vector3 first_column, vector3 second_column, vector3 third_column) noexcept;
    matrix3(float column0_row0, float column0_row1, float column0_row2, float column1_row0, float column1_row1,
            float column1_row2, float column2_row0, float column2_row1, float column2_row2) noexcept;

    float  operator()(int column, int row) const noexcept;
    float& operator()(int column, int row) noexcept;
};

static_assert(sizeof(matrix3) == sizeof(float) * 3 * 3, "matrix3 should be 3x3 floats");

matrix3 operator*(const matrix3& m1, const matrix3& m2) noexcept;
void    operator*=(matrix3& m1, const matrix3& m2) noexcept;
vector3 operator*(const matrix3& m, vector3 v) noexcept;

struct vector2;
namespace MATRIX3
{
    matrix3 transpose(const matrix3& m) noexcept;
    matrix3 build_rotation(float angle_in_radians) noexcept;
    matrix3 build_identity() noexcept;
    matrix3 build_scale(float scale_x, float scale_y) noexcept;
    matrix3 build_scale(float scale) noexcept;
    matrix3 build_scale(const vector2& scale) noexcept;
    matrix3 build_translation(float translate_x, float translate_y) noexcept;
    matrix3 build_translation(const vector2& translation) noexcept;
}
#pragma warning(pop)