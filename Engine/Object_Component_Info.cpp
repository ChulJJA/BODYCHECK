/*
 * Author		:Sangmin Kim
 * File			:Object_Component_Info.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for represent object's component information.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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