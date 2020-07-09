/*
 * Author		:Suhwan Kim
 * File			:Tutorial.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Tutorial
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Windows.h"
#include "Tutorial.hpp"
#include "Referee.h"
#include "Component_Text.h"
#include "Player_Ui.h"
#include "Engine.hpp"
#include "UsefulTools.hpp"
#include "Application.hpp"
#include "Loading_Scene.h"
#include "ObjectSetter.h"
#include "Audience.h"
#include "Input.h"
#include "Option.h"
#include "StateManager.h"


#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32 
#include <GLFW/glfw3native.h>
#include <mutex>
#include "Physics.h"

namespace
{
	Referee* referee = nullptr;
	StateManager* state_manager = nullptr;
	ObjectManager* object_manager = nullptr;

}

void Tutorial::Load()
{
	if (sound.isInitialized == false)
	{
		sound.Initialize();
	}
	Loading_Scene* loading = new Loading_Scene();
	loading->Load();

	HDC hdc = wglGetCurrentDC();//GetDC(glfwGetWin32Window(Application::Get_Application()->Get_Window()));
	const HGLRC main_context = wglGetCurrentContext();
	HGLRC loading_context = wglCreateContext(hdc);
	wglShareLists(main_context, loading_context);


	std::thread loading_thread([&]()
		{
			BOOL check = wglMakeCurrent(hdc, loading_context);
			loading->Update(0.05f);
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(loading_context);
		}
	);

	{
		dt_refreshed = false;
		timer_deleted = false;

		prev_timer = nullptr;
		transition_timer = 4.9f;
		current_state = GameState::Tutorial;
		referee = Referee::Get_Referee();
		object_manager = ObjectManager::GetObjectManager();
		state_manager = StateManager::GetStateManager();
		Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
		FMOD_BOOL isPlayingBGM;
		FMOD_BOOL isPlayingBGM2;
		FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM)], &isPlayingBGM);
		FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &isPlayingBGM2);
		if (isPlayingBGM == true)
		{
			sound.Stop(SOUND::BGM);
		}
		if (isPlayingBGM2 == false)
		{
			sound.Play(SOUND::BGM2);
		}


		SetArena();

		referee->Init();
	
		Player_Second_UI = Make_Set_Ui("second_ui", "ui", "../Sprite/UI/pen_red_ui.png", { -500, -800 }, { 5.0f,5.0f }, Player_Second);
		Player_Third_UI = Make_Set_Ui("third_ui", "ui", "../Sprite/UI/pen_blue_ui.png", { 300, -800 }, { 5.0f,5.0f }, Player_Third);


		//Player_First = Make_Player("first", "player", "pen_green2", { 400.f, 400.f }, { 2.f, 2.f });
		Player_Second = Make_Player("second", "player", "pen_red2", { 400.f, -400.f }, { 2.f, 2.f });
		Player_Third = Make_Player("third", "player", "pen_blue2", { -400.f, 400.f }, { 2.f, 2.f });
		//Player_Fourth = Make_Player("fourth", "player", "pen_normal2", { -400.f, -400.f }, { 2.f, 2.f });

		//Player_First->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_First_UI);
		Player_Second->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Second_UI);
		Player_Third->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Third_UI);
		//Player_Fourth->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Fourth_UI);



		//Referee::Get_Referee()->Set_First_Ui(Player_First_UI);
		Referee::Get_Referee()->Set_Second_Ui(Player_Second_UI);
		Referee::Get_Referee()->Set_Third_Ui(Player_Third_UI);
		//Referee::Get_Referee()->Set_Fourth_Ui(Player_Fourth_UI);




		Graphic::GetGraphic()->get_need_update_sprite() = true;


		loading->Set_Done(false);
		if (loading_thread.joinable())
		{
			loading_thread.join();
		}

		sound.Play(SOUND::CountDown);
	}
}

void Tutorial::Update(float dt)
{
	FMOD_BOOL isBGMPlaying;

	FMOD_Channel_IsPlaying(sound.channel[1], &isBGMPlaying);
	if (dt_refreshed == true)
	{
		if (transition_timer > 0.f)
		{
			transition_timer -= dt;
			int timer_int = static_cast<int>(transition_timer);

			if (((transition_timer > 1.8f && transition_timer < 2.4f) ||
				((transition_timer > 3.6f && transition_timer < 4.2f)))
				&& timer_int > 1)
			{
				timer_int = 6;
			}
			else if (transition_timer < 1.f)
			{
				timer_int = 7;
			}

			Object* timer_obj = nullptr;
			Object* prev_timer_obj = nullptr;

			switch (timer_int)
			{
			case 1:
				timer_obj = ObjectManager::GetObjectManager()->Find_Object_By_Name("timer1");
				prev_timer = timer_obj;
				prev_timer_obj = ObjectManager::GetObjectManager()->Find_Object_By_Name("timer_erase");
			case 2:
			case 3:
				timer_obj = ObjectManager::GetObjectManager()->Find_Object_By_Name("timer2");
				prev_timer = timer_obj;
				prev_timer_obj = ObjectManager::GetObjectManager()->Find_Object_By_Name("timer_erase");
				break;
			case 4:
			case 5:
				timer_obj = ObjectManager::GetObjectManager()->Find_Object_By_Name("timer3");
				prev_timer = timer_obj;
				break;
			case 6:
				timer_obj = ObjectManager::GetObjectManager()->Find_Object_By_Name("timer_erase");
				timer_obj->Set_Need_To_Update(true);
				prev_timer->Set_Need_To_Update(false);
				break;
			case 7:
				timer_obj = ObjectManager::GetObjectManager()->Find_Object_By_Name("timer_start");
				timer_obj->Set_Need_To_Update(true);
				prev_timer->Set_Need_To_Update(false);

				vector2& scale = timer_obj->GetScale_Reference();
				scale.x += 0.3f;
				scale.y += 0.3f;
				break;
			}

			if (prev_timer_obj != nullptr)
			{
				prev_timer_obj->Set_Need_To_Update(false);
				timer_obj->Set_Need_To_Update(true);
			}
		}
		else
		{
			referee->Update(dt);

			if (timer_deleted == false)
			{
				std::vector<Object*> timers = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("timer");
				int size = timers.size();

				for (int i = 0; i < size; i++)
				{
					timers.at(i)->SetDeadCondition(true);
				}

				timer_deleted = true;
			}
		}
	}
	else
	{
		dt_refreshed = true;
	}

	//EventCheck();

	Pause();
}


void Tutorial::SetArena()
{
	Arena = new Object();
	Arena->Set_Name("arena");
	Arena->Set_Tag("arena");
	Arena->AddComponent(new Sprite(Arena, "../Sprite/IceGround2.png", { 0,-100 }, false));
	Arena->Set_Current_Sprite(Arena->Find_Sprite_By_Name("arena"));
	Arena->SetScale({ 35, 17 });
	ObjectManager::GetObjectManager()->AddObject(Arena);
}

void Tutorial::SetStaffAndExplanation()
{
	Explanation_Staff = new Object();
	Explanation_Staff->Set_Name("explanation_staff");
	Explanation_Staff->AddComponent(new Sprite(Explanation_Staff, "../Sprite/HowToPlay.png", { 1400, 0 }, false));
	Explanation_Staff->GetTransform().SetScale(9.f);
	ObjectManager::GetObjectManager()->AddObject(Explanation_Staff);

	/*Explanation_Text_First = new Object();
	Explanation_Text_First->Set_Name("explanation_text_first");
	Explanation_Text_First->AddComponent(new Sprite(Explanation_Text_First, "../Sprite/ExplanationTextFirst.png", { 1450, 0 }, false));
	Explanation_Text_First->GetTransform().SetScale({ 9.f, 9.f });
	Explanation_Text_First->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(Explanation_Text_First);

	Explanation_Text_Second = new Object();
	Explanation_Text_Second->Set_Name("explanation_text_second");
	Explanation_Text_Second->AddComponent(new Sprite(Explanation_Text_Second, "../Sprite/ExplanationTextSecond.png", { 1450, 0 }, false));
	Explanation_Text_Second->GetTransform().SetScale({ 9.f, 9.f });
	Explanation_Text_Second->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(Explanation_Text_Second);

	Explanation_Text_Third = new Object();
	Explanation_Text_Third->Set_Name("explanation_text_third");
	Explanation_Text_Third->AddComponent(new Sprite(Explanation_Text_Third, "../Sprite/ExplanationTextThird.png", { 1450, 0 }, false));
	Explanation_Text_Third->GetTransform().SetScale({ 9.f, 9.f });
	Explanation_Text_Third->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(Explanation_Text_Third);

	Explanation_Text_Fourth = new Object();
	Explanation_Text_Fourth->Set_Name("explanation_text_second");
	Explanation_Text_Fourth->AddComponent(new Sprite(Explanation_Text_Fourth, "../Sprite/ExplanationTextSecond.png", { 1450, 0 }, false));
	Explanation_Text_Fourth->GetTransform().SetScale({ 9.f, 9.f });
	Explanation_Text_Fourth->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	ObjectManager::GetObjectManager()->AddObject(Explanation_Text_Fourth);*/
}



void Tutorial::EventCheck()
{
	/* if (Player_First->Get_Hitted_By || Player_Second->Get_Hitted_By || Player_Third->Get_Hitted_By
		 || Player_Fourth->Get_Hitted_By)
	 {
		 ObjectHover(Explanation_Text_First, Explanation_Text_Second);
	 }
	 else if (referee->Get_Player_First_Life < 5 || referee->Get_Player_Second_Life < 5
		 || referee->Get_Player_Third_Life < 5 || referee->Get_Player_Fourth_Life < 5)
	 {
		 ObjectHover(Explanation_Text_Second, Explanation_Text_Third);
	 }*/


}

void Tutorial::Pause()
{
	if (input.Is_Key_Pressed(GLFW_KEY_P))
	{
		sound.Play(SOUND::Click);
		is_pause = true;
	}
}

void Tutorial::Clear()
{
	object_manager->Clear();
}

