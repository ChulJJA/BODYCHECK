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