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

	Delete_Object,
	
};