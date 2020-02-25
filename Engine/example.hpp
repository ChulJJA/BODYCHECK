#pragma once
#include <iostream>
#include "Engine.hpp"
#include "Component_Sprite.h"
#include "Component_Transform.h"
#include "Component_TopDownMovement.h"
#include "Application.hpp"
#include "ObjectManager.h"
#include "Timer.hpp"
#include "StateManager.h"


class Example
{
public:
	static Example* GetExample();

	void Init();
	void Update();
	void Reset();
	bool IsDone() { return is_done; }
	void Delete();
private:
	static Example* example;
	bool is_done = false;
	float m_dt;
	Timer game_timer;
};