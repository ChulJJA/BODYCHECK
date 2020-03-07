#pragma once
#include "State.h"
#include "Object.h"
#include "BitmapFont.hpp"

class PLAYER_UI;

class Testing_Level : public State
{
public:
	Testing_Level()
	{
		
	}

	virtual void Load() override;
	virtual void Update(float dt);

	virtual void UnLoad()
	{
		next_level = {};
		is_next = false;
	}

private:

	Object* player;
	Object* item;
	PLAYER_UI* player_first_ui;
	Object* text;
};
