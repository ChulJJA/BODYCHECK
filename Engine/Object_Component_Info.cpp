/*
 * Author		:Sangmin Kim
 * File			:Object_Component_Info.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Object Component Info
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Object_Component_Info.h"

Object_Component_Info::Object_Component_Info(Object* obj)
{
    m_owner = obj;

    component_info_player = false;
    component_info_enemy = false;
    component_info_physics = false;
    component_info_collision = false;
    component_info_sprite = false;
    component_info_top_down_movement = false;
}