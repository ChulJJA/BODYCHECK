/*
 * Author		:Sangmin Kim
 * File			:matrix3.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for matrix3
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "matrix3.hpp"
#include "vector2.hpp"
#include <cassert>
#include <cmath>
#include <limits>
#include "../Engine/angles.hpp"

#define COORDINATE_LIMIT 2


matrix3::matrix3() noexcept
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            elements[i][j] = 0.0f;
        }
    }
}
matrix3::matrix3(vector3 first_column, vector3 second_column, vector3 third_column) noexcept
{
    elements[0][0] = first_column.x;
    elements[1][0] = second_column.x;
    elements[2][0] = third_column.x;

    elements[0][1] = first_column.y;
    elements[1][1] = second_column.y;
    elements[2][1] = third_column.y;

    elements[0][2] = first_column.z;
    elements[1][2] = second_column.z;
    elements[2][2] = third_column.z;
}
matrix3::matrix3(float column0_row0, float column0_row1, float column0_row2, float column1_row0, float column1_row1,
    float column1_row2, float column2_row0, float column2_row1, float column2_row2) noexcept
{
    elements[0][0] = column0_row0;
    elements[1][0] = column1_row0;
    elements[2][0] = column2_row0;

    elements[0][1] = column0_row1;
    elements[1][1] = column1_row1;
    elements[2][1] = column2_row1;

    elements[0][2] = column0_row2;
    elements[1][2] = column1_row2;
    elements[2][2] = column2_row2;
}
float matrix3::operator()(int column, int row) const noexcept
{
    assert(column >= 0 && column <= COORDINATE_LIMIT);
    assert(row >= 0 && row <= COORDINATE_LIMIT);

    float element_val = 0.0f;

    element_val = elements[column][row];

    return element_val;
}
float& matrix3::operator()(int column, int row) noexcept
{
    assert(column >= 0 && column <= COORDINATE_LIMIT);
    assert(row >= 0 && row <= COORDINATE_LIMIT);

    return elements[column][row];
}
matrix3 operator*(const matrix3& m1, const matrix3& m2) noexcept
{
    matrix3 result_matrix;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int z = 0; z < 3; z++)
            {
                result_matrix.elements[j][i] += m1.elements[z][i] * m2.elements[j][z];
            }
        }
    }
    return result_matrix;
}
void    operator*=(matrix3& m1, const matrix3& m2) noexcept { m1 = m1 * m2; }
vector3 operator*(const matrix3& m, vector3 v) noexcept
{
    vector3 my_vec;
    my_vec.x = ((m.column0.x * v.x) + (m.column1.x * v.y) + (m.column2.x * v.z));
    my_vec.y = ((m.column0.y * v.x) + (m.column1.y * v.y) + (m.column2.y * v.z));
    my_vec.z = ((m.column0.z * v.x) + (m.column1.z * v.y) + (m.column2.z * v.z));

    return my_vec;
}

matrix3 MATRIX3::transpose(const matrix3& m) noexcept
{
    matrix3 result_matrix;

    result_matrix.elements[0][0] = m.elements[0][0];
    result_matrix.elements[0][1] = m.elements[1][0];
    result_matrix.elements[0][2] = m.elements[2][0];

    result_matrix.elements[1][0] = m.elements[0][1];
    result_matrix.elements[1][1] = m.elements[1][1];
    result_matrix.elements[1][2] = m.elements[2][1];

    result_matrix.elements[2][0] = m.elements[0][2];
    result_matrix.elements[2][1] = m.elements[1][2];
    result_matrix.elements[2][2] = m.elements[2][2];

    return result_matrix;
}
matrix3 MATRIX3::build_rotation(float angle_in_radians) noexcept
{
    matrix3   result_matrix;
    const int zero_val = 0;

	angle_in_radians = to_radians(angle_in_radians);

    result_matrix.column0.x = std::cos(angle_in_radians);
    result_matrix.column0.y = sin(angle_in_radians);
    result_matrix.column0.z = 0.0f;
    result_matrix.column1.x = -(sin(angle_in_radians));
    result_matrix.column1.y = cos(angle_in_radians);
    result_matrix.column1.z = 0.0f;
    result_matrix.column2.x = 0.0f;
    result_matrix.column2.y = 0.0f;
    result_matrix.column2.z = 1.0f;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (std::abs(result_matrix.elements[i][j]) <= std::numeric_limits<float>::epsilon())
            {
                result_matrix.elements[i][j] = (float)zero_val;
            }
        }
    }

    return result_matrix;
}
matrix3 MATRIX3::build_identity() noexcept
{
    matrix3 result_matrix;

    result_matrix.column0.x = 1.0f;
    result_matrix.column1.y = 1.0f;
    result_matrix.column2.z = 1.0f;

    return result_matrix;
}
matrix3 MATRIX3::build_scale(float scale_x, float scale_y) noexcept
{
    matrix3 result_matrix;

    result_matrix.elements[0][0] = scale_x;
    result_matrix.elements[1][1] = scale_y;
    result_matrix.elements[2][2] = 1.0f;

    return result_matrix;
}
matrix3 MATRIX3::build_scale(float scale) noexcept
{
    matrix3 result_matrix;
    result_matrix.column0.x = scale;
    result_matrix.column1.y = scale;
    result_matrix.column2.z = 1.0f;

    return result_matrix;
}
matrix3 MATRIX3::build_scale(const vector2& scale) noexcept
{
    matrix3 result_matrix;
    result_matrix.column0.x = scale.x;
    result_matrix.column1.y = scale.y;
    result_matrix.column2.z = 1.0f;

    return result_matrix;
}
matrix3 MATRIX3::build_translation(float translate_x, float translate_y) noexcept
{
    matrix3 result_matrix;

    result_matrix.column0.x = 1.0f;
    result_matrix.column1.y = 1.0f;
    result_matrix.column2.x = translate_x;
    result_matrix.column2.y = translate_y;
    result_matrix.column2.z = 1.0f;

    return result_matrix;
}
matrix3 MATRIX3::build_translation(const vector2& translation) noexcept
{
    matrix3 result_matrix;

    result_matrix.column0.x = 1.0f;
    result_matrix.column1.y = 1.0f;
    result_matrix.column2.x = translation.x;
    result_matrix.column2.y = translation.y;
    result_matrix.column2.z = 1.0f;

    return result_matrix;
}