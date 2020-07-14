/*
 * Author		:Sangmin Kim
 * File			:Level1.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for level1
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include <fstream>
#include <sstream>
#include "Windows.h"
#include "Level1.h"
#include "Referee.h"
#include "Component_Text.h"
#include "Engine.hpp"
#include "Loading_Scene.h"
#include "Application.hpp"
#include "ObjectSetter.h"
#include "Audience.h"
#include "Input.h"
#include "Message_Manager.h"
#include "Option.h"
#include "StateManager.h"
#include "Editor.h"
#include "gl.hpp"
#include "File_Driven_Manager.h"
#include "Gamepad.hpp"

using namespace std;

namespace
{
	Referee* referee = nullptr;
	ObjectManager* object_manager = nullptr;
	StateManager* state_manager = nullptr;
	Editor* editor = nullptr;
	File_Driven_Manager file_driven;
	Gamepad* gamepadManager = nullptr;
	Gamepad* gamepadManagerSec = nullptr;
	
}

void Level1::Load()
{
	if (sound.isInitialized == false)
	{
		sound.Initialize();
	}
	Loading_Scene* loading = new Loading_Scene();
	loading->Load();
	GL::set_clear_color({ 0.31372, 0.73725, 0.8745, 1 });


	HDC hdc = wglGetCurrentDC();
	const HGLRC main_context = wglGetCurrentContext();
	HGLRC loading_context = wglCreateContext(hdc);
	wglShareLists(main_context, loading_context);

	std::thread loading_thread([&]()
		{
			wglMakeCurrent(hdc, loading_context);
			loading->Update(0.05f);
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(loading_context);
		}
	);

	showing_editor = true;
	dt_refreshed = false;
	timer_deleted = false;
	prev_timer = nullptr;
	arena = nullptr;
	editor = nullptr;

	current_state = GameState::Game;
	transition_timer = 4.9f;
	referee = Referee::Get_Referee();
	object_manager = ObjectManager::GetObjectManager();
	state_manager = StateManager::GetStateManager();
	gamepadManager = Gamepad::getGamepad();
	gamepadManagerSec = Gamepad::getGamepadSecond();
	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);

	arena = new Object();
	arena->Set_Name("arena");
	arena->Set_Tag("arena");
	arena->AddComponent(new Sprite(arena, "../Sprite/IceGround2.png", { 0,-100 }, false), "arena");
	arena->Set_Current_Sprite(arena->Find_Sprite_By_Name("arena"));
	arena->SetScale({ 35, 17 });

	Object* fire1 = new Object();
	fire1->Set_Name("fire");
	fire1->Set_Tag("fire");
	fire1->AddComponent(new Sprite(fire1, "../Sprite/fire.png", true, 5, 15, { -1600.f,800.f }, { 100.f, 100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "fire", true);
	fire1->Set_Current_Sprite(fire1->Find_Sprite_By_Type(Sprite_Type::None));
	fire1->SetScale(3.f);

	Object* fire2 = new Object();
	fire2->Set_Name("fire");
	fire2->Set_Tag("fire");
	fire2->AddComponent(new Sprite(fire2, "../Sprite/fire.png", true, 5, 15, { 1600.f,800.f }, { 100.f, 100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "fire", true);
	fire2->Set_Current_Sprite(fire2->Find_Sprite_By_Type(Sprite_Type::None));
	fire2->SetScale(3.f);

	ObjectManager::GetObjectManager()->AddObject(arena);
	ObjectManager::GetObjectManager()->AddObject(fire1);
	ObjectManager::GetObjectManager()->AddObject(fire2);

	aud = Get_Audience();
	file_driven.Get_Player_Info("../Data/Objects/player_sec.txt", player_sec_pos, player_sec_scale, player_sec_sprite_path);
	file_driven.Get_Player_Info("../Data/Objects/player_third.txt", player_third_pos, player_third_scale, player_third_sprite_path);
	Referee::Get_Referee()->Set_Sec_Player_Info(player_sec_pos, player_sec_scale, player_sec_sprite_path);
	Referee::Get_Referee()->Set_Third_Player_Info(player_third_pos, player_third_scale, player_third_sprite_path);

	referee->Init();

	player_second_ui = Make_Set_Ui("second_ui", "ui", "../Sprite/UI/pen_red_ui.png", { -500, -800 }, { 5.0f,5.0f }, player_sec);
	player_third_ui = Make_Set_Ui("third_ui", "ui", "../Sprite/UI/pen_blue_ui.png", { 300, -800 }, { 5.0f,5.0f }, player_third);

	player_sec = Make_Player("second", "player", player_sec_sprite_path, player_sec_pos, player_sec_scale);
	player_third = Make_Player("third", "player", player_third_sprite_path, player_third_pos, player_third_scale);

	player_sec->GetComponentByTemplate<Player>()->Set_This_UI_info(player_second_ui);
	player_third->GetComponentByTemplate<Player>()->Set_This_UI_info(player_third_ui);

	Referee::Get_Referee()->Set_Second_Ui(player_second_ui);
	Referee::Get_Referee()->Set_Third_Ui(player_third_ui);
	Referee::Get_Referee()->Set_Curr_Sec_Player(player_sec);
	Referee::Get_Referee()->Set_Curr_Third_Player(player_third);
	Graphic::GetGraphic()->get_need_update_sprite() = true;

	loading->Set_Done(false);
	if (loading_thread.joinable())
	{
		loading_thread.join();
	}
	sound.Play(SOUND::CountDown);
}

void Level1::Update(float dt)
{
	FMOD_BOOL isPauseBGMPlaying;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::PauseBGM)], &isPauseBGMPlaying);

	if (isPauseBGMPlaying)
	{
		sound.Stop(SOUND::PauseBGM);
	}
	if (dt_refreshed == true)
	{
		if (transition_timer > 0.f)
		{
			transition_timer -= dt;

			int timer_in_int = (int)transition_timer;


			if (((transition_timer > 1.8f && transition_timer < 2.4f) ||
				((transition_timer > 3.6f && transition_timer < 4.2f)
					)) && timer_in_int > 1)
			{
				timer_in_int = 6;
			}
			else if (transition_timer < 1.f)
			{
				timer_in_int = 7;
			}

			Object* timer_obj = nullptr;
			Object* prev_timer_obj = nullptr;

			switch (timer_in_int)
			{
			case 1:
				timer_obj = ObjectManager::GetObjectManager()->Find_Object_By_Name("timer1");
				prev_timer = timer_obj;
				prev_timer_obj = ObjectManager::GetObjectManager()->Find_Object_By_Name("timer_erase");
				break;
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

				for (int i = 0; i < size; ++i)
				{
					timers[i]->SetDeadCondition(true);
				}

				timer_deleted = true;
			}
		}
	}
	else
	{
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(player_sec, nullptr, Message_Kind::Spawn_Object, 4.1f));
		Message_Manager::Get_Message_Manager()->Save_Message(new Message(player_third, nullptr, Message_Kind::Spawn_Object, 4.1f));

		dt_refreshed = true;
	}

	if (input.Is_Key_Pressed(GLFW_KEY_V))
	{
		if (editor == nullptr)
		{
			editor = new Editor();
			editor->Init();
		}

		if (editor != nullptr)
		{
			editor->Update(dt);
			if (showing_editor == false)
			{
				editor->Set_Visible(true);
				sound.Play(SOUND::EditorAppear);
			}
			showing_editor = true;
		}
	}
	else if (input.Is_Key_Released(GLFW_KEY_V))
	{
		if (editor != nullptr && showing_editor)
		{
			std::cout << "why" << std::endl;
			showing_editor = false;
			editor->Set_Visible(false);
		}
	}

	if(referee->isGameDone == true)
	{
		gameDoneTimer += dt;

	}
	if(gameDoneTimer >= 1)
	{
		Clear();
		referee->isGameDone = false;
		Graphic::GetGraphic()->Get_View().Set_Is_Zoom_End_False();
		is_next = true;
		next_level = "Menu";
		gameDoneTimer = 0;
	}
	Pause();
}

void Level1::UnLoad()
{
	//next_level = {};
	//is_next = false;
	//delete referee;
	//delete object_manager;  
}

void Level1::Pause()
{

	if (input.Is_Key_Pressed(GLFW_KEY_ESCAPE) || gamepadManager->GetButtonDown(xButtons.Back) || gamepadManagerSec->GetButtonDown(xButtons.Back))
	{
		sound.StopAllSFX();
		sound.Play(SOUND::Click);
		is_pause = true;
	}
}

void Level1::Clear()
{
	Message_Manager::Get_Message_Manager()->Get_Messages().clear();
	ObjectManager::GetObjectManager()->Get_Objects().clear();

	if (editor != nullptr)
	{
		editor = nullptr;
	}
}