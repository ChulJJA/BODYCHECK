#pragma once
#include "Component.hpp"

class Lock : public Component
{
public:
	void Init(Object* obj) override;
	void Update(float dt) override;
	
	void Set_Timer(float timer_);
	void Set_Speed(float speed_);
	
	void Set_Locking_Obj(Object* obj);
	Object* Get_Locking_Obj();
	Object* Get_Locking_Target();
	void Set_Locking_Target(Object* obj);
	void Control_Input(float dt);
	void Func_Set_Magnatic();
	
private:
	vector2 pos;
	float timer;
	float speed;
	Object* locking_obj;
	Object* locking_target;
};