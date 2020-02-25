#pragma once


inline Shader& SHADER::solid_color() noexcept
{
    static Shader shader(R"(
#version 330

layout(location = 0) in vec2 position;

uniform mat3 to_ndc;
uniform float depth;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);
}
)",
R"(
#version 330

uniform vec4 color;
out vec4 output_color;

void main()
{
    output_color = color;
}
)");
    return shader;
}

inline const VertexLayoutDescription& SHADER::solid_color_vertex_layout() noexcept
{
    static VertexLayoutDescription layout{ VertexLayoutDescription::Position2WithFloats };
    return layout;
}

inline Shader& SHADER::interpolated_colors() noexcept
{
    static Shader shader(
        R"(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;

uniform mat3 to_ndc;
uniform float depth;

smooth out vec4 interpolated_color;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);
    interpolated_color = color;
}
)",
R"(
#version 330

in vec4 interpolated_color;
out vec4 output_color;

void main()
{
    output_color = interpolated_color;
}
)");
    return shader;
}

inline const VertexLayoutDescription& SHADER::interpolated_colors_vertex_layout() noexcept
{
    static VertexLayoutDescription layout{ VertexLayoutDescription::Position2WithFloats,
                                          VertexLayoutDescription::Color4WithUnsignedBytes };
    return layout;
}

inline Shader& SHADER::textured() noexcept
{
    static Shader shader(
        R"(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture_coordinate;

uniform mat3 to_ndc;
uniform float depth;

out vec2 interpolated_texture_coordinate;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);
    interpolated_texture_coordinate = texture_coordinate;
}
)",
R"(
#version 330

in vec2 interpolated_texture_coordinate;

uniform vec4 color;
uniform sampler2D texture_to_sample;

out vec4 output_color;

void main()
{
    vec4 texel = texture(texture_to_sample, interpolated_texture_coordinate);
    vec4 new_color = color * texel;
    if(new_color.a <= 0.0f)
        discard;
    output_color = new_color;
}
)");
    return shader;
}

inline const VertexLayoutDescription& SHADER::textured_vertex_layout() noexcept
{
    static VertexLayoutDescription layout{ VertexLayoutDescription::Position2WithFloats,
                                          VertexLayoutDescription::TextureCoordinates2WithFloats };
    return layout;
}

