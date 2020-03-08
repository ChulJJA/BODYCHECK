#pragma once
#include "Component.hpp"

class Lock : public Component
{
public:
	enum class Status
	{
		None,
		Locking,
		Locked
	};

	void Init(Object* obj) override;
	void Update(float dt) override;
	
	void Set_State(Status status);
	Status Get_State();
	
	void Set_Timer(float timer_);
	void Set_Speed(float speed_);
	void Set_Throwing_Obj(Object* obj);
	Object* Get_Throwing_Obj();
	Object* Get_Locking_Target();
	void Set_Locking_Target(Object* obj);
	
private:
	Status state;
	vector2 pos;
	float timer;
	float speed;
	Object* throwing_obj;
	Object* locking_target;
};