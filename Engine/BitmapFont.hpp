/*
 * Author		:Jeesoo Kim
 * File			:BitmapFont.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Bitmap Font
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Texture.hpp"
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

class [[nodiscard]] BitmapFont
{
public:
    struct [[nodiscard]] character
    {
        wchar_t        id = wchar_t(-1); // The character id.
        unsigned short x = 0;           // The left position of the character image in the texture.
        unsigned short y = 0;           // The top position of the character image in the texture.
        unsigned short width = 0;           // The width of the character image in the texture.
        unsigned short height = 0;           // The height of the character image in the texture.
        short xOffset = 0; // How much the current position should be offset when copying the image from the texture
                           // to the screen.
        short yOffset = 0; // How much the current position should be offset when copying the image from the texture
                           // to the screen.
        short         xAdvance = 0; // How much the current position should be advanced after drawing the character.
        unsigned char page = 0; // The texture page where the character image is found.
    };

    struct [[nodiscard]] information
    {
        short          fontSize = 0;
        std::wstring   fontName{};
        unsigned short lineHeight = 0; // This is the distance in pixels between each line of text.
        unsigned short imageWidth = 0;
        unsigned short imageHeight = 0;
        unsigned short pagesCount = 0; // The number of texture pages included in the font.
        std::vector<std::wstring>
            pageNames{}; // the name of a texture file. There is one for each page in the font.
    };

public:
    bool               LoadFromFile(const std::filesystem::path& filename);
    bool               LoadDefinition(const std::wstring& font_definition, std::vector<Texture> page_textures);
    const information& GetInformation() const noexcept;
    character          GetCharacter(wchar_t character_id) const noexcept;
    unsigned short     GetLineHeight() const noexcept;
    const Texture& GetTexture(int page_index) const noexcept;
    bool               HasCharacter(wchar_t character_id) const noexcept;

private:
    bool CanParseFile(const std::filesystem::path& filename);
    bool CanParseStream(std::wistream& stream);

private:
    information                            details{};
    std::unordered_map<wchar_t, character> characters{};
    std::vector<Texture>                   pageTextures{};
};