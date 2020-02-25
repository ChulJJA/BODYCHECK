/*
 * Author		:Sangmin Kim
 * File			:Object_Component_info.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Object_Component_Info.cpp.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

class Object;

class Object_Component_Info
{
public:
    Object_Component_Info(Object* obj);
    Object* m_owner;
    bool component_info_player;
    bool component_info_enemy;
    bool component_info_physics;
    bool component_info_collision;
    bool component_info_sprite;
    bool component_info_top_down_movement;

private:
};