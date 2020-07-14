/*
 * Author		:Jeesoo Kim
 * File			:Graphic.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Graphic
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Graphic.h"
#include "Application.hpp"
#include "GL.hpp"

Graphic* Graphic::graphic = nullptr;

Graphic* Graphic::GetGraphic()
{
    if (graphic == nullptr)
        graphic = new Graphic();

    return graphic;
}

void Graphic::Init()
{
    glewInit();
    glEnable(GL_DEPTH | GL_BLEND);
    view.Init();


    glClearColor(0.31372 ,0.73725,0.8745,1);
}

void Graphic::Update(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    seconds += dt;

    view.Update(dt);
}

void Graphic::Delete()
{
	graphic = nullptr;
}

void Graphic::Draw(Vertices& shape, material material)
{
    GL::draw(shape, material);

    GL::end_drawing();
}

void Graphic::Instancing_Draw(Vertices& shape, material material)
{
	GL::draw_instance(shape, material);

}

void Graphic::Render()
{
    glVertexAttribDivisor(0, 0); 
    glVertexAttribDivisor(1, 1); 
    glVertexAttribDivisor(2, 1); 
	
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 30);

	GL::end_drawing();

}
