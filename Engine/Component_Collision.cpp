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

#define  PI  3.14159265359

float RadianToDegree(float radian)
{
	float degree = static_cast<float>(radian * (180 / PI));

	return degree;
}

float DegreeToRadian(float degree)
{
	float radian = static_cast<float>(degree * (PI / 180));

	return radian;
}

void Collision::Init(Object* obj)
{
	m_owner = obj;
}

bool Collision::BoxToBoxCollision(Mesh mesh) const
{
	if (m_owner->GetMesh().GetPoint(0).x > mesh.GetPoint(2).x || m_owner->GetMesh().GetPoint(0).y > mesh.GetPoint(2).y)
	{
		return false;
	}
	else if (m_owner->GetMesh().GetPoint(1).x > mesh.GetPoint(3).x || m_owner->GetMesh().GetPoint(1).y < mesh.GetPoint(3).y)
	{
		return false;
	}
	else if (m_owner->GetMesh().GetPoint(2).x < mesh.GetPoint(0).x || m_owner->GetMesh().GetPoint(2).y < mesh.GetPoint(0).y)
	{
		return false;
	}
	else if (m_owner->GetMesh().GetPoint(3).x < mesh.GetPoint(1).x || m_owner->GetMesh().GetPoint(3).y > mesh.GetPoint(1).y)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Collision::CircleToCircleCollision()
{
	const unsigned int object_position_size = static_cast<unsigned int>(ObjectManager::GetObjectManager()->GetObjectManagerContainer().size());

	for (unsigned int i = 0; i < object_position_size; ++i)
	{
		Object* obj_i = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[i].get();

		if (Filter_Object(obj_i))
		{
			const vector2 obj_i_trans = obj_i->GetTransform().GetTranslation();
			const float obj_i_radius = obj_i->GetTransform().GetScale().x * 30.f;

			for (unsigned int j = 0; j < object_position_size; ++j)
			{
				Object* obj_j = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[j].get();

				if (Filter_Object(obj_j))
				{
					if (Check_Need_To_Check_Collision(obj_i, obj_j))
					{
						const vector2 obj_j_trans = obj_j->GetTransform().GetTranslation();
						const float obj_j_radius = obj_j->GetTransform().GetScale().x * 30.f;

						const float distance = sqrt((obj_i_trans.x - obj_j_trans.x) * (obj_i_trans.x - obj_j_trans.x) + (obj_i_trans.y - obj_j_trans.y) * (obj_i_trans.y - obj_j_trans.y));
						if (distance < obj_i_radius + obj_j_radius)
						{
							Physics* obj_i_physics = obj_i->GetComponentByTemplate<Physics>();
							Physics* obj_j_physics = obj_j->GetComponentByTemplate<Physics>();

							obj_i_physics->Get_Save_Acceleration_Reference().x = obj_i_physics->GetAcceleration().x;
							obj_i_physics->Get_Save_Acceleration_Reference().y = obj_i_physics->GetAcceleration().y;
							obj_j_physics->Get_Save_Acceleration_Reference().x = obj_j_physics->GetAcceleration().x;
							obj_j_physics->Get_Save_Acceleration_Reference().y = obj_j_physics->GetAcceleration().y;

							Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_j, obj_i, "collision"));
							obj_i->Set_Is_It_Collided(true);
							obj_j->Set_Is_It_Collided(true);

							if ((obj_i->Get_Tag() != "item" && obj_j->Get_Tag() != "item"))
							{
								if(obj_i->Get_Tag() == "lock" || obj_j->Get_Tag() == "lock")
								{
									continue;
								}
								physics.KnockBack(obj_i, obj_j);
							}
						}
						else if (obj_i->Get_Tag() == "lock")
						{
							if (obj_j->Get_Tag() == "player")
							{
								if (obj_i->GetComponentByTemplate<Lock>()->Get_Locking_Target() == obj_j)
								{
									Component* change_sprite_to = obj_j->Find_Component_By_Name("normal");
									Component* current_sprite = obj_j->Find_Component_By_Name("lock");
									change_sprite_to->Set_Need_Update(true);
									current_sprite->Set_Need_Update(false);
									obj_i->GetComponentByTemplate<Lock>()->Set_Locking_Target(nullptr);
								}
							}
						}
						else if (obj_j->Get_Tag() == "lock")
						{
							if (obj_i->Get_Tag() == "player")
							{
								if (obj_j->GetComponentByTemplate<Lock>()->Get_Locking_Target() == obj_i)
								{
									Component* change_sprite_to = obj_i->Find_Component_By_Name("normal");
									Component* current_sprite = obj_i->Find_Component_By_Name("lock");
									change_sprite_to->Set_Need_Update(true);
									current_sprite->Set_Need_Update(false);
									obj_j->GetComponentByTemplate<Lock>()->Set_Locking_Target(nullptr);
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void Collision::CircleArenaCollision()
{
	const unsigned int object_position_size = static_cast<unsigned int>(ObjectManager::GetObjectManager()->GetObjectManagerContainer().size());

	for (unsigned int i = 0; i < object_position_size; ++i)
	{
		Object* obj_i = ObjectManager::GetObjectManager()->GetObjectManagerContainer()[i].get();
		vector2 obj_i_trans = obj_i->GetTransform().GetTranslation();

		const float distance = sqrt((obj_i_trans.x * obj_i_trans.x) + (obj_i_trans.y * obj_i_trans.y));

		if (distance >= 10000)
		{

			const vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();
			obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(-direction_to_go);
		}
	}
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

		if (line_max_point - max_x < 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr)
		{
			sound.Play(SOUND::Crack);

			vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();

			angle = RadianToDegree(angle_between({ 0,1 }, direction_to_go));
			angle2 = 2 * (180 - angle);
			angle = 360 - angle2;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go);

			obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().x;
			obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().y;

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, "wall_collision"));
		}
		else if (line_max_point - max_y < 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr)
		{
			sound.Play(SOUND::Crack);

			vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();
			angle = RadianToDegree(angle_between({ -1,0 }, direction_to_go));

			angle2 = 2 * (180 - angle);
			angle = 360 - angle2;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go);

			obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().x;
			obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().y;

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, "wall_collision"));
		}
		else if (line_min_point - min_x > 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr)
		{
			sound.Play(SOUND::Crack);

			vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();
			angle = RadianToDegree(angle_between({ 0,-1 }, direction_to_go));

			angle2 = 2 * (180 - angle);
			angle = 360 - angle2;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go);

			obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().x;
			obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().y;

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, "wall_collision"));
		}
		else if (line_min_point - min_y > 0 && obj_i->GetComponentByTemplate<Physics>() != nullptr)
		{
			sound.Play(SOUND::Crack);

			vector2 direction_to_go = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration();
			angle = RadianToDegree(angle_between({ 1,0 }, direction_to_go));

			angle2 = 2 * (180 - angle);
			angle = 360 - angle2;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			obj_i->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go);

			obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().x = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().x;
			obj_i->GetComponentByTemplate<Physics>()->Get_Save_Acceleration_Reference().y = obj_i->GetComponentByTemplate<Physics>()->GetAcceleration().y;

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(obj_i, nullptr, "wall_collision"));
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
		if (obj_i->GetComponentByTemplate<Throwing>()->Get_Throwing_Obj() == obj_j)
		{
			return false;
		}
	}
	else if (obj_j->Get_Tag() == "throwing")
	{
		if (obj_j->GetComponentByTemplate<Throwing>()->Get_Throwing_Obj() == obj_i)
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
		if (obj_i->GetComponentByTemplate<Lock>()->Get_Throwing_Obj() == obj_j)
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
		if (obj_j->GetComponentByTemplate<Lock>()->Get_Throwing_Obj() == obj_i)
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

	if (physics_obj_i->Get_Ghost_Collision_Reference() || physics_obj_j->Get_Ghost_Collision_Reference())
	{
		return false;
	}


	/*
	 * Otherwise, return true.
	 */
	return true;
}

bool Collision::Filter_Object(Object* obj)
{
	if (obj->Get_Tag() == "player" || obj->Get_Tag() == "item" || obj->Get_Tag() == "throwing" ||
		obj->Get_Tag() == "lock")
	{
		return true;
	}
	return false;
}

void Collision::Update(float dt)
{
	sound_timer += dt;
	CircleToCircleCollision();
	SquareArenaCollision();
}
