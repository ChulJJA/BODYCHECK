/*
 * Author		:Sangmin Kim
 * File			:Object_Component_Info.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Object Component Info
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
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