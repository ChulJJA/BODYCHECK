/*
 * Author		:Jeesoo Kim
 * File			:BitmapFont.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Bitmap Font
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "BitmapFont.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "Messagebox.h"
#include <iostream>

bool BitmapFont::LoadDefinition(const std::wstring& font_definition, std::vector<Texture> page_textures)
{
    std::wistringstream stream(font_definition);
    if (!CanParseStream(stream))
        return false;
    pageTextures = std::move(page_textures);
    return pageTextures.size() == details.pagesCount;
}
bool BitmapFont::LoadFromFile(const std::filesystem::path& filename)
{
	std::ifstream f;
	f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		f.open(filename);
		if (CanParseFile(filename))
		{
			Texture texture;

			std::wstring temp_name;

			for (int i = 0; i < details.pagesCount; i++)
			{
				temp_name = details.pageNames[i];
				temp_name = filename.parent_path().append(temp_name.substr(1, 18));
				if (texture.LoadFromPNG(temp_name))
				{
					pageTextures.push_back(std::move(texture));
				}
				else
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (std::system_error & e)
	{
		std::cerr << e.code().message() << std::endl;
		Messagebox::Init_Box(filename);
	}
}
const BitmapFont::information& BitmapFont::GetInformation() const noexcept
{
    return details;
}
BitmapFont::character          BitmapFont::GetCharacter(wchar_t character_id) const noexcept
{
    for (auto c : characters)
    {
        if (c.first == character_id)
        {
            return c.second;
        }
    }
    for (auto c : characters)
    {
        if (c.first == wchar_t(-1))
        {
            return c.second;
        }
    }
    return character();

}
unsigned short     BitmapFont::GetLineHeight() const noexcept
{
    return details.lineHeight;
}
const Texture& BitmapFont::GetTexture(int page_index) const noexcept
{
    assert(pageTextures.size() >= 1);
    assert(page_index <= pageTextures.size() && page_index >= 0);
    return pageTextures[page_index];
}
bool               BitmapFont::HasCharacter(wchar_t character_id) const noexcept
{
    if (character_id != NULL)
    {
        return true;
    }
    else
        return false;
}
bool BitmapFont::CanParseFile(const std::filesystem::path& filename)
{
    std::wifstream stream;
    stream.open(filename.c_str());
    return CanParseStream(stream);
}

bool BitmapFont::CanParseStream(std::wistream& stream)
{
    std::wstring      Line;
    std::wstring Read, Key, Value;
    std::size_t i;

    character charId;

    while (!stream.eof())
    {
        std::wstringstream LineStream;
        std::getline(stream, Line);
        LineStream << Line;
        LineStream >> Read;
        if (Read == L"info")
        {
            while (!LineStream.eof())
            {
                std::wstringstream Converter;
                LineStream >> Read;
                i = Read.find('=');
                Key = Read.substr(0, i);
                Value = Read.substr(i + 1);
                // assign the correct value
                Converter << Value;
                if (Key == L"face")
                    Converter >> details.fontName;
                if (Key == L"size")
                    Converter >> details.fontSize;
            }
        }
        else if (Read == L"page")
        {
            while (!LineStream.eof())
            {
                std::wstringstream Converter;
                LineStream >> Read;
                i = Read.find('=');
                Key = Read.substr(0, i);
                Value = Read.substr(i + 1);
                // assign the correct value
                Converter << Value;
                if (Key == L"file")
                {
                    details.pageNames.push_back(Value);
                }
            }
        }
        else if (Read == L"common")
        {
            // this holds common data
            while (!LineStream.eof())
            {
                std::wstringstream Converter;
                LineStream >> Read;
                i = Read.find('=');
                Key = Read.substr(0, i);
                Value = Read.substr(i + 1);
                // assign the correct value
                Converter << Value;
                if (Key == L"lineHeight")
                    Converter >> details.lineHeight;
                if (Key == L"scaleW")
                    Converter >> details.imageWidth;
                if (Key == L"scaleH")
                    Converter >> details.imageHeight;
                if (Key == L"pages")
                    Converter >> details.pagesCount;
            }
        }
        else if (Read == L"char")
        {

            while (!LineStream.eof())
            {
                std::wstringstream Converter;
                LineStream >> Read;
                i = Read.find('=');
                Key = Read.substr(0, i);
                Value = Read.substr(i + 1);
                // assign the correct value
                Converter << Value;
                if (Key == L"id")
                    Converter >> reinterpret_cast<unsigned short&>(charId.id);
                if (Key == L"x")
                    Converter >> characters[charId.id].x;
                if (Key == L"y")
                    Converter >> characters[charId.id].y;
                if (Key == L"width")
                    Converter >> characters[charId.id].width;
                if (Key == L"height")
                    Converter >> characters[charId.id].height;
                if (Key == L"xoffset")
                    Converter >> characters[charId.id].xOffset;
                if (Key == L"yoffset")
                    Converter >> characters[charId.id].yOffset;
                if (Key == L"xadvance")
                    Converter >> characters[charId.id].xAdvance;
                if (Key == L"page")
                {
                    unsigned short page;
                    Converter >> page;
                    characters[charId.id].page = static_cast<unsigned char>(page);
                }
            }
        }
    }
    return true;
}