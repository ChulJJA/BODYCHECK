/*
 * Author		:Jeesoo Kim
 * File			:Graphic.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for refresh screen & background color.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
#ifdef _DEBUG
	//Application::Get_Application()->Imgui_Init();
#endif

    glClearColor(0.31372 ,0.73725,0.8745,1);
}

void Graphic::Update(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef _DEBUG
	//Application::Get_Application()->Imgui_Update();
#endif

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
	
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 84);

	GL::end_drawing();

}
