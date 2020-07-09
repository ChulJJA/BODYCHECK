/*
 * Author		:Jeesoo Kim
 * File			:Component_Text.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Component Text
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Text.h"
#include "GL.hpp"

TextComp::TextComp(Object* obj, std::wstring text_string, Color4f color, vector2 size, BitmapFont& font)
{
    m_owner = obj;

    textMaterial.shader = &SHADER::textured();
    textMaterial.color4fUniforms[SHADER::Uniform_Color] = color;

    text_size = size;
    text.SetFont(font);
    text.SetString(text_string);
    const float left = -width * 0.5f + m_owner->GetTransform().GetTranslation().x;
    const float top = height * 0.5f - m_owner->GetTransform().GetTranslation().y;

    float zoom = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetZoom();
    matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
    mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
    mat_ndc *= m_owner->GetTransform().GetModelToWorld();
    textMaterial.matrix3Uniforms["to_ndc"] =
        mat_ndc * MATRIX3::build_scale(size.x / 100.0f, size.y / 100.0f);
    for (auto& vertices_texture_pair : text.GetVerticesWithMatchingTextures())
    {
        Vertices& text_vertices = *vertices_texture_pair.first;
        const Texture* text_texture = vertices_texture_pair.second;
        textMaterial.textureUniforms.insert_or_assign(SHADER::Uniform_Texture, texture_uniform{ text_texture });
        Graphic::GetGraphic()->Draw(text_vertices, textMaterial);
    }

    this->color = color;
}

void TextComp::Init(Object* obj)
{
    m_owner = obj;
}

void TextComp::Update(float dt)
{
    if (this->need_to_keep_drawing)
    {
        const float left = -width * 0.5f + m_owner->GetTransform().GetTranslation().x;
        const float top = height * 0.5f - m_owner->GetTransform().GetTranslation().y;

        float zoom = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetZoom();
        matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
        mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
        mat_ndc *= m_owner->GetTransform().GetModelToWorld();
        textMaterial.matrix3Uniforms["to_ndc"] =
            mat_ndc * MATRIX3::build_scale(text_size.x / 100.0f, text_size.y / 100.0f);

        for (auto& vertices_texture_pair : text.GetVerticesWithMatchingTextures())
        {
            Vertices& text_vertices = *vertices_texture_pair.first;
            const Texture* text_texture = vertices_texture_pair.second;
            textMaterial.textureUniforms.insert_or_assign(SHADER::Uniform_Texture, texture_uniform{ text_texture });
            Graphic::GetGraphic()->Draw(text_vertices, textMaterial);
        }
    }
    if (this->timer > 0.f && !this->need_to_keep_drawing)
    {
        const float left = -width * 0.5f + m_owner->GetTransform().GetTranslation().x;
        const float top = height * 0.5f - m_owner->GetTransform().GetTranslation().y;

        float zoom = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetZoom();
        matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
        mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
        mat_ndc *= m_owner->GetTransform().GetModelToWorld();
        textMaterial.matrix3Uniforms["to_ndc"] =
            mat_ndc * MATRIX3::build_scale(text_size.x / 100.0f, text_size.y / 100.0f);

        for (auto& vertices_texture_pair : text.GetVerticesWithMatchingTextures())
        {
            Vertices& text_vertices = *vertices_texture_pair.first;
            const Texture* text_texture = vertices_texture_pair.second;
            textMaterial.textureUniforms.insert_or_assign(SHADER::Uniform_Texture, texture_uniform{ text_texture });
            Graphic::GetGraphic()->Draw(text_vertices, textMaterial);
        }

        timer -= dt;
    }
}

Text& TextComp::GetText()
{
    return text;
}