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
#include "Component_Collision.h"
#include "Referee.h"
#include "Component_Text.h"
#include "Player_Ui.h"
#include "Engine.hpp"
#include "UsefulTools.hpp"
#include "Application.hpp"
#include "Loading_Scene.h"
#include "StateManager.h"


#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32 
#include <GLFW/glfw3native.h>
#include <mutex>

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

	HDC hdc = GetDC(glfwGetWin32Window(Application::Get_Application()->Get_Window()));
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
		state_manager = StateManager::GetStateManager();
		current_state = GameState::Tutorial;
		referee = Referee::Get_Referee();

		object_manager = ObjectManager::GetObjectManager();
		Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);

		sound.Stop(SOUND::BGM);
		sound.Play(SOUND::BGM2);


		SetArena();
		SetFirstPlayer();
		SetSecondPlayer();
		SetThirdPlayer();
		SetFourthPlayer();
		SetStaffAndExplanation();



		referee->AddComponent(new Collision());
		//referee->SetTutorialLife();
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
	EventCheck();
}


void Tutorial::SetArena()
{
	Arena = new Object();
	Arena->Set_Name("arena");
	Arena->Set_Tag("arena");
	Arena->AddComponent(new Sprite(Arena, "../Sprite/IceGround.png", { 0,0 }, false));
	Arena->SetScale({ 20, 20 });
	ObjectManager::GetObjectManager()->AddObject(Arena);
}

void Tutorial::SetFirstPlayer()
{
	Player_First = new Object();
	Player_First->Set_Name("first");
	Player_First->Set_Tag("player");
	Player_First->AddComponent(new Player());
	Player_First->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
	Player_First->AddComponent(new Sprite(Player_First, "../Sprite/pen_green.png", { 400,400 }));
	Player_First->AddComponent(new Physics());
	Player_First->GetTransform().SetScale({ 3.f,3.f });

	ObjectManager::GetObjectManager()->AddObject(Player_First);

	Player_First_Text = Make_Set_Text("red_text", "text", { 200,0 }, Player_First, { 0,1,0,1 }, { 150,150 }, &font);
	Player_First_UI = Make_Set_Ui("first_ui", "ui", "../sprite/pen_green.png", { 1200, 800 }, { 4.0f,4.0f }, Player_First);
	Player_First->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_First_UI);

	Referee::Get_Referee()->Set_First_Text(Player_First_Text);
	Referee::Get_Referee()->Set_First_Ui(Player_First_UI);
}

void Tutorial::SetSecondPlayer()
{
	Player_Second = new Object();
	Player_Second->Set_Name("second");
	Player_Second->Set_Tag("player");
	Player_Second->AddComponent(new Player());
	Player_Second->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
	Player_Second->AddComponent(new Sprite(Player_Second, "../Sprite/pen_red.png", { -400,400 }));
	Player_Second->AddComponent(new Physics());
	Player_Second->GetTransform().SetScale({ 3.f,3.f });

	ObjectManager::GetObjectManager()->AddObject(Player_Second);

	Player_Second_Text = Make_Set_Text("green_text", "text", { 200,-200 }, Player_Second, { 1,0,0,1 }, { 150,150 }, &font);
	Player_Second_UI = Make_Set_Ui("second_ui", "ui", "../sprite/pen_red.png", { 1200, -600 }, { 4.0f,4.0f }, Player_Second);
	Player_Second->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Second_UI);

	Referee::Get_Referee()->Set_Second_Text(Player_Second_Text);
	Referee::Get_Referee()->Set_Second_Ui(Player_Second_UI);
}

void Tutorial::SetThirdPlayer()
{
	Player_Third = new Object();
	Player_Third->Set_Name("third");
	Player_Third->Set_Tag("player");
	Player_Third->AddComponent(new Player());
	Player_Third->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
	Player_Third->AddComponent(new Sprite(Player_Third, "../Sprite/pen_purple.png", { 400,-400 }));
	Player_Third->AddComponent(new Physics());
	Player_Third->GetTransform().SetScale({ 3.f,3.f });

	ObjectManager::GetObjectManager()->AddObject(Player_Third);

	Player_Third_Text = Make_Set_Text("blue_text", "text", { 200,-400 }, Player_Third, { 0.54,0,1,1 }, { 150,150 }, &font);
	Player_Third_UI = Make_Set_Ui("third_ui", "ui", "../sprite/pen_purple.png", { -1600, 800 }, { 4.0f,4.0f }, Player_Third);
	Player_Third->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Third_UI);

	Referee::Get_Referee()->Set_Third_Text(Player_Third_Text);
	Referee::Get_Referee()->Set_Third_Ui(Player_Third_UI);
}

void Tutorial::SetFourthPlayer()
{
	Player_Fourth = new Object();
	Player_Fourth->Set_Name("fourth");
	Player_Fourth->Set_Tag("player");
	Player_Fourth->AddComponent(new Player());
	Player_Fourth->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
	Player_Fourth->AddComponent(new Sprite(Player_Fourth, "../Sprite/pen_normal.png", { -400,-400 }));
	Player_Fourth->AddComponent(new Physics());
	Player_Fourth->GetTransform().SetScale({ 3.f,3.f });

	ObjectManager::GetObjectManager()->AddObject(Player_Fourth);

	Player_Fourth_Text = Make_Set_Text("yellow_text", "text", { 200,-400 }, Player_Fourth, { 0.5,0.5,0.5,1 }, { 150,150 }, &font);
	Player_Fourth_UI = Make_Set_Ui("fourth_ui", "ui", "../sprite/pen_normal.png", { -1600, -600 }, { 4.0f,4.0f }, Player_Fourth);
	Player_Fourth->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Fourth_UI);

	Referee::Get_Referee()->Set_Fourth_Text(Player_Fourth_Text);
	Referee::Get_Referee()->Set_Fourth_Ui(Player_Fourth_UI);
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
