/*
 * Author		:Suhwan Kim
 * File			:GamePad.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for GamePad
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <Windows.h>

#include <Xinput.h>


static const WORD XINPUT_Buttons[] = {
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK
};

struct XInput_ButtonIDs
{
	XInput_ButtonIDs();

	int A, B, X, Y;
	int DPad_Up, DPad_Down, DPad_Left, DPad_Right;
	int L_Shoulder, R_Shoulder;
	int L_Thumbstick, R_Thumbstick;

	int Start;
	int Back;
};

class Gamepad
{
public:
	static Gamepad* getGamepad();
	static Gamepad* getGamepadSecond();

	Gamepad();
	Gamepad(int controllerNumber);

    void Update();
	void Refresh();

	void Delete();

	bool LStick_InDeadzone();
	bool RStick_InDeadzone();

	float LeftStick_X();
	float LeftStick_Y();
	float RightStick_X();
	float RightStick_Y();

	float LeftTrigger();
	float RightTrigger();

	bool GetButtonPressed(int get_Button);

	bool GetButtonDown(int get_button);

	XINPUT_STATE GetState();
	int Get_GamepadID();
	bool Connected();

	void Rumble(float Get_LeftMoter = 0.0f, float Get_RightMotor = 0.0f);
	

private:
	static Gamepad* gamepadManager;
	static Gamepad* gamepadManagerSec;
	XINPUT_STATE m_State;
	int m_GamepadID;

	static const int ButtonCount = 14;
	bool Prev_ButtonStates[ButtonCount];
	bool ButtonStates[ButtonCount];

	bool Gamepad_ButtonsDown[ButtonCount];
};

extern XInput_ButtonIDs xButtons;