/*
 * Author		:Sangmin Kim
 * File			:Audience.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Audience
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once


#include "Object.h"

enum PEN
{
	Normal,
	Red,
	Blue,
	Green
};


Object* Get_Audience();
//
//class Audience : public Object
//{
//public:
//	enum class PEN
//	{
//		Normal,
//		Red,
//		Blue,
//		Green
//	};
//	Object* Get_Audience(PEN aud_type);
//
//private:
//	
//};