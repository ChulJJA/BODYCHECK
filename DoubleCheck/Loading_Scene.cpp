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
#include "Input.h"
#include "Engine.hpp"

namespace 
{
	StateManager* state_manager = nullptr;
}


Loading_Scene::Loading_Scene() : image(nullptr), image2(nullptr)
{

}

void Loading_Scene::Load()
{
	FMOD_BOOL isPlayingBGM;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM)], &isPlayingBGM);
	if (!isPlayingBGM)
	{
		sound.Play(SOUND::BGM);
	}
	
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
			{ 200.f, 200.f }, { 255,255,255,255 }, Sprite_Type::Loading));
		image->AddComponent(new Sprite(image, "../sprite/loading_press.png", true, 2, 2, { 0.f, 0.f },
			{ 200.f, 200.f }, { 255,255,255,255 }, Sprite_Type::Loading_Press));
		image->SetScale(vector2{ 19.f , 12.f});

		bool is_done = true;
		while (is_done)
		{
			glfwSwapBuffers(Application::Get_Application()->Get_Window());
			glfwPollEvents();
			Graphic::GetGraphic()->Update(dt);
			GL::set_clear_color({ 0.31372, 0.73725, 0.8745, 1 });

			if (done)
			{
				image->Find_Sprite_By_Type(Sprite_Type::Loading)->Update(dt);
			}
			else
			{
				image->Find_Sprite_By_Type(Sprite_Type::Loading_Press)->Update(dt);

				if (GetKeyState(VK_SPACE) & 0x8000)
				{
					sound.Play(SOUND::GameStart);
					Sleep(1000);
					is_done = false;
					sound.UnLoad();
					sound.Initialize();
					FMOD_BOOL isPlayingBGM;
					FMOD_BOOL isPlayingBGM2;
					FMOD_BOOL isPauseBGMPlaying;
					FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::PauseBGM)], &isPauseBGMPlaying);
					FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM)], &isPlayingBGM);
					FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &isPlayingBGM2);
					if (isPlayingBGM == true)
					{
						sound.Stop(SOUND::BGM);
					}
					if (isPauseBGMPlaying)
					{
						sound.Stop(SOUND::PauseBGM);
					}
					if (isPlayingBGM2 == false)
					{
						sound.Play(SOUND::BGM2);
						sound.currentBGM = SOUND::BGM2;
					}
				}
			}
		}

	}
	else if (state_manager->GetCurrentState()->GetStateInfo() == GameState::Tutorial)
	{
		image2->AddComponent(new Sprite(image2, "../Sprite/Credit2.png", { 0, 0 }, false));
		image2->SetScale({ 38.f , 21.f});

		while (done)
		{
			SetFocus(GetFocus());
			glfwSwapBuffers(Application::Get_Application()->Get_Window());
			glfwPollEvents();
			Graphic::GetGraphic()->Update(dt);
			GL::set_clear_color({ 0.31372, 0.73725, 0.8745, 1 });
			image2->GetComponentByTemplate<Sprite>()->Update(dt);
		}
	}
}

void Loading_Scene::UnLoad()
{
	next_level = {};
	is_next = false;
}
