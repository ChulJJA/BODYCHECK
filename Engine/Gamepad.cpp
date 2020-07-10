/*
 * Author		:Suhwan Kim
 * File			:GamePad.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Gamepad
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Gamepad.hpp"

#pragma comment(lib, "XInput9_1_0.lib")

XInput_ButtonIDs xButtons;

XInput_ButtonIDs::XInput_ButtonIDs()
{
	A = 0;
	B = 1;
	X = 2;
	Y = 3;

	DPad_Up = 4;
	DPad_Down = 5;
	DPad_Left = 6;
	DPad_Right = 7;

	L_Shoulder = 8;
	R_Shoulder = 9;

	L_Thumbstick = 10;
	R_Thumbstick = 11;

	Start = 12;
	Back = 13;

}

Gamepad* Gamepad::gamepadManager = nullptr;
Gamepad* Gamepad::gamepadManagerSec = nullptr;

Gamepad* Gamepad::getGamepad()
{
	if (gamepadManager == nullptr)
		gamepadManager = new Gamepad(1);

	return gamepadManager;
}

Gamepad* Gamepad::getGamepadSecond()
{
	if (gamepadManagerSec == nullptr)
		gamepadManagerSec = new Gamepad(2);

	return gamepadManagerSec;
}

Gamepad::Gamepad(){}

Gamepad::Gamepad(int controllerNumber)
{
	m_GamepadID = controllerNumber - 1;

	for (int i = 0; i < ButtonCount; i++)
	{
		Prev_ButtonStates[i]   = false;
		ButtonStates[i]        = false;
		Gamepad_ButtonsDown[i] = false;
	}
}

void Gamepad::Update()
{
	m_State = GetState(); // Obtain current gamepad state

	for (int i = 0; i < ButtonCount; i++)
	{
		ButtonStates[i] = (m_State.Gamepad.wButtons & XINPUT_Buttons[i]) == XINPUT_Buttons[i];
	}
}

void Gamepad::Refresh()
{
	memcpy(Prev_ButtonStates, ButtonStates, sizeof(Prev_ButtonStates));
}

void Gamepad::Delete()
{
	delete gamepadManager;
	gamepadManager = nullptr;
}

bool Gamepad::LStick_InDeadzone()
{
	short X = m_State.Gamepad.sThumbLX;
	short Y = m_State.Gamepad.sThumbLY;

	if(X > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		X < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;
	
	if(Y > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		Y < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	return true;
}

bool Gamepad::RStick_InDeadzone()
{
	short X = m_State.Gamepad.sThumbRX;
	short Y = m_State.Gamepad.sThumbRY;

	if (X > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		X < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	if (Y > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		Y < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	return true;
}

float Gamepad::LeftStick_X()
{
	short sX = m_State.Gamepad.sThumbLX;

	return (static_cast<float>(sX) / 32768.0f);
}

float Gamepad::LeftStick_Y()
{
	short sY = m_State.Gamepad.sThumbLY;

	return (static_cast<float>(sY) / 32768.0f);
}

float Gamepad::RightStick_X()
{
	short sX = m_State.Gamepad.sThumbRX;

	return (static_cast<float>(sX) / 32768.0f);
}

float Gamepad::RightStick_Y()
{
	short sY = m_State.Gamepad.sThumbRY;

	return (static_cast<float>(sY) / 32768.0f);
}

float Gamepad::LeftTrigger()
{
	BYTE Trigger = m_State.Gamepad.bLeftTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return (Trigger / 255.0f);
	else
		return 0.0f;
}

float Gamepad::RightTrigger()
{
	BYTE Trigger = m_State.Gamepad.bRightTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return (Trigger / 255.0f);
	else
		return 0.0f;
}

bool Gamepad::GetButtonPressed(int get_Button)
{
	if (m_State.Gamepad.wButtons & XINPUT_Buttons[get_Button])
		return true;
	else
		return false;
}

bool Gamepad::GetButtonDown(int get_button)
{
	return !Prev_ButtonStates[get_button] && ButtonStates[get_button];
}

XINPUT_STATE Gamepad::GetState()
{
	XINPUT_STATE GamepadState;

	ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));

	XInputGetState(m_GamepadID, &GamepadState);

	return GamepadState;
}

int Gamepad::Get_GamepadID()
{
	return m_GamepadID;
}

bool Gamepad::Connected()
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));

	DWORD Result = XInputGetState(m_GamepadID, &m_State);

	if (Result == ERROR_SUCCESS)
		return true; // The Gamepad is connected
	else
		return false; // The gamepad is disconnected
}

void Gamepad::Rumble(float Get_LeftMoter, float Get_RightMotor)
{
	XINPUT_VIBRATION VibrationState;

	ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

	int Set_LeftMotor = int(Get_LeftMoter * 65535.0f);
	int Set_RightMotor = int(Get_RightMotor * 65535.0f);

	VibrationState.wLeftMotorSpeed = Set_LeftMotor;
	VibrationState.wRightMotorSpeed = Set_RightMotor;

	XInputSetState(m_GamepadID, &VibrationState);
}


