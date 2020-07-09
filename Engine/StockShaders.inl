/*
 * Author		:Jeesoo Kim
 * File			:StockShaders.inl
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Stock Shader
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

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
uniform mat3 model;
uniform mat3 cam;
uniform float depth;

out vec2 interpolated_texture_coordinate;

void main()
{
    //vec3 position = to_ndc * vec3(position, 1.0f);
	vec3 position = to_ndc * cam * model * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, 0.5, 1.0);
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
    if(new_color.a <= 0.1)
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

inline Shader& SHADER::particles() noexcept
{
	static Shader shader(
		R"(
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture_coordinate;

out vec4 ParticleColor;
out vec2 Texcoords;

uniform mat3 to_ndc;
uniform vec4 color;
uniform vec2 offset;
uniform float depth;

void main()
{
	Texcoords = texture_coordinate;
    ParticleColor = color;
    vec3 p_position = to_ndc * vec3(position + offset, 1.0);
	gl_Position = vec4(p_position.xy, 0.1, 1.0);
}
)",
R"(
#version 330 core
in vec4 ParticleColor;
in vec2 Texcoords;

out vec4 output_color;

uniform sampler2D texture_to_sample;

void main()
{
	vec4 texel = texture(texture_to_sample, Texcoords);
    vec4 new_color = ParticleColor * texel;
    if(new_color.a <= 0)
        discard;
    output_color = new_color;
}  
)");
	return shader;
}

inline const VertexLayoutDescription& SHADER::particles_layout() noexcept
{
	static VertexLayoutDescription layout{ VertexLayoutDescription::Position2WithFloats,
										  VertexLayoutDescription::TextureCoordinates2WithFloats };
	return layout;
}