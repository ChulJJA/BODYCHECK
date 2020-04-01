#pragma once
#include "Component.hpp"

class Player;

class Lock : public Component
{
public:
	void Init(Object* obj) override;
	void Update(float dt) override;
	
	void Set_Timer(float timer_);
	void Set_Speed(float speed_);
	
	void Set_Locking_Obj(Object* obj);
	Object* Get_Locking_Obj() const;
	Object* Get_Locking_Target();
	void Set_Locking_Target(Object* obj);
	void Control_Input(float dt);
	void Func_Set_Magnatic() const;
	
private:
	vector2 pos;
	float timer = 0;
	float speed = 0;

	/*
	 * locking_obj				= player who use magnetic item.
	 * info_player_locking_obj	= player pointer of locking_obj.
	 *
	 * locking_target			= current locked player.
	 */
	
	Object* locking_obj = nullptr;
	Player* info_player_locking_obj = nullptr;
	
	Object* locking_target = nullptr;
};