#include "Collision.h"
#include "ObjectManager.h"
#include "UsefulTools.hpp"
#include "Message_Manager.h"
#include "Physics.h"
#include "Component_Lock.h"
#include "Component_Player.h"
#include "Sound_Manager.h"
#include "Component_Throwing.h"
#include "Engine.hpp"
#include "Component_Missile.h"
#include "Object.h"
#include "Component_Sprite.h"
#include "Component_Button.h"

bool ObjectAndObjectCollision(Object* object_a, Object* object_b)
{
	if (object_a->GetComponentByTemplate<Physics>()->GetGhostReference() == true || object_b->GetComponentByTemplate<Physics>()->GetGhostReference() == true)
	{
		return false;
	}

	const vector2 obj_a_trans = object_a->GetTransform().GetTranslation();
	const vector2 obj_b_trans = object_b->GetTransform().GetTranslation();
	const float obj_a_radius = object_a->GetTransform().GetScale().x * 45.f;
	const float obj_b_radius = object_b->GetTransform().GetScale().x * 45.f;
	const float distance = DistanceBetween(obj_a_trans, obj_b_trans);
	std::string object_a_tag = object_a->Get_Tag();
	std::string object_b_tag = object_b->Get_Tag();
	std::string object_a_name = object_a->Get_Name();
	std::string object_b_name = object_b->Get_Name();
	Physics physics;

	if (distance < obj_a_radius + obj_b_radius)
	{

		/* Player vs Item throwing */
		if (object_a_name == "throwing")
		{
			if (object_a->GetComponentByTemplate<Throwing>()->Get_Throwing_Obj() != object_b)
			{
				physics.PushPlayer(object_b, object_a);
				Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));
			}
		}
		else if (object_b_name == "throwing")
		{
			if (object_b->GetComponentByTemplate<Throwing>()->Get_Throwing_Obj() != object_a)
			{
				physics.PushPlayer(object_a, object_b);
				Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));
			}
		}
		/* Player vs Item Missile */
		else if (object_a_name == "missile")
		{

			physics.PushPlayer(object_b, object_a);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));

		}
		else if (object_b_name == "missile")
		{

			physics.PushPlayer(object_a, object_b);
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));

		}
		/* Player vs Item Lock */
		else if (object_a_tag == "lock")
		{
			if (object_a->GetComponentByTemplate<Lock>()->Get_Locking_Obj() != object_b)
			{
				Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));
			}
		}
		else if (object_b_tag == "lock")
		{
			if (object_b->GetComponentByTemplate<Lock>()->Get_Locking_Obj() != object_a)
			{
				Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));
			}
		}
		/* Player vs Item Mine */
		else if (object_a_tag == "install_mine")
		{
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));
		}
		else if (object_b_tag == "install_mine")
		{
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));
		}


		//find arena and player collision
		else if (object_a_tag == "arena")
		{
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));
		}
		else if (object_b_tag == "arena")
		{
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));
		}
		else if (object_a_tag == "button" && object_b_tag == "player")
		{
			Component_Button* button_info = object_a->GetComponentByTemplate<Component_Button>();
			button_info->Collided(object_b);
		}
		else if (object_b_tag == "button" && object_a_tag == "player")
		{
			Component_Button* button_info = object_b->GetComponentByTemplate<Component_Button>();
			button_info->Collided(object_a);
		}

		else
		{
			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object_a, object_b, Message_Kind::Collision));
		}
	}
	/* Player vs Unlock */
	else if ((object_a_tag == "lock" && object_b_tag == "player"))
	{
		Collision_Off_Lock_And_Player(object_b, object_a);
	}
	else if ((object_b_tag == "lock" && object_a_tag == "player"))
	{
		Collision_Off_Lock_And_Player(object_a, object_b);
	}

	else if ((object_a_tag == "button" && object_b_tag == "player"))
	{
		Component_Button* button_info = object_a->GetComponentByTemplate<Component_Button>();
		button_info->Collided_Off(object_b);
	}
	else if ((object_b_tag == "button" && object_a_tag == "player"))
	{
		Component_Button* button_info = object_b->GetComponentByTemplate<Component_Button>();
		button_info->Collided_Off(object_a);
	}

	else if (object_a_tag == "install_mine" && object_b_tag == "player")
	{
		if (obj_a_radius + obj_b_radius + 200 > distance)
		{
			FMOD_BOOL isPlaying;
			FMOD_Channel_IsPlaying(sound.channel[29], &isPlaying);
			if (sound.mineAlarm <= 0)
			{
				sound.Play(SOUND::MineAlarm);
				sound.mineAlarm = 60.f;
			}
		}
	}
	else if (object_b_tag == "install_mine" && object_a_tag == "player")
	{
		if (obj_a_radius + obj_b_radius + 200 > distance)
		{
			FMOD_BOOL isPlaying;
			FMOD_Channel_IsPlaying(sound.channel[29], &isPlaying);
			if (sound.mineAlarm <= 0)
			{
				sound.Play(SOUND::MineAlarm);
				sound.mineAlarm = 60.f;
			}
		}
	}
	return false;
}

void ArenaAndObjectCollision(Object* object)
{
	const float x_max_point = 1720;
	const float x_min_point = -1720;
	const float y_max_point = 700;
	const float y_min_point = -900;
	float angle;
	float temp_angle;

	const vector2 object_translation = object->GetTransform().GetTranslation();
	const vector2 object_scale = object->GetTransform().GetScale();

	const double max_x = object_translation.x + (40.0 * object_scale.x);
	const double min_x = object_translation.x - (40.0 * object_scale.x);
	const double max_y = object_translation.y + (40.0 * object_scale.y);
	const double min_y = object_translation.y - (40.0 * object_scale.y);

	Player* object_player = object->GetComponentByTemplate<Player>();
	if(object_translation.x < -1650 || object_translation.x > 1650 || object_translation.y < -850 || object_translation.y > 630)
	{
		object->SetTranslation({ 0,0 });
	}
	if (object_player != nullptr)
	{
		if (x_max_point - max_x < 0)
		{
			if (DeleteUnlessPlayer(object))
			{
				return;
			}
			vector2 direction_to_go = object_player->GetPlayerVelocity();

			angle = RadianToDegree(angle_between({ 0,1 }, direction_to_go));
			temp_angle = 2 * (180 - angle);
			angle = 360 - temp_angle;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			object_player->SetPlayerVelocity(direction_to_go);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, Message_Kind::Collision_Wall));
		}
		else if (y_max_point - max_y < 0)
		{
			if (DeleteUnlessPlayer(object))
			{
				return;
			}

			vector2 direction_to_go = object_player->GetPlayerVelocity();
			angle = RadianToDegree(angle_between({ -1,0 }, direction_to_go));

			temp_angle = 2 * (180 - angle);
			angle = 360 - temp_angle;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			object_player->SetPlayerVelocity(direction_to_go);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, Message_Kind::Collision_Wall));
		}
		else if (x_min_point - min_x > 0)
		{
			if (DeleteUnlessPlayer(object))
			{
				return;
			}
			vector2 direction_to_go = object_player->GetPlayerVelocity();
			angle = RadianToDegree(angle_between({ 0,-1 }, direction_to_go));

			temp_angle = 2 * (180 - angle);
			angle = 360 - temp_angle;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			object_player->SetPlayerVelocity(direction_to_go);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, Message_Kind::Collision_Wall));
		}
		else if (y_min_point - min_y > 0)
		{
			if (DeleteUnlessPlayer(object))
			{
				return;
			}
			vector2 direction_to_go = object_player->GetPlayerVelocity();
			angle = RadianToDegree(angle_between({ 1,0 }, direction_to_go));

			temp_angle = 2 * (180 - angle);
			angle = 360 - temp_angle;
			direction_to_go = rotate_by(DegreeToRadian(angle), direction_to_go);
			object_player->SetPlayerVelocity(direction_to_go);

			Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, Message_Kind::Collision_Wall));
		}
	}
}

void Collision_Off_Lock_And_Player(Object* player, Object* lock)
{
	Lock* info_lock = lock->GetComponentByTemplate<Lock>();

	if (info_lock != nullptr)
	{
		if (info_lock->Get_Locking_Target() == player)
		{
			player->Change_Sprite(player->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
		}
		info_lock->Set_Locking_Target(nullptr);
	}
}

bool DeleteUnlessPlayer(Object* object)
{
	Throwing* object_throwing = object->GetComponentByTemplate<Throwing>();
	Lock* object_lock = object->GetComponentByTemplate<Lock>();

	if (object_throwing != nullptr || object_lock != nullptr)
	{
		if (object_lock != nullptr)
		{
			Object* locking_obj = object_lock->Get_Locking_Obj();
			Object* locking_target = object_lock->Get_Locking_Target();

			if (locking_obj != nullptr)
			{
				locking_obj->Change_Sprite(locking_obj->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
			}

			if (locking_target != nullptr)
			{
				locking_target->Change_Sprite(locking_target->Find_Sprite_By_Type(Sprite_Type::Player_Normal));
			}
		}
		object->SetDeadCondition(true);
		return true;
	}

	return false;
}
