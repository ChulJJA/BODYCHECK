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

#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32 
#include <GLFW/glfw3native.h>
#include <mutex>
#include "Editor.h"
#include "Input.h"

using namespace std;

namespace
{
    Referee* referee = nullptr;

    ObjectManager* object_manager = nullptr;
	Editor* editor = nullptr;

}

void Level1::Load()
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
		current_state = GameState::Game;
		referee = Referee::Get_Referee();
		editor = Editor::Get_Editor();
		object_manager = ObjectManager::GetObjectManager();
		Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);

		sound.Stop(SOUND::BGM);
		sound.Play(SOUND::BGM2);

		arena = new Object();
		arena->Set_Name("arena");
		arena->Set_Tag("arena");
		arena->AddComponent(new Sprite(arena, "../Sprite/IceGround.png", { 0,0 }, false), "arena");
		arena->Set_Current_Sprite(arena->Find_Sprite_By_Name("arena"));
		arena->SetScale({ 20, 20 });
		ObjectManager::GetObjectManager()->AddObject(arena);

		player = Make_Player("first", "player", "pen_green", { 400.f, 400.f }, { 3.f, 3.f });
		player_sec = Make_Player("second", "player", "pen_red", { 400.f, -400.f }, { 3.f, 3.f });
		player_third = Make_Player("third", "player", "pen_purple", { -400.f, 400.f }, { 3.f, 3.f });
		player_forth = Make_Player("forth", "player", "pen_normal", { -400.f, -400.f }, { 3.f, 3.f });

		text = Make_Set_Text("red_text", "text", { 200,0 }, player, { 0,1,0,1 }, { 150,150 }, &font);
		text_2 = Make_Set_Text("green_text", "text", { 200,-200 }, player_sec, { 1,0,0,1 }, { 150,150 }, &font);
		text_3 = Make_Set_Text("blue_text", "text", { 200,-400 }, player_third, { 0.54,0,1,1 }, { 150,150 }, &font);
		text_4 = Make_Set_Text("yellow_text", "text", { 200,-400 }, player_forth, { 0.5,0.5,0.5,1 }, { 150,150 }, &font);

		player_first_ui = Make_Set_Ui("first_ui", "ui", "../sprite/pen_green.png", { -1000, -800 }, { 4.0f,4.0f }, player);
		player_second_ui = Make_Set_Ui("second_ui", "ui", "../sprite/pen_red.png", { -400, -800 }, { 4.0f,4.0f }, player_sec);
		player_third_ui = Make_Set_Ui("third_ui", "ui", "../sprite/pen_purple.png", { 200, -800 }, { 4.0f,4.0f }, player_third);
		player_fourth_ui = Make_Set_Ui("fourth_ui", "ui", "../sprite/pen_normal.png", { 800, -800 }, { 4.0f,4.0f }, player_forth);

		player->GetComponentByTemplate<Player>()->Set_This_UI_info(player_first_ui);
		player_sec->GetComponentByTemplate<Player>()->Set_This_UI_info(player_second_ui);
		player_third->GetComponentByTemplate<Player>()->Set_This_UI_info(player_third_ui);
		player_forth->GetComponentByTemplate<Player>()->Set_This_UI_info(player_fourth_ui);

		Referee::Get_Referee()->Set_First_Ui(player_first_ui);
		Referee::Get_Referee()->Set_Second_Ui(player_second_ui);
		Referee::Get_Referee()->Set_Third_Ui(player_third_ui);
		Referee::Get_Referee()->Set_Fourth_Ui(player_fourth_ui);

		Referee::Get_Referee()->Set_First_Text(text);
		Referee::Get_Referee()->Set_Second_Text(text_2);
		Referee::Get_Referee()->Set_Third_Text(text_3);
		Referee::Get_Referee()->Set_Fourth_Text(text_4);

		//referee->SetNeedCollision(true); //Collision Test
		referee->Init();
		
		Graphic::GetGraphic()->get_need_update_sprite() = true;
	}

	loading->Set_Done(false);
	if(loading_thread.joinable())
	{
		loading_thread.join();
	}
}

void Level1::Update(float dt)
{

	
	
	referee->Update(dt);

}