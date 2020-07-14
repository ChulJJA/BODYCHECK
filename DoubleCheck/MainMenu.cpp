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
}

void MainMenu::Load()
{

	if (sound.isInitialized == false)
	{
		sound.Initialize();
	}
	FMOD_BOOL isPlaying;
	FMOD_BOOL isPlayingBGM2;
	FMOD_BOOL isMatchBGMPlaying;
	FMOD_BOOL isPauseBGMPlaying;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM)], &isPlaying);
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::BGM2)], &isPlayingBGM2);
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::MatchBGM)], &isMatchBGMPlaying);
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::PauseBGM)], &isPauseBGMPlaying);
	if (isPlaying == false)
	{
		sound.Play(SOUND::BGM);
	}
	if (isPlayingBGM2 == true)
	{
		sound.Stop(SOUND::BGM2);
	}
	if(isMatchBGMPlaying)
	{
		sound.Stop(SOUND::MatchBGM);
	}
	if(isPauseBGMPlaying)
	{
		sound.Stop(SOUND::PauseBGM);
	}
	p_1_selected = false;
	p_2_selected = false;
	r_u_sure = false;
	r_u_sure_come = false;

	state_manager = StateManager::GetStateManager();
	object_manager = ObjectManager::GetObjectManager();

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
	SetCreditButton();
	SetTestLevelButton();
	
	make_sure_dialogue = new Object();
	make_sure_dialogue->AddComponent(new Sprite(make_sure_dialogue, "../Sprite/rusure_yes.png", { 0.f, 0.f }, false, Sprite_Type::R_U_SURE_YES), "rusureyes", false);
	make_sure_dialogue->AddComponent(new Sprite(make_sure_dialogue, "../Sprite/rusure_no.png", { 0.f, 0.f }, false, Sprite_Type::R_U_SURE_NO), "rusureno", false);
	make_sure_dialogue->GetTransform().SetScale({ 10.f, 6.f });
	make_sure_dialogue->Set_Need_To_Update(false);
	object_manager->AddObject(make_sure_dialogue);
}

void MainMenu::Update(float dt)
{
	FMOD_BOOL isPauseBGMPlaying;
	FMOD_Channel_IsPlaying(sound.channel[static_cast<int>(SOUND::MatchBGM)], &isPauseBGMPlaying);
	if (isPauseBGMPlaying)
	{
		sound.Stop(SOUND::PauseBGM);
	}
	button_timer++;

	if (button_timer >= 10)
	{
		ButtonSelector();
	}
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
	play_button->AddComponent(new Sprite(play_button, "../Sprite/PlayButtonHover.png", { 50, 100 }, false, Sprite_Type::Button_Hover), "hover", false);
	play_button->GetTransform().SetScale({ 5, 5 });
	play_button->Set_Current_Sprite(play_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
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

}

void MainMenu::SetTestLevelButton()
{
	test_button = new Object();
	test_button->Set_Name("test_button");
	test_button->Set_Tag("button");
	test_button->AddComponent(new Component_Button());

	test_button->AddComponent(new Sprite(test_button, "../Sprite/TestButton.png", { 50, -900 }, false, Sprite_Type::Button), "button", true);
	test_button->AddComponent(new Sprite(test_button, "../Sprite/TestButtonHover.png", { 50, -900 }, false, Sprite_Type::Button_Hover), "button", false);
	test_button->GetTransform().SetScale({ 5, 5 });
	test_button->SetNeedCollision(true);
	test_button->AddComponent(new Physics());

	ObjectManager::GetObjectManager()->AddObject(test_button);

}

void MainMenu::SetCreditButton()
{
	creditButton = new Object();
	creditButton->Set_Name("creditButton");
	creditButton->Set_Tag("button");
	creditButton->AddComponent(new Component_Button());

	creditButton->AddComponent(new Sprite(creditButton, "../Sprite/CreditButton.png", { 50, -650 }, false, Sprite_Type::Button), "button", true);
	creditButton->AddComponent(new Sprite(creditButton, "../Sprite/CreditButtonHover.png", { 50, -650 }, false, Sprite_Type::Button_Hover), "button", false);
	creditButton->GetTransform().SetScale({ 5, 5 });
	creditButton->SetNeedCollision(true);
	creditButton->AddComponent(new Physics());

	ObjectManager::GetObjectManager()->AddObject(creditButton);
}

void MainMenu::ButtonSelector()
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
					sound.Play(SOUND::Click);
					make_sure_dialogue->Change_Sprite(r_u_sure_no_sprite);
				}
			}
			else if (input.Is_Key_Triggered(GLFW_KEY_LEFT))
			{
				if (r_u_sure_current_sprite == r_u_sure_no_sprite)
				{
					sound.Play(SOUND::Click);
					make_sure_dialogue->Change_Sprite(r_u_sure_yes_sprite);
				}
			}

			if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && r_u_sure_current_sprite == r_u_sure_yes_sprite)
			{
				sound.Play(SOUND::Selected);
				r_u_sure_come = false;
				r_u_sure = true;
			}
			else if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && r_u_sure_current_sprite == r_u_sure_no_sprite)
			{
				sound.Play(SOUND::Selected);
				r_u_sure_come = false;
				make_sure_dialogue->Set_Need_To_Update(false);
			}
		}
	}
	else
	{
		if (input.Is_Key_Pressed(GLFW_KEY_DOWN) && pointer <= static_cast<int>(BUTTON::TEST))
		{
			pointer++;

			if (pointer == static_cast<int>(BUTTON::START))
			{
				sound.Play(SOUND::Click);
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
			}
			else if (pointer == static_cast<int>(BUTTON::MUSIC))
			{
				sound.Play(SOUND::Click);
				tutorial_button->Change_Sprite(tutorial_button->Find_Sprite_By_Type(Sprite_Type::Button));
				music_button->Change_Sprite(music_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
				pointer1->SetTranslation({ -250,-400 });
				pointer2->SetTranslation({ 350,-400 });
			}
			else if (pointer == static_cast<int>(BUTTON::CREDIT))
			{
				sound.Play(SOUND::Click);

				music_button->Change_Sprite(music_button->Find_Sprite_By_Type(Sprite_Type::Button));
				creditButton->Change_Sprite(creditButton->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
				pointer1->SetTranslation({ -250,-650 });
				pointer2->SetTranslation({ 350,-650 });
			}
			else if (pointer == static_cast<int>(BUTTON::TEST))
			{
				sound.Play(SOUND::Click);

				creditButton->Change_Sprite(creditButton->Find_Sprite_By_Type(Sprite_Type::Button));
				test_button->Change_Sprite(test_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
				pointer1->SetTranslation({ -250,-900 });
				pointer2->SetTranslation({ 350,-900 });
			}
			else if (pointer > 4)
			{
				pointer = 4;
			}
			button_timer = 0;
		}
		else if (input.Is_Key_Pressed(GLFW_KEY_UP) && pointer >= static_cast<int>(BUTTON::START))
		{
			pointer--;

			if (pointer == static_cast<int>(BUTTON::START))
			{
				sound.Play(SOUND::Click);
				tutorial_button->Change_Sprite(tutorial_button->Find_Sprite_By_Type(Sprite_Type::Button));
				play_button->Change_Sprite(play_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
				pointer1->SetTranslation({ -250,100 });
				pointer2->SetTranslation({ 350,100 });
			}
			else if (pointer == static_cast<int>(BUTTON::TUTORIAL))
			{
				sound.Play(SOUND::Click);
				music_button->Change_Sprite(music_button->Find_Sprite_By_Type(Sprite_Type::Button));
				tutorial_button->Change_Sprite(tutorial_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
				pointer1->SetTranslation({ -250,-150 });
				pointer2->SetTranslation({ 350,-150 });
			}
			else if (pointer == static_cast<int>(BUTTON::MUSIC))
			{
				sound.Play(SOUND::Click);
				creditButton->Change_Sprite(creditButton->Find_Sprite_By_Type(Sprite_Type::Button));
				music_button->Change_Sprite(music_button->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
				pointer1->SetTranslation({ -250,-400 });
				pointer2->SetTranslation({ 350,-400 });
			}
			else if (pointer == static_cast<int>(BUTTON::CREDIT))
			{
				sound.Play(SOUND::Click);
				test_button->Change_Sprite(test_button->Find_Sprite_By_Type(Sprite_Type::Button));
				creditButton->Change_Sprite(creditButton->Find_Sprite_By_Type(Sprite_Type::Button_Hover));
				pointer1->SetTranslation({ -250,-650 });
				pointer2->SetTranslation({ 350,-650 });
			}
			else if (pointer == static_cast<int>(BUTTON::TEST))
			{
				sound.Play(SOUND::Click);
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


		if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && pointer == static_cast<int>(BUTTON::START))
		{
			pointer = static_cast<int>(BUTTON::START);
			sound.Play(SOUND::Selected);
			StateManager::GetStateManager()->level_state->is_pause = false;
			is_next = true;
			next_level = "Level1";
			Clear();
		}
		else if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && pointer == static_cast<int>(BUTTON::TUTORIAL))
		{
			sound.Play(SOUND::Selected);
			is_next = true;
			next_level = "Tutorial";
			Clear();
		}
		else if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && pointer == static_cast<int>(BUTTON::MUSIC))
		{
			pointer = static_cast<int>(BUTTON::START);
			sound.Play(SOUND::Selected);
			is_next = true;
			next_level = "Option";
			Clear();
		}
		else if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && pointer == static_cast<int>(BUTTON::CREDIT))
		{
			sound.StopAllSFX();
			pointer = static_cast<int>(BUTTON::START);
			sound.Play(SOUND::Selected);
			is_next = true;
			next_level = "Credit";
			Clear();
		}
		else if ((input.Is_Key_Triggered(GLFW_KEY_SPACE) || input.Is_Key_Triggered(GLFW_KEY_ENTER)) && pointer == static_cast<int>(BUTTON::TEST))
		{
			sound.Play(SOUND::Selected);
			if (r_u_sure == true)
			{
				pointer = static_cast<int>(BUTTON::START);
				Clear();
				Sleep(1000);
				exit(0);
			}
			else
			{
				r_u_sure_come = true;
			}
		}
		if (r_u_sure == true)
		{
			Clear();
			Sleep(1000);
			exit(0);
		}
	}
}

void MainMenu::Set_Player_Button()
{
	vector2 button1_pos{ -1500, 600 };
	vector2 button2_pos{ 1500, 600 };

	player_sec = Make_Player("second", "player", "pen_red2", { -800.f, 0.f }, { 4.f, 4.f }, true);
	player_third = Make_Player("third", "player", "pen_blue2", { 800.f, 0.f }, { 4.f, 4.f }, true);

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
}

void MainMenu::SetControllerImage()
{
	firstPlayerKeyboard = new Object();
	firstPlayerKeyboard->Set_Name("firstPlayerKeyboardImage");
	firstPlayerKeyboard->AddComponent(new Sprite(firstPlayerKeyboard, "../Sprite/UI/firstPlayerKeyboard.png", { -400.f ,-900.f }, false, Sprite_Type::None), "firstPlayerKeyboardImage", true);
	firstPlayerKeyboard->GetTransform().SetScale({ 4, 4 });

	secPlayerKeyboard = new Object();
	secPlayerKeyboard->Set_Name("secPlayerKeyboardImage");
	secPlayerKeyboard->AddComponent(new Sprite(secPlayerKeyboard, "../Sprite/UI/secPlayerKeyboard.png", { 800.f ,-900.f }, false, Sprite_Type::None), "secPlayerKeyboardImage", true);
	secPlayerKeyboard->GetTransform().SetScale({ 4, 4 });

	firstPlayerGamepad = new Object();
	firstPlayerGamepad->Set_Name("firstPlayerGamepadImage");
	firstPlayerGamepad->AddComponent(new Sprite(firstPlayerGamepad, "../Sprite/UI/Player1.png", { -400.f ,-900.f }, false, Sprite_Type::None), "firstPlayerGamepadImage", true);
	firstPlayerGamepad->GetTransform().SetScale({ 4, 4 });

	
	secPlayerGamepad = new Object();
	secPlayerGamepad->Set_Name("secPlayerGamepadImage");
	secPlayerGamepad->AddComponent(new Sprite(secPlayerGamepad, "../Sprite/UI/Player2.png", { 800.f ,-900.f }, false, Sprite_Type::None), "secPlayerGamepadImage", true);
	secPlayerGamepad->GetTransform().SetScale({ 4, 4 });
}
