/*
 * Author		:Chulseung Lee Kim
 * File			:MainMenu.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Main Menu
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include <GLFW/glfw3.h>
#include "MainMenu.h"
#include "Input.h"
#include "ObjectManager.h"
#include "Component_Text.h"
#include "StateManager.h"
#include "Object.h"
#include "Transform.hpp"
#include "Engine.hpp"
#include "Sound_Manager.h"
#include "Windows.h"
#include <GLFW/glfw3.h>
#include "UsefulTools.hpp"
#include "Gamepad.hpp"
#include "Level1.h"
#include "Physics.h"
#include "Component_Button.h"
#include "Message_Manager.h"


namespace
{
	ObjectManager* object_manager = nullptr;
	StateManager* state_manager = nullptr;
	Gamepad* gamepadManager = nullptr;
}

void MainMenu::Load()
{

	if (sound.isInitialized == false)
	{
		sound.Initialize();
	}
	FMOD_BOOL isPlaying;
	FMOD_Channel_IsPlaying(sound.channel[0], &isPlaying);
	if (isPlaying == false)
	{
		sound.Play(SOUND::BGM);
	}
	p_1_selected = false;
	p_2_selected = false;

	state_manager = StateManager::GetStateManager();
	object_manager = ObjectManager::GetObjectManager();
	gamepadManager = Gamepad::getGamepad();

	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
	Graphic::GetGraphic()->get_need_update_sprite() = true;

	pointer = 0;
	button_timer = 0;

	Object* back = new Object();

	back->AddComponent(new Sprite(back, "../Sprite/menu_background.png", { 50.f,20.f }, false));
	back->GetTransform().SetScale({ 38.f, 21.f });
	object_manager->AddObject(back);
	SetPlayButton();
	SetTutorialButton();
	SetMusicButton();
	SetTestLevelButton();
	Set_Player_Button();
}

void MainMenu::Update(float dt)
{

	button_timer++;

	if (button_timer >= 10)
	{
		ButtonSelector();
	}

	if (input.Is_Key_Triggered(GLFW_KEY_1))
	{
		if (p_1_selected)
		{
			player_sec->SetNeedCollision(false);
			player_sec->Set_Need_To_Update(false);
			p_1_selected = false;
			player_1_button->Change_Sprite(player_1_button->Find_Sprite_By_Type(Sprite_Type::None));

			/*play_button->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			play_button_hover->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			tutorial_button->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			tutorial_button_hover->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			music_button->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			music_button_hover->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			test_button->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			test_button_hover->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();*/
		}
		else
		{
			player_sec->SetTranslation(player_sec_pos);
			player_sec->SetNeedCollision(true);
			player_sec->Set_Need_To_Update(true);
			p_1_selected = true;
			player_1_button->Change_Sprite(player_1_button->Find_Sprite_By_Type(Sprite_Type::Player_Selected));
			Graphic::GetGraphic()->Get_View().Active_Screen_Shake(10.f, 3);


			/*play_button->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			play_button_hover->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			tutorial_button->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			tutorial_button_hover->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			music_button->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			music_button_hover->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			test_button->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			test_button_hover->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();*/
		}
	}
	if (input.Is_Key_Triggered(GLFW_KEY_2))
	{
		if (p_2_selected)
		{
			player_third->Set_Need_To_Update(false);
			p_2_selected = false;
			player_third->SetNeedCollision(false);
			player_2_button->Change_Sprite(player_2_button->Find_Sprite_By_Type(Sprite_Type::None));

			/* play_button->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			 play_button_hover->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			 tutorial_button->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			 tutorial_button_hover->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			 music_button->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			 music_button_hover->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			 test_button->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();
			 test_button_hover->GetComponentByTemplate<Component_Button>()->Decrement_Max_Player_Num();*/
		}
		else
		{
			player_third->SetNeedCollision(true);
			player_third->SetTranslation(player_third_pos);
			player_third->Set_Need_To_Update(true);
			p_2_selected = true;
			player_2_button->Change_Sprite(player_2_button->Find_Sprite_By_Type(Sprite_Type::Player_Selected));
			Graphic::GetGraphic()->Get_View().Active_Screen_Shake(10.f, 3);

			/*play_button->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			play_button_hover->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			tutorial_button->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			tutorial_button_hover->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			music_button->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			music_button_hover->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			test_button->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();
			test_button_hover->GetComponentByTemplate<Component_Button>()->Increment_Max_Player_Num();*/
		}
	}

	//std::cout << "max : " << play_button->GetComponentByTemplate<Component_Button>()->Get_Max_Player_Num() << std::endl;
	//std::cout << "curr : " << play_button->GetComponentByTemplate<Component_Button>()->Get_Curr_Player_Num() << std::endl;

	/*if (play_button->GetComponentByTemplate<Component_Button>()->Selected())
	{
		pointer = static_cast<int>(BUTTON::START);
		sound.Play(SOUND::Selected);
		StateManager::GetStateManager()->level_state->is_pause = false;
		is_next = true;
		next_level = "Level1";
		Sleep(800);
		sound.UnLoad();
		Clear();
	}*/
}

void MainMenu::Clear()
{
	Message_Manager::Get_Message_Manager()->Get_Messages().clear();
	object_manager->Clear();

}

void MainMenu::SetPlayButton()
{
	play_button = new Object();
	play_button->Set_Name("play_button");
	play_button->Set_Tag("button");
	play_button->AddComponent(new Component_Button());
	play_button->AddComponent(new Sprite(play_button, "../Sprite/PlayButton.png", { 50, 100 }, false, Sprite_Type::Button), "button", true);
	play_button->AddComponent(new Sprite(play_button, "../Sprite/PlayButtonHover.png", { 50, 100 }, false, Sprite_Type::Button_Hover),"hover", false);
	//play_button->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	play_button->GetTransform().SetScale({ 5, 5 });
	play_button->AddComponent(new Physics());
	play_button->SetNeedCollision(true);
	ObjectManager::GetObjectManager()->AddObject(play_button);
	
	pointer1 = new Object();
	pointer1->Set_Name("pointer1");
	pointer1->Set_Tag("pointer");
	pointer1->AddComponent(new Sprite(pointer1, "../Sprite/Player/State/pen_purple_dance.png", true, 15, 7, { -250,100 }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Dance), "dance", true);
	pointer1->GetTransform().SetScale({ 2, 2 });
	ObjectManager::GetObjectManager()->AddObject(pointer1);

	pointer2 = new Object();
	pointer2->Set_Name("pointer2");
	pointer2->Set_Tag("pointer");
	pointer2->AddComponent(new Sprite(pointer2, "../Sprite/Player/State/pen_purple_dance.png", true, 15, 7, { 350,100 }, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::Player_Dance), "dance", true);
	pointer2->GetTransform().SetScale({ 2, 2 });
	ObjectManager::GetObjectManager()->AddObject(pointer2);
	
	//play_button_hover = new Object();
	//play_button_hover->Set_Name("play_button_hover");
	//play_button_hover->Set_Tag("button");
	//play_button_hover->AddComponent(new Component_Button());
	//play_button_hover->AddComponent(new Sprite(play_button_hover, "../Sprite/PlayButtonHover.png", { 0, 100 }, false));
	//play_button_hover->GetTransform().SetScale({ 5, 5 });
	//play_button_hover->SetNeedCollision(true);
	//play_button_hover->AddComponent(new Physics());
	//ObjectManager::GetObjectManager()->AddObject(play_button_hover);
}

void MainMenu::SetTutorialButton()
{
	tutorial_button = new Object();
	tutorial_button->Set_Name("tutorial_button");
	tutorial_button->Set_Tag("button");
	tutorial_button->AddComponent(new Component_Button());
	tutorial_button->AddComponent(new Sprite(tutorial_button, "../Sprite/TutorialButton.png", { 50, -150 }, false, Sprite_Type::Button), "button", true);
	tutorial_button->AddComponent(new Sprite(tutorial_button, "../Sprite/TutorialButtonHover.png", { 50, -150 }, false, Sprite_Type::Button_Hover), "hover", false);
	tutorial_button->GetTransform().SetScale({ 5, 5 });
	tutorial_button->SetNeedCollision(true);
	tutorial_button->AddComponent(new Physics());

	ObjectManager::GetObjectManager()->AddObject(tutorial_button);

	/*tutorial_button_hover = new Object();
	tutorial_button_hover->Set_Name("tutorial_button_hover");
	tutorial_button_hover->Set_Tag("button");
	tutorial_button_hover->AddComponent(new Component_Button());
	tutorial_button_hover->AddComponent(new Sprite(tutorial_button_hover, "../Sprite/TutorialButtonHover.png", { 0, -150 }, false));
	tutorial_button_hover->GetTransform().SetScale({ 5, 5 });
	tutorial_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	tutorial_button_hover->SetNeedCollision(true);
	tutorial_button_hover->AddComponent(new Physics());

	ObjectManager::GetObjectManager()->AddObject(tutorial_button_hover);*/
}

void MainMenu::SetMusicButton()
{
	music_button = new Object();
	music_button->Set_Name("music_button");
	music_button->Set_Tag("button");
	music_button->AddComponent(new Component_Button());
	music_button->AddComponent(new Sprite(music_button, "../Sprite/MusicButton_.png", { 50, -400 }, false, Sprite_Type::Button), "button", true);
	music_button->AddComponent(new Sprite(music_button, "../Sprite/MusicButtonHover_.png", { 50, -400 }, false, Sprite_Type::Button_Hover), "hover", false);
	music_button->GetTransform().SetScale({ 5, 5 });
	music_button->SetNeedCollision(true);
	music_button->AddComponent(new Physics());

	ObjectManager::GetObjectManager()->AddObject(music_button);

	/*music_button_hover = new Object();
	music_button_hover->Set_Name("music_button_hover");
	music_button_hover->Set_Tag("button");
	music_button_hover->AddComponent(new Component_Button());
	music_button_hover->AddComponent(new Sprite(music_button_hover, "../Sprite/MusicButtonHover_.png", { 0, -400 }, false));
	music_button_hover->GetTransform().SetScale({ 5, 5 });
	music_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	music_button_hover->SetNeedCollision(true);
	music_button_hover->AddComponent(new Physics());

	ObjectManager::GetObjectManager()->AddObject(music_button_hover);*/
}

void MainMenu::SetTestLevelButton()
{
	test_button = new Object();
	test_button->Set_Name("test_button");
	test_button->Set_Tag("button");
	test_button->AddComponent(new Component_Button());

	test_button->AddComponent(new Sprite(test_button, "../Sprite/TestButton.png", { 50, -650 }, false, Sprite_Type::Button), "button", true);
	test_button->AddComponent(new Sprite(test_button, "../Sprite/TestButtonHover.png", { 50, -650 }, false, Sprite_Type::Button_Hover), "button", false);
	test_button->GetTransform().SetScale({ 5, 5 });
	test_button->SetNeedCollision(true);
	test_button->AddComponent(new Physics());

	ObjectManager::GetObjectManager()->AddObject(test_button);

	/*test_button_hover = new Object();
	test_button_hover->Set_Name("test_button_hover");
	test_button_hover->Set_Tag("button");
	test_button_hover->AddComponent(new Component_Button());
	test_button_hover->AddComponent(new Sprite(test_button_hover, "../Sprite/TestButtonHover.png", { 0, -650 }, false));
	test_button_hover->GetTransform().SetScale({ 5, 5 });
	test_button_hover->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1,1,1,0 };
	test_button_hover->SetNeedCollision(true);
	test_button_hover->AddComponent(new Physics());

	ObjectManager::GetObjectManager()->AddObject(test_button_hover);*/
}

void MainMenu::ButtonSelector()
{
	float LeftThumbStateY = gamepadManager->LeftStick_Y();

	if ((input.Is_Key_Pressed(GLFW_KEY_DOWN) || (LeftThumbStateY < 0)) && pointer <= static_cast<int>(BUTTON::TEST))
	{
		pointer++;

		if (pointer == static_cast<int>(BUTTON::START))
		{
			sound.Play(SOUND::Click);
			//ObjectHover(play_button, play_button_hover);
			play_button->Change_Sprite(play_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
			pointer1->SetTranslation({ -250,100 });
			pointer2->SetTranslation({ 350,100 });
		}
		else if (pointer == static_cast<int>(BUTTON::TUTORIAL))
		{
			sound.Play(SOUND::Click);
			play_button->Change_Sprite(play_button->Find_Sprite_By_Type(Sprite_Type::Button));
			tutorial_button->Change_Sprite(tutorial_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
			pointer1->SetTranslation({ -250,-150 });
			pointer2->SetTranslation({ 350,-150 });
			//ObjectHover(tutorial_button, tutorial_button_hover);
			//ObjectHover(play_button_hover, play_button);
		}
		else if (pointer == static_cast<int>(BUTTON::MUSIC))
		{
			sound.Play(SOUND::Click);
			//ObjectHover(music_button, music_button_hover);
			//ObjectHover(tutorial_button_hover, tutorial_button);
			tutorial_button->Change_Sprite(tutorial_button->Find_Sprite_By_Type(Sprite_Type::Button));
			music_button->Change_Sprite(music_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
			pointer1->SetTranslation({ -250,-400 });
			pointer2->SetTranslation({ 350,-400 });
		}
		else if (pointer == static_cast<int>(BUTTON::TEST))
		{
			sound.Play(SOUND::Click);
			//ObjectHover(test_button, test_button_hover);
			//ObjectHover(music_button_hover, music_button);

			music_button->Change_Sprite(music_button->Find_Sprite_By_Type(Sprite_Type::Button));
			test_button->Change_Sprite(test_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
			pointer1->SetTranslation({ -250,-650 });
			pointer2->SetTranslation({ 350,-650 });
		}
		else if (pointer > 3)
		{
			pointer = 3;
		}
		button_timer = 0;
	}
	else if ((input.Is_Key_Pressed(GLFW_KEY_UP) || LeftThumbStateY > 0) && pointer >= static_cast<int>(BUTTON::START))
	{
		pointer--;

		if (pointer == static_cast<int>(BUTTON::START))
		{
			sound.Play(SOUND::Click);
			tutorial_button->Change_Sprite(tutorial_button->Find_Sprite_By_Type(Sprite_Type::Button));
			play_button->Change_Sprite(play_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
			pointer1->SetTranslation({ -250,100 });
			pointer2->SetTranslation({ 350,100 });
			//ObjectHover(play_button, play_button_hover);
			//ObjectHover(tutorial_button_hover, tutorial_button);
		}
		else if (pointer == static_cast<int>(BUTTON::TUTORIAL))
		{
			sound.Play(SOUND::Click);
			//ObjectHover(tutorial_button, tutorial_button_hover);
			//ObjectHover(music_button_hover, music_button);

			music_button->Change_Sprite(music_button->Find_Sprite_By_Type(Sprite_Type::Button));
			tutorial_button->Change_Sprite(tutorial_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
			pointer1->SetTranslation({ -250,-150 });
			pointer2->SetTranslation({ 350,-150 });
		}
		else if (pointer == static_cast<int>(BUTTON::MUSIC))
		{
			sound.Play(SOUND::Click);
			//ObjectHover(music_button, music_button_hover);
			//ObjectHover(test_button_hover, test_button);

			test_button->Change_Sprite(test_button->Find_Sprite_By_Type(Sprite_Type::Button));
			music_button->Change_Sprite(music_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
			pointer1->SetTranslation({ -250,-400 });
			pointer2->SetTranslation({ 350,-400 });
		}
		else if (pointer == static_cast<int>(BUTTON::TEST))
		{
			sound.Play(SOUND::Click);
			/*ObjectHover(test_button, test_button_hover);*/
			test_button->Change_Sprite(test_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
			pointer1->SetTranslation({ -250,-650 });
			pointer2->SetTranslation({ 350,-650 });
		}
		else if (pointer < 0)
		{
			pointer = 0;
		}
		button_timer = 0;
	}

	if ((input.Is_Key_Pressed(GLFW_KEY_SPACE) || gamepadManager->GetButtonDown(xButtons.A)) && pointer == static_cast<int>(BUTTON::START))
	{
		pointer = static_cast<int>(BUTTON::START);
		sound.Play(SOUND::Selected);
		StateManager::GetStateManager()->level_state->is_pause = false;
		is_next = true;
		next_level = "Level1";
		Sleep(800);
		sound.UnLoad();
		Clear();
	}
	else if ((input.Is_Key_Pressed(GLFW_KEY_SPACE) || gamepadManager->GetButtonDown(xButtons.A)) && pointer == static_cast<int>(BUTTON::TUTORIAL))
	{
		sound.Play(SOUND::Selected);
		is_next = true;
		next_level = "Tutorial";
		Clear();
	}
	else if ((input.Is_Key_Pressed(GLFW_KEY_SPACE) || gamepadManager->GetButtonDown(xButtons.A)) && pointer == static_cast<int>(BUTTON::MUSIC))
	{
		pointer = static_cast<int>(BUTTON::START);
		sound.Play(SOUND::Selected);
		is_next = true;
		next_level = "Option";
		Clear();
	}
	else if ((input.Is_Key_Pressed(GLFW_KEY_SPACE) || gamepadManager->GetButtonDown(xButtons.A)) && pointer == static_cast<int>(BUTTON::TEST))
	{
		pointer = static_cast<int>(BUTTON::START);
		sound.Play(SOUND::Selected);
		//is_next = true;
		//next_level = "TestLevel";
		Clear();
		exit(0);

	}
}

void MainMenu::Set_Player_Button()
{
	vector2 button1_pos{ -1500, 600 };
	vector2 button2_pos{ 1500, 600 };

	player_sec = Make_Player("second", "player", "pen_red2", { -800.f, 0.f }/*{ 400.f, -400.f }*/, { 4.f, 4.f }, true);
	player_third = Make_Player("third", "player", "pen_blue2", { 800.f, 0.f }/*{ -400.f, 400.f }*/, { 4.f, 4.f }, true);

	player_sec->Get_Belongs_Objects().clear();
	player_third->Get_Belongs_Objects().clear();

	player_sec->Set_Need_To_Update(false);
	player_sec->SetNeedCollision(false);
	player_third->Set_Need_To_Update(false);
	player_third->SetNeedCollision(false);

	player_1_button = new Object();

	player_1_button->AddComponent(new Sprite(player_1_button, "../Sprite/UI/p1_select.png", true, 2, 4, button1_pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "p1_button", true);

	player_1_button->AddComponent(new Sprite(player_1_button, "../Sprite/UI/p1_selected.png", button1_pos, false, Sprite_Type::Player_Selected), "selected", false);


	object_manager->AddObject(player_1_button);

	player_1_button->SetScale(5.f);

	player_2_button = new Object();
	player_2_button->AddComponent(new Sprite(player_2_button, "../Sprite/UI/p2_select.png", true, 2, 4, button2_pos, { 100.f,100.f },
		{ 255,255,255,255 }, Sprite_Type::None), "p2_button", true);

	player_2_button->AddComponent(new Sprite(player_2_button, "../Sprite/UI/p2_selected.png", button2_pos, false, Sprite_Type::Player_Selected), "selected", false);

	object_manager->AddObject(player_2_button);

	player_2_button->SetScale(5.f);

	//object_manager->AddObject(player_sec);
	//object_manager->AddObject(player_third);
}
