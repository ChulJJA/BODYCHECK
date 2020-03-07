#pragma once
#include "Component.hpp"
#include "vector2.hpp"

class Throwing : public Component
{
public:
	Throwing() : timer(0.f) , angle(0.f), angle_in_radian(90.f), pos(0.f)
	{
		
	}
	
	void Init(Object* obj) override;
	void Update(float dt) override;

	void Set_Timer(float timer_);
	void Set_Angle(float angle);
	void Set_Throwing_Obj(Object* obj);
	Object* Get_Throwing_Obj();
private:
	float timer;
	float angle;
	float angle_in_radian;
	vector2 pos;
	Object* throwing_obj;
};
