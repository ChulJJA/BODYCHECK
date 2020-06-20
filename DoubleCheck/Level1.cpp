/*
 * Author		:Suwhan Kim
 * File			:Level1.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:This file is for intialize the stuff required on the prototype.
 *				 There are Player objects, refree, items, text, ui information.
 *
 *				 copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
using namespace std;

namespace
{
	Referee* referee = nullptr;
	ObjectManager* object_manager = nullptr;
	StateManager* state_manager = nullptr;
}

void Level1::Load()
{
	if (sound.isInitialized == false)
	{
		sound.Initialize();
	}
	Loading_Scene* loading = new Loading_Scene();
	loading->Load();

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

	current_state = GameState::Game;
	transition_timer = 4.9f;
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

	referee->Init();

	//player_first_ui = Make_Set_Ui("first_ui", "ui", "../Sprite/UI/pen_green_ui.png", { -1300, -800 }, { 5.0f,5.0f }, player);
	player_second_ui = Make_Set_Ui("second_ui", "ui", "../Sprite/UI/pen_red_ui.png", { -500, -800 }, { 5.0f,5.0f }, player_sec);
	player_third_ui = Make_Set_Ui("third_ui", "ui", "../Sprite/UI/pen_blue_ui.png", { 300, -800 }, { 5.0f,5.0f }, player_third);
	//player_fourth_ui = Make_Set_Ui("fourth_ui", "ui", "../Sprite/UI/pen_normal_ui.png", { 1100, -800 }, { 5.0f,5.0f }, player_forth);

	//player = Make_Player("first", "player", "pen_green2", { 400.f, 400.f }, { 2.f, 2.f });
	player_sec = Make_Player("second", "player", "pen_red2", {-800.f, 0.f}/*{ 400.f, -400.f }*/, { 4.f, 4.f });
	player_third = Make_Player("third", "player", "pen_blue2", {800.f, 0.f}/*{ -400.f, 400.f }*/, { 4.f, 4.f });
	//player_forth = Make_Player("fourth", "player", "pen_normal2", { -400.f, -400.f }, { 2.f, 2.f });

	//player->GetComponentByTemplate<Player>()->Set_This_UI_info(player_first_ui);
	player_sec->GetComponentByTemplate<Player>()->Set_This_UI_info(player_second_ui);
	player_third->GetComponentByTemplate<Player>()->Set_This_UI_info(player_third_ui);
	//player_forth->GetComponentByTemplate<Player>()->Set_This_UI_info(player_fourth_ui);

	//text = Make_Set_Text("red_text", "text", { 200,0 }, player, { 0,1,0,1 }, { 150,150 }, &font);
	//text_2 = Make_Set_Text("green_text", "text", { 200,-200 }, player_sec, { 1,0,0,1 }, { 150,150 }, &font);
	//text_3 = Make_Set_Text("blue_text", "text", { 200,-400 }, player_third, { 0.54,0,1,1 }, { 150,150 }, &font);
	//text_4 = Make_Set_Text("yellow_text", "text", { 200,-400 }, player_forth, { 0.5,0.5,0.5,1 }, { 150,150 }, &font);


	//player->GetComponentByTemplate<Player>()->Set_This_UI_info(player_first_ui);
	//player_sec->GetComponentByTemplate<Player>()->Set_This_UI_info(player_second_ui);
	//player_third->GetComponentByTemplate<Player>()->Set_This_UI_info(player_third_ui);
	//player_forth->GetComponentByTemplate<Player>()->Set_This_UI_info(player_fourth_ui);


	Referee::Get_Referee()->Set_First_Ui(player_first_ui);

	Referee::Get_Referee()->Set_Second_Ui(player_second_ui);
	Referee::Get_Referee()->Set_Third_Ui(player_third_ui);
	//Referee::Get_Referee()->Set_Fourth_Ui(player_fourth_ui);
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
	FMOD_BOOL isBGMPlaying;

	FMOD_Channel_IsPlaying(sound.channel[1], &isBGMPlaying);
	if(!isBGMPlaying)
	{
		sound.Play(SOUND::BGM2);
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

	Pause();
}

void Level1::UnLoad()
{
	next_level = {};
	is_next = false;
	delete referee;
	delete object_manager;
}

void Level1::Pause()
{
	if (input.Is_Key_Pressed(GLFW_KEY_P))
	{
		sound.Play(SOUND::Click);
		const float currentBGM_Volume = sound.GetSoundGroupVolume(true);
		sound.SetSoundGroupVolume(true, currentBGM_Volume / 3);
		is_pause = true;
	}
}

void Level1::Clear()
{
	Message_Manager::Get_Message_Manager()->Get_Messages().clear();
	//object_manager->Clear();
	ObjectManager::GetObjectManager()->Get_Objects().clear();
}
