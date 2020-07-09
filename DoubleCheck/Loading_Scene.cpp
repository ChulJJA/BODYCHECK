/*
 * Author		:Sangmin Kim
 * File			:Loading_Scene.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Loading Scene
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Loading_Scene.h"
#include "Object.h"
#include "Component_Sprite.h"
#include "Graphic.h"
#include "Application.hpp"
#include "Level1.h"
#include "StateManager.h"


#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32 
#include "GLFW/glfw3native.h"

#include <Windows.h>
#include <consoleapi2.h>
#include <consoleapi3.h>
#include "GL.hpp"

namespace 
{
	StateManager* state_manager = nullptr;
}


Loading_Scene::Loading_Scene() : image(nullptr), image2(nullptr)
{

}

void Loading_Scene::Load()
{
	state_manager = StateManager::GetStateManager();
	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
	done = true;

	image = new Object();
	image->Set_Name("loading_image");
	image->Set_Tag("image");

	image2 = new Object();
	image2->Set_Name("loading_howtoplay_image");
	image2->Set_Tag("image");
}

void Loading_Scene::Update(float dt)
{
	if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Game)
	{
		
		image->AddComponent(new Sprite(image, "../sprite/loading.png", true, 7, 4, { 0.f, 0.f },
			{ 200.f, 200.f }, { 255,255,255,255 }));
		image->SetScale(vector2{ 19.f , 12.f});

		while (done)
		{
			glfwSwapBuffers(Application::Get_Application()->Get_Window());
			glfwPollEvents();
			Graphic::GetGraphic()->Update(dt);
			GL::set_clear_color({ 0.31372, 0.73725, 0.8745, 1 });
			image->GetComponentByTemplate<Sprite>()->Update(dt);
		}

	}
	else if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Tutorial)
	{
		image2->AddComponent(new Sprite(image2, "../Sprite/HowToPlay.png", { 0, 0 }, false));
		image2->SetScale(20.f);

		while (done)
		{
			glfwSwapBuffers(Application::Get_Application()->Get_Window());
			glfwPollEvents();
			Graphic::GetGraphic()->Update(dt);
			GL::set_clear_color({ 0.31372, 0.73725, 0.8745, 1 });
			image2->GetComponentByTemplate<Sprite>()->Update(dt);
		}
	}


	//image->AddComponent(new Sprite(image, "../sprite/loadingscene.png", { 0.f, 0.f }));
}

void Loading_Scene::UnLoad()
{
	next_level = {};
	is_next = false;
}
