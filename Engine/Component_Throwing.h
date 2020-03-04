#pragma once
#include "Component.hpp"
#include "vector2.hpp"

class Throwing : public Component
{
public:
	void Init(Object* obj) override;
	void Update(float dt) override;

	void Set_Target_Dir(vector2 pos);
	void Set_Timer(float timer_);
	void Set_Target_Pos(vector2 pos);
	
private:
	vector2 target_dir;
	float timer;
	vector2 owner_pos;
	vector2 target_pos;
	float angle;
	float dir_vec_length;

	float dx;
	float dy;
};
