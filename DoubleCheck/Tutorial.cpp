/*
 * Author		:Suwhan Kim
 * File			:Tutorial.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/02/22
 * Description	:This file is for intialize the stuff required on the prototype.
 *				 There are Player objects, refree, items, text, ui information.
 *
 *				 copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
	Loading_Scene* loading = new Loading_Scene();
	loading->Load();

	HDC hdc = wglGetCurrentDC();//GetDC(glfwGetWin32Window(Application::Get_Application()->Get_Window()));
	HGLRC main_context = wglGetCurrentContext();
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
		current_state = GameState::Tutorial;
		referee = Referee::Get_Referee();
		object_manager = ObjectManager::GetObjectManager();
		state_manager = StateManager::GetStateManager();
		Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);

		sound.Stop(SOUND::BGM);
		sound.Play(SOUND::BGM2);

		SetArena();
		//SetStaffAndExplanation();
		Player_First_UI = Make_Set_Ui("first_ui", "ui", "../Sprite/UI/pen_green_ui.png", { -1300, -800 }, { 5.0f,5.0f }, Player_First);
		Player_Second_UI = Make_Set_Ui("second_ui", "ui", "../Sprite/UI/pen_red_ui.png", { -500, -800 }, { 5.0f,5.0f }, Player_Second);
		Player_Third_UI = Make_Set_Ui("third_ui", "ui", "../Sprite/UI/pen_blue_ui.png", { 300, -800 }, { 5.0f,5.0f }, Player_Third);
		Player_Fourth_UI = Make_Set_Ui("fourth_ui", "ui", "../Sprite/UI/pen_normal_ui.png", { 1100, -800 }, { 5.0f,5.0f }, Player_Fourth);

		Player_First = Make_Player("first", "player", "pen_green2", { 400.f, 400.f }, { 2.f, 2.f });
		Player_Second = Make_Player("second", "player", "pen_red2", { 400.f, -400.f }, { 2.f, 2.f });
		Player_Third = Make_Player("third", "player", "pen_blue2", { -400.f, 400.f }, { 2.f, 2.f });
		Player_Fourth = Make_Player("fourth", "player", "pen_normal2", { -400.f, -400.f }, { 2.f, 2.f });

		Player_First->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_First_UI);
		Player_Second->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Second_UI);
		Player_Third->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Third_UI);
		Player_Fourth->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Fourth_UI);

		

		Referee::Get_Referee()->Set_First_Ui(Player_First_UI);
		Referee::Get_Referee()->Set_Second_Ui(Player_Second_UI);
		Referee::Get_Referee()->Set_Third_Ui(Player_Third_UI);
		Referee::Get_Referee()->Set_Fourth_Ui(Player_Fourth_UI);



		referee->Init();
		Graphic::GetGraphic()->get_need_update_sprite() = true;
	}

	loading->Set_Done(false);
	if (loading_thread.joinable())
	{
		loading_thread.join();
	}
}

void Tutorial::Update(float dt)
{
	referee->Update(dt);
	//EventCheck();
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

