/*
 * Author		:Sangmin Kim
 * File			:Message_Kind.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message Kind
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

enum class Message_Kind
{
	None,
	Collision_Wall,
	Collision,
	Respawn,
	Die,

	Item_Bulkup,
	Item_Recover,
	Item_Dash,
	Item_Throwing,
	Item_Magnetic,
	Item_Timepause,
	Item_Reverse,
	Item_Missile,

	Audience_Red_Joy,
	Audience_Blue_Joy,
	Audience_Green_Joy,
	Audience_Normal_Joy,
	Item_Mine,
	Item_Eat,
	Spawn_Object,
	Delete_Object,

	Particle_Collision,
	
};