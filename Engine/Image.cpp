/*
 * Author		:Jeesoo Kim
 * File			:Image.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Image
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */


#include "Image.hpp"
#include <cassert>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#pragma warning(push)
#pragma warning(disable : 4505) // unreferenced local function has been removed
#pragma warning(disable : 4100) // unreferenced formal parameter
#include <stb_image.h>
#pragma warning(pop)

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include <stb_image_write.h>

void Image::ResizeToPixelWidthHeight(const int pixel_width, const int pixel_height) noexcept
{
    assert(pixel_height > 0 && pixel_width > 0);
    width = pixel_width;
    height = pixel_height;
    pixels.resize(width * height);
}

bool Image::LoadFromPNG(const std::filesystem::path& file_path) noexcept
{
    int channels;
	std::string file_name = file_path.string();
    unsigned char* is_load_proper = stbi_load(file_name.c_str(), &width, &height, &channels, ChannelsPerColor);

    Color4ub temp_color;
    for (int i = 0; i < width * height * ChannelsPerColor; i += ChannelsPerColor)
    {
        temp_color.red = is_load_proper[i];
        temp_color.green = is_load_proper[i + 1];
        temp_color.blue = is_load_proper[i + 2];
        temp_color.alpha = is_load_proper[i + 3];
        pixels.push_back(temp_color);
    }
    return is_load_proper != nullptr;
}

void Image::SaveToPNG(const std::filesystem::path& file_path) const noexcept
{
    stbi_write_png(file_path.string().c_str(), width, height, ChannelsPerColor, GetPixelsPointer(), width * sizeof(Color4ub));
}

int Image::GetWidth() const noexcept
{
    return width;
}

int Image::GetHeight() const noexcept
{
    return height;
}

void Image::SetPixel(const int column, const int row, const Color4ub color) noexcept
{
    assert(row >= 0 && row <= height);
    assert(column >= 0 && row <= width);

    pixels[(row * width) + column] = color;
}

Color4ub* Image::GetPixelsPointer() noexcept
{
    return &pixels[0];
}

const Color4ub* Image::GetPixelsPointer() const noexcept
{
	return &pixels[0];
}

int Image::GetPixelsBufferBytesSize() const noexcept
{
    return static_cast<int>(sizeof(Color4ub) * pixels.size());
}

void Image::FlipVertically() noexcept
{
    std::vector<Color4ub> temp_save;

    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {
            temp_save.push_back(pixels[(i * width) + j]);
        }
    }
    pixels = temp_save;
}