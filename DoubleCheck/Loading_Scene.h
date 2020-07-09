/*
 * Author		:Sangmin Kim
 * File			:Loading_Scene.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Loading Scene
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "State.h"
#include <atomic>
#include "Level1.h"


class Loading_Scene : public State
{
public:
	Loading_Scene();
	virtual void Load() override;
	virtual void Update(float dt) override;

	virtual void UnLoad() override;

	void Set_Done(bool toggle)
	{
		done = toggle;
	}

private:
	Object* volatile image;
	Object* volatile image2;
	std::atomic<bool> done;
	Level1* level1;
	std::vector<std::thread> thread_vec;
};
