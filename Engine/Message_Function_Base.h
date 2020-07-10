/*
 * Author		:Sangmin Kim
 * File			:Message_Function_Base.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Message Function Base
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

class Object;
class Message;

class Msg_Func_Base
{
public:
	
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;

	Msg_Func_Base()
	{
		
	}
	virtual ~Msg_Func_Base()
	{
		
	}
	
private:
	
protected:
	Object* m_from;
	Object* m_target;
	Message* msg;
	
};