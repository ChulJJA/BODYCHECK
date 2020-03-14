/*
 * Author		:Sangmin Kim
 * File			:Component.hpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Component.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <string>
#include "Object.h"

class Component
{
public:
	virtual ~Component() = default;
	virtual  void Init(Object* obj) = 0;
    virtual  void Update(float dt) = 0;

    void SetComponentName(std::string component)
    {
        component_name = component;
    }
    std::string GetComponentName() const
    {
        return component_name;
    }
	void Set_Need_Update(bool toggle)
    {
		need_update = toggle;
    }
	bool Get_Need_Update()
    {
		return need_update;
    }

    Object* m_owner = nullptr;

private:
    std::string component_name;
	bool need_update = true;
};