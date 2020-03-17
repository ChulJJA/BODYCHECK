/*
 * Author		:Chulseung Lee
 * File			:Component_Collision.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Collision check of objects in engine.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Collision.h"
#include "Physics.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Engine.hpp"
#include "Message_Manager.h"
#include "Component_Sprite.h"
#include "Message.h"
#include "Component_Throwing.h"
#include "Component_Lock.h"
#include "Component_Player.h"
#include "UsefulTools.hpp"
#include "Component_Missile.h"

void Collision::Init(Object* obj)
{
	m_owner = obj;
}

void Collision::Update(float dt)
{
	sound_timer += dt;
	CircleToCircleCollision();
	SquareArenaCollision();
}

bool Collision::CircleToCircleCollision()
{
	const int object_size = ObjectManager::GetObjectManager()->GetObjectManagerContainer().size();
	
	for (int i = 0; i < object_size; ++i)
	{
		Object* obj_i = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[i].get();

		if (ObjectFilter(obj_i))
		{
			const vector2 obj_i_trans = obj_i->GetTransform().GetTranslation();
			const float obj_i_radius = obj_i->GetTransform().GetScale().x * 30.f;

			for (int j = 0; j < object_size; ++j)
			{
				Object* obj_j = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[j].get();

				if (ObjectFilter(obj_j))
				{
					if (Check_Need_To_Check_Collision(obj_i, obj_j))
					{
						const vector2 obj_j_trans = obj_j->GetTransform().GetTranslation();
						const float obj_j_radius = obj_j->GetTransform().GetScale().x * 30.f;
						const float distance = DistanceBetween(obj_i_trans, obj_j_trans);
						
						if (distance < obj_i_radius + obj_j_radius)
						{
							Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_j, obj_i, Message_Kind::Collision));
							obj_i->Set_Is_It_Collided(true);
							obj_j->Set_Is_It_Collided(true);

							if ((obj_i->Get_Tag() != "item" && obj_j->Get_Tag() != "item") || obj_i->Get_Tag() == "throwing")
							{
								if (obj_i->Get_Tag() == "lock" || obj_j->Get_Tag() == "lock" || obj_j->Get_Tag() == "throwing")
								{
									continue;
								}
								physics.KnockBack(obj_i, obj_j);
							}
						}
						else if((obj_i->Get_Tag() == "lock" && obj_j->Get_Tag() == "player"))
						{
							Collision_Off_Lock_And_Player(obj_j, obj_i);
						}
						else if ((obj_j->Get_Tag() == "lock" && obj_i->Get_Tag() == "player"))
						{
							Collision_Off_Lock_And_Player(obj_i, obj_j);
						}
						
					}
				}
			}
		}
	}
	return false;
}

void Collision::SquareArenaCollision()
{
	const unsigned int object_position_size = static_cast<unsigned int>(ObjectManager::GetObjectManager()->GetObjectManagerContainer().size());
	const float line_max_point = 980;
	const float line_min_point = -980;
	float angle = 0;
	float angle2 = 0;
	for (unsigned int i = 0; i < object_position_size; ++i)
	{
		Object* obj_i = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[i].get();
		vector2 obj_i_trans = obj_i->GetTransform().GetTranslation();
		vector2 obj_i_scale = obj_i->GetTransform().GetScale();

		const double max_x = obj_i_trans.x + (30.0 * obj_i_scale.x);
		const double min_x = obj_i_trans.x - (30.0 * obj_i_scale.x);
		const double max_y = obj_i_trans.y + (30.0 * obj_i_scale.y);
		const double min_y = obj_i_trans.y - (30.0 * obj_i_scale.y);

		if (line_max_point - max_x < 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr && obj_i->GetComponentByTemplate<Throwing>() == nullptr)
		{
			sound.Play(SOUND::Crack);

			vector2 direction_to_go = obj_i->GetComponentByTemplate<Player>()->GetPlayerVelocity();

			angle = RadianToDegree(angle_between({ 0,1 }, direction_to_go));
			angle2 = 2 * (180 - angle);
			angle = 360 - angle2;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			obj_i->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, Message_Kind::Collision_Wall));
		}
		else if (line_max_point - max_y < 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr && obj_i->GetComponentByTemplate<Throwing>() == nullptr)
		{
			sound.Play(SOUND::Crack);

			vector2 direction_to_go = obj_i->GetComponentByTemplate<Player>()->GetPlayerVelocity();
			angle = RadianToDegree(angle_between({ -1,0 }, direction_to_go));

			angle2 = 2 * (180 - angle);
			angle = 360 - angle2;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			obj_i->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, Message_Kind::Collision_Wall));
		}
		else if (line_min_point - min_x > 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr && obj_i->GetComponentByTemplate<Throwing>() == nullptr)
		{
			sound.Play(SOUND::Crack);

			vector2 direction_to_go = obj_i->GetComponentByTemplate<Player>()->GetPlayerVelocity();
			angle = RadianToDegree(angle_between({ 0,-1 }, direction_to_go));

			angle2 = 2 * (180 - angle);
			angle = 360 - angle2;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			obj_i->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, Message_Kind::Collision_Wall));
		}
		else if (line_min_point - min_y > 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr && obj_i->GetComponentByTemplate<Throwing>() == nullptr)
		{
			sound.Play(SOUND::Crack);

			vector2 direction_to_go = obj_i->GetComponentByTemplate<Player>()->GetPlayerVelocity();
			angle = RadianToDegree(angle_between({ 1,0 }, direction_to_go));

			angle2 = 2 * (180 - angle);
			angle = 360 - angle2;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			obj_i->GetComponentByTemplate<Player>()->SetPlayerVelocity(direction_to_go);
			
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, Message_Kind::Collision_Wall));
		}
	}
}

bool Collision::Check_Need_To_Check_Collision(Object* obj_i, Object* obj_j)
{
	/*
	 * Check the object is needing update.
	 */
	if (!obj_i->Get_Need_To_Update())
	{
		return false;
	}
	if (!obj_j->Get_Need_To_Update())
	{
		return false;
	}

	/*
	 * Check the one of objects are already setted collided.
	 */
	if (obj_i->Get_Is_It_Collided() == true || obj_j->Get_Is_It_Collided() == true)
	{
		return false;
	}

	/*
	 * Prevent arena & arena collision
	 * Prevent item & item collision
	 */
	if (obj_j->GetName() == "arena" || obj_i->GetName() == "arena")
	{
		return false;
	}
	if (obj_j->Get_Tag() == "item" && obj_i->Get_Tag() == "item")
	{
		return false;
	}

	/*
	 * Check the object thrown object, other object is throwing object.
	 */
	if (obj_i->Get_Tag() == "throwing")
	{
		if (obj_i->GetName() == "throwing")
		{
			if (obj_i->GetComponentByTemplate<Throwing>()->Get_Throwing_Obj() == obj_j)
			{
				return false;
			}
		}
		else if (obj_i->GetName() == "missile")
		{
			if (obj_i->GetComponentByTemplate<Missile>()->Get_From_Obj() == obj_j)
			{
				return false;
			}
		}
		else if (obj_j->Get_Tag() == "throwing")
		{
			return false;
		}

	}
	else if (obj_j->Get_Tag() == "throwing")
	{
		if (obj_j->GetName() == "throwing")
		{
			if (obj_j->GetComponentByTemplate<Throwing>()->Get_Throwing_Obj() == obj_i)
			{
				return false;
			}
		}
		else if (obj_j->GetName() == "missile")
		{
			if (obj_j->GetComponentByTemplate<Missile>()->Get_From_Obj() == obj_i)
			{
				return false;
			}
		}
		else if (obj_i->Get_Tag() == "throwing")
		{
			return false;
		}

	}

	/*
	 * Check the object lock object, other object is player.
	 */
	if (obj_i->Get_Tag() == "lock")
	{
		if (obj_j->Get_Tag() == "throwing" || obj_j->Get_Tag() == "item")
		{
			return false;
		}
		if (obj_i->GetComponentByTemplate<Lock>()->Get_Locking_Obj() == obj_j)
		{
			return false;
		}
	}

	if (obj_j->Get_Tag() == "lock")
	{
		if (obj_i->Get_Tag() == "throwing" || obj_i->Get_Tag() == "item")
		{
			return false;
		}
		if (obj_j->GetComponentByTemplate<Lock>()->Get_Locking_Obj() == obj_i)
		{
			return false;
		}
	}

	/*
	 * Check the objects are different objects.
	 */
	if (obj_i == obj_j)
	{
		return false;
	}

	/*
	 * Check the both objects are have physics component.
	 * If either object's physics state is ghost, return false.
	 */
	Physics* physics_obj_i = obj_i->GetComponentByTemplate<Physics>();
	Physics* physics_obj_j = obj_j->GetComponentByTemplate<Physics>();

	if (physics_obj_i == nullptr || physics_obj_j == nullptr)
	{
		return false;
	}

	if (physics_obj_i->GetGhostReference() || physics_obj_j->GetGhostReference())
	{
		return false;
	}


	/*
	 * Otherwise, return true.
	 */
	return true;
}

bool Collision::ObjectFilter(Object* obj)
{
	if (obj->Get_Tag() == "player" || obj->Get_Tag() == "item" || obj->Get_Tag() == "throwing" ||
		obj->Get_Tag() == "lock")
	{
		return true;
	}
	
	return false;
}

void Collision::Collision_Off_Lock_And_Player(Object* player, Object* lock)
{
	Lock* info_lock = lock->GetComponentByTemplate<Lock>();

	if(info_lock != nullptr)
	{
		if (info_lock->Get_Locking_Target() == player)
		{
			player->Change_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
		}
		info_lock->Set_Locking_Target(nullptr);
	}
	
}