/*
 * Author		:Jeesoo Kim
 * File			:Shader.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Shader
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <map>
#include <string>

class Color4f;
struct matrix3;
struct vector3;

class [[nodiscard]] Shader
{
public:
    Shader() noexcept = default;
    Shader(const std::string & vertex_shader_source_code, const std::string & fragment_shader_source_code);
    ~Shader() noexcept = default;

    bool LoadFromSource(const std::string & vertex_shader_source_code,
                        const std::string & fragment_shader_source_code);

    void SendUniformVariable(const std::string & variable_name, const matrix3 & affine_matrix) noexcept;
    void SendUniformVariable(const std::string & variable_name, float number) noexcept;
    void SendUniformVariable(const std::string & variable_name, int number) noexcept;
    void SendUniformVariable(const std::string & variable_name, Color4f color) noexcept;

    constexpr unsigned GetShaderHandler() const noexcept { return handleToShader; }

    void Delete() noexcept;

public:
    static void Select(const Shader & shader) noexcept;
    static void SelectNothing() noexcept;

public:
    Shader(const Shader & other) = delete;
    Shader(Shader && other) noexcept = delete;
    Shader& operator=(const Shader & other) = delete;
    Shader& operator=(Shader && other) noexcept = delete;

private:
    int GetUniformLocation(const std::string & name) noexcept;

private:
    unsigned                   handleToShader = 0;
    std::map<std::string, int> uniformNameToLocation{};
};