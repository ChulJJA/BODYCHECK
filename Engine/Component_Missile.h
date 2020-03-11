#pragma once
#include "Component.hpp"
#include "vector2.hpp"

class Missile : public Component
{
public:
	Missile() : timer(0.f), angle(0.f), angle_in_radian(90.f), pos(0.f)
	{

	}

	void Init(Object* obj) override;
	void Update(float dt) override;
	void Set_Target(Object* obj);
	void Set_From_Obj(Object* obj);
	Object* Get_Target();
	Object* Get_From_Obj();
private:
	float timer;
	float angle;
	float angle_in_radian;
	vector2 pos;
	Object* target;
	Object* from;
};
