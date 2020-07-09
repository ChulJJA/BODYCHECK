/*
 * Author		:Jeesoo Kim
 * File			:Shader.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Shader
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Color4f.hpp"
#include "Shader.hpp"
#include "matrix3.hpp"
#include "Application.hpp"
#include <cassert>
#include <iostream>


Shader::Shader(const std::string& vertex_shader_source_code, const std::string& fragment_shader_source_code)
{
    if (!LoadFromSource(vertex_shader_source_code, fragment_shader_source_code))
    {
        std::cerr << "Fail to compile shader!" << std::endl;
    }
}
bool Shader::LoadFromSource(const std::string& vertex_shader_source_code,
    const std::string& fragment_shader_source_code)
{
    if (vertex_shader_source_code.empty() || fragment_shader_source_code.empty())
    {
        std::cerr << "shader source code is empty!" << std::endl;
        return false;
    }
    if (handleToShader != NULL)
    {
        Delete();
    }


    int         vertex_result;
    int         fragment_result;
    int         program_result;
    const char* src_vertex = vertex_shader_source_code.c_str();
    const char* src_frag = fragment_shader_source_code.c_str();
    GLint       vertex_id;
    GLint       fragment_id;

    vertex_id = glCreateShader(GL_VERTEX_SHADER);
    fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

    handleToShader = glCreateProgram();

    glShaderSource(vertex_id, 1, &src_vertex, nullptr);
    glShaderSource(fragment_id, 1, &src_frag, nullptr);

    glCompileShader(vertex_id);
    glCompileShader(fragment_id);

    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &vertex_result);
    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &fragment_result);

    if (vertex_result == GL_FALSE)
    {
        glDeleteShader(vertex_id);
        GLint max_length = 0;
        glGetShaderiv(vertex_id, GL_INFO_LOG_LENGTH, &max_length);
        GLchar* vertex_info_log = new GLchar[max_length + 1];

        glGetProgramInfoLog(vertex_id, max_length, &max_length, vertex_info_log);
        std::cerr << "Fail to compile vertex shader " << vertex_info_log << std::endl;
        uniformNameToLocation.clear();
        delete[] vertex_info_log;
        return false;
    }

    if (fragment_result == GL_FALSE)
    {
        glDeleteShader(fragment_id);
        GLint max_length = 0;
        glGetShaderiv(fragment_id, GL_INFO_LOG_LENGTH, &max_length);
        GLchar* fragment_info_log = new GLchar[max_length + 1];

        glGetProgramInfoLog(fragment_id, max_length, &max_length, fragment_info_log);
        std::cerr << "Fail to compile fragment shader " << fragment_info_log << std::endl;
        uniformNameToLocation.clear();
        delete[] fragment_info_log;
        return false;
    }
    glAttachShader(handleToShader, vertex_id);
    glAttachShader(handleToShader, fragment_id);

    glLinkProgram(handleToShader);
    glGetProgramiv(handleToShader, GL_LINK_STATUS, &program_result);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
    if (program_result == GL_FALSE)
    {
        GLint max_length = 0;
        glGetProgramiv(handleToShader, GL_INFO_LOG_LENGTH, &max_length);
        GLchar* program_info_log = new GLchar[max_length + 1];

        glGetProgramInfoLog(handleToShader, max_length, &max_length, program_info_log);
        std::cerr << "Fail to link program " << program_info_log << std::endl;

        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
        uniformNameToLocation.clear();
        Delete();

        return false;
    }
    return true;
}
int Shader::GetUniformLocation(const std::string& name) noexcept
{
    auto uniform_it = uniformNameToLocation.find(name);

    if (uniform_it == uniformNameToLocation.end())
    {
        unsigned int uniform_location;
        uniform_location = glGetUniformLocation(handleToShader, name.c_str());
        uniformNameToLocation[name] = uniform_location;
        return uniform_location;
    }
    return uniform_it->second;
}
void Shader::SendUniformVariable(const std::string& variable_name, const matrix3& affine_matrix) noexcept
{
    int uniform_location = GetUniformLocation(variable_name);
    glUniformMatrix3fv(uniform_location, 1, GL_FALSE, &affine_matrix.elements[0][0]);
}
void Shader::SendUniformVariable(const std::string& variable_name, float number) noexcept
{
    int uniform_location = GetUniformLocation(variable_name);
    glUniform1f(uniform_location, number);
}
void Shader::SendUniformVariable(const std::string& variable_name, int number) noexcept
{
    int uniform_location = GetUniformLocation(variable_name);
    glUniform1i(uniform_location, number);
}
void Shader::SendUniformVariable(const std::string& variable_name, Color4f color) noexcept
{
    int uniform_location = GetUniformLocation(variable_name);
    glUniform4f(uniform_location, color.red, color.green, color.blue, color.alpha);
}
void Shader::Select(const Shader& shader) noexcept
{
    glUseProgram(shader.GetShaderHandler());
}
void Shader::SelectNothing() noexcept
{
    glUseProgram(NULL);
}
void Shader::Delete() noexcept
{
    glDeleteProgram(handleToShader);
    uniformNameToLocation.clear();
}