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
#include "Message_Manager.h"
#include "Editor.h"

 //
 //#define GLFW_EXPOSE_NATIVE_WGL
 //#define GLFW_EXPOSE_NATIVE_WIN32 
 //#include <GLFW/glfw3native.h>
 //#include <mutex>
 //#include "Physics.h"

namespace
{
	Referee* referee = nullptr;
	StateManager* state_manager = nullptr;
	ObjectManager* object_manager = nullptr;
	Editor* editor = nullptr;
}

void Tutorial::Load()
{
	if (sound.isInitialized == false)
	{
		sound.Initialize();
	}
	current_state = GameState::Tutorial;
	r_u_sure = false;
	r_u_sure_come = false;
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
		
		editor = new Editor();
		referee->Init();
		editor->Init();
		editor->Set_Visible(true);

		//Player_Second_UI = Make_Set_Ui("second_ui", "ui", "../Sprite/UI/pen_red_ui.png", { -500, -800 }, { 5.0f,5.0f }, Player_Second);
		//Player_Third_UI = Make_Set_Ui("third_ui", "ui", "../Sprite/UI/pen_blue_ui.png", { 300, -800 }, { 5.0f,5.0f }, Player_Third);


		Player_Second = Make_Player("second", "player", "pen_red2", { -800.f, 0.f }, { 4.f, 4.f }, true);
		Player_Third = Make_Player("third", "player", "pen_blue2", { 800.f,0.f }, { 4.f, 4.f }, true);


		Player_Second->Get_Belongs_Objects().clear();
		Player_Third->Get_Belongs_Objects().clear();

		/*Player_Second->Set_Need_To_Update(false);
		Player_Second->SetNeedCollision(false);
		Player_Third->Set_Need_To_Update(false);
		Player_Third->SetNeedCollision(false);*/

		//Player_Second->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Second_UI);
		//Player_Third->GetComponentByTemplate<Player>()->Set_This_UI_info(Player_Third_UI);



		//Referee::Get_Referee()->Set_First_Ui(Player_First_UI);
		//Referee::Get_Referee()->Set_Second_Ui(Player_Second_UI);
		//Referee::Get_Referee()->Set_Third_Ui(Player_Third_UI);
		//Referee::Get_Referee()->Set_Fourth_Ui(Player_Fourth_UI);
		Referee::Get_Referee()->Set_Curr_Sec_Player(Player_Second);
		Referee::Get_Referee()->Set_Curr_Third_Player(Player_Third);



		Graphic::GetGraphic()->get_need_update_sprite() = true;


		loading->Set_Done(false);
		if (loading_thread.joinable())
		{
			loading_thread.join();
		}

	}
	make_sure_dialogue = new Object();
	make_sure_dialogue->AddComponent(new Sprite(make_sure_dialogue, "../Sprite/rusure_yes.png", { 0.f, 0.f }, false, Sprite_Type::R_U_SURE_YES), "rusureyes", false);
	make_sure_dialogue->AddComponent(new Sprite(make_sure_dialogue, "../Sprite/rusure_no.png", { 0.f, 0.f }, false, Sprite_Type::R_U_SURE_NO), "rusureno", false);
	make_sure_dialogue->GetTransform().SetScale({ 10.f, 6.f });
	make_sure_dialogue->Set_Need_To_Update(false);
	object_manager->AddObject(make_sure_dialogue);
}

void Tutorial::Update(float dt)
{
	FMOD_BOOL isBGMPlaying;

	FMOD_Channel_IsPlaying(sound.channel[1], &isBGMPlaying);

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

	//EventCheck();

	editor->Update(dt);

	if(r_u_sure)
	{
		is_next = true;
		next_level = "Menu";
		Clear();
	}
	
	BackToMenu();
}

void Tutorial::UnLoad()
{
	next_level = {};
	is_next = false;
	//delete referee;
	///delete object_manager;
}

void Tutorial::SetArena()
{
	Arena = new Object();
	Arena->Set_Name("arena");
	Arena->Set_Tag("arena");
	Arena->AddComponent(new Sprite(Arena, "../Sprite/IceGround2.png", { 0,-100 }, false));
	Arena->Set_Current_Sprite(Arena->Find_Sprite_By_Name("arena"));
	Arena->SetScale({ 35, 17 });
	//ObjectManager::GetObjectManager()->AddObject(Arena);
}

void Tutorial::SetStaffAndExplanation()
{
	/*Explanation_Staff = new Object();
	Explanation_Staff->Set_Name("explanation_staff");
	Explanation_Staff->AddComponent(new Sprite(Explanation_Staff, "../Sprite/HowToPlay.png", { 1400, 0 }, false));
	Explanation_Staff->GetTransform().SetScale(9.f);
	ObjectManager::GetObjectManager()->AddObject(Explanation_Staff);*/

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

void Tutorial::BackToMenu()
{
	if (r_u_sure_come)
	{
		Component* r_u_sure_current_sprite = make_sure_dialogue->Get_Current_Sprite();
		Component* r_u_sure_yes_sprite = make_sure_dialogue->Find_Sprite_By_Type(Sprite_Type::R_U_SURE_YES);
		Component* r_u_sure_no_sprite = make_sure_dialogue->Find_Sprite_By_Type(Sprite_Type::R_U_SURE_NO);

		if (make_sure_dialogue->Get_Need_To_Update() == false)
		{
			make_sure_dialogue->Change_Sprite(make_sure_dialogue->Find_Sprite_By_Type(Sprite_Type::R_U_SURE_YES));
			make_sure_dialogue->Set_Need_To_Update(true);
		}

		if (r_u_sure_current_sprite != nullptr && r_u_sure_yes_sprite != nullptr && r_u_sure_no_sprite != nullptr)
		{
			if (input.Is_Key_Triggered(GLFW_KEY_RIGHT))
			{
				if (r_u_sure_current_sprite == r_u_sure_yes_sprite)
				{
					make_sure_dialogue->Change_Sprite(r_u_sure_no_sprite);
				}
			}
			else if (input.Is_Key_Triggered(GLFW_KEY_LEFT))
			{
				if (r_u_sure_current_sprite == r_u_sure_no_sprite)
				{
					make_sure_dialogue->Change_Sprite(r_u_sure_yes_sprite);
				}
			}

			if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && r_u_sure_current_sprite == r_u_sure_yes_sprite)
			{
				r_u_sure_come = false;
				r_u_sure = true;
			}
			else if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && r_u_sure_current_sprite == r_u_sure_no_sprite)
			{
				r_u_sure_come = false;
				make_sure_dialogue->Set_Need_To_Update(false);
			}
		}
	}
	if (input.Is_Key_Pressed(GLFW_KEY_ESCAPE))
	{
		r_u_sure_come = true;
	}
}

void Tutorial::Clear()
{
	Message_Manager::Get_Message_Manager()->Get_Messages().clear();
	ObjectManager::GetObjectManager()->Get_Objects().clear();
	//object_manager->Clear();

	if (editor != nullptr)
	{
		editor = nullptr;
	}
}

