/*
 * Author		:Jeesoo Kim
 * File			:Image.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Image
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Color4ub.hpp"
#include <filesystem>
#include <vector>

class [[nodiscard]] Image
{
public:
    void ResizeToPixelWidthHeight(int pixel_width, int pixel_height) noexcept;
    bool LoadFromPNG(const std::filesystem::path& file_path) noexcept;
    void SaveToPNG(const std::filesystem::path& file_path) const noexcept;

    int GetWidth() const noexcept;
    int GetHeight() const noexcept;

    void            SetPixel(int column, int row, Color4ub color) noexcept;
    Color4ub* GetPixelsPointer() noexcept;
    const Color4ub* GetPixelsPointer() const noexcept;
    int             GetPixelsBufferBytesSize() const noexcept;
    void            FlipVertically() noexcept;

private:
    int                   width = 0;
    int                   height = 0;
    std::vector<Color4ub> pixels{};

    static const int ChannelsPerColor = 4;
};