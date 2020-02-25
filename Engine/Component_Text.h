/*
 * Author		:Jeesoo Kim
 * File			:Component_Text.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Header file for Component_Text.cpp.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include "Component.hpp"
#include "Text.hpp"
#include "BitmapFont.hpp"
#include "Mesh.hpp"
#include "StockShaders.hpp"
#include "Graphic.h"
#include "Shader.hpp"
#include "Vertices.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "Object.h"

class TextComp : public Component
{
public:
    TextComp();
    TextComp(Object* obj, std::wstring text_string, Color4f color, vector2 size, BitmapFont& font);
    void Init(Object* obj) override;
    void Update(float dt) override;
    Text& GetText();
    float& Get_Timer()
    {
        return timer;
    }
    bool& Get_Need_To_Keep_Drawing()
    {
        return need_to_keep_drawing;
    }
private:
    BitmapFont      font{};
    Text text{};
    material textMaterial{};
    CameraView      view{};
    Vertices        lineVertices{};
    float seconds = 0;
    int width = 1280;
    int height = 720;
    vector2 text_position;
    vector2 text_size;
    float timer = 0.1f;
    Color4f color;
    bool need_to_keep_drawing = false;
};