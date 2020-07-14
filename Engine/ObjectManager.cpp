/*
 * Author		:Sangmin Kim
 * File			:ObjectManager.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Object Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */
#include "ObjectManager.h"
#include <functional>
#include "StateManager.h"
#include "Component.hpp"
#include "Component_Sprite.h"
#include "Collision.h"

ObjectManager* ObjectManager::object_manager = nullptr;

ObjectManager* ObjectManager::GetObjectManager()
{
	if (object_manager == nullptr)
		object_manager = new ObjectManager();

	return object_manager;
}

void ObjectManager::Init()
{
	objects.clear();
	delete_obj.clear();
}

void ObjectManager::Update(float dt)
{
	if (StateManager::GetStateManager()->GetPrevState() != nullptr)
	{
		if (!StateManager::GetStateManager()->level_state->is_pause)//
		{
			delete_obj.clear();
			float t_timer = StateManager::GetStateManager()->level_state->Get_Trans_Timer();

			std::vector<Object*> timers;

			if (t_timer > 0.f)
			{
				timers = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("timer");
			}

			for (auto& obj : objects)
			{
				if (obj != nullptr)
				{
					if (obj->Get_Need_To_Update())
					{
						obj->object_state = StateManager::GetStateManager()->GetCurrentState()->GetStateInfo();

						if (t_timer <= 0.f)
						{
							for (auto component : obj->GetComponentContainer())
							{
								if (component->Get_Need_Update())
								{
									component->Update(dt);
								}
							}
						}
						else
						{
							if (!timers.empty())
							{
								if (std::find(timers.begin(), timers.end(), obj.get()) == timers.end())
								{
									Component* sprite = obj->Get_Current_Sprite();
									sprite->Update(dt);
								}
								else
								{
									for (auto component : obj->GetComponentContainer())
									{
										if (component->Get_Need_Update())
										{
											component->Update(dt);
										}
									}
								}
							}
						}
					}
					if (obj != nullptr)
					{
						if (obj->IsDead())
						{
							delete_obj.push_back(obj);
						}
					}
				}


			}
			for (auto& remove_obj : delete_obj)
			{
				DeleteObject(remove_obj);
				remove_obj = nullptr;
			}
		}
		else if (StateManager::GetStateManager()->level_state->is_pause)
		{
			delete_obj.clear();

			for (auto& obj : objects)
			{
				if (obj->Get_Need_To_Update() && obj->object_state != GameState::Game)
				{
					for (auto component : obj->GetComponentContainer())
					{
						if (component->Get_Need_Update())
						{
							component->Update(dt);
						}
					}
				}
				if (obj->IsDead())
				{
					delete_obj.push_back(obj);
				}
			}
			for (auto& remove_obj : delete_obj)
			{
				DeleteObject(remove_obj);
				remove_obj = nullptr;
			}
		}
	}

	ObjectCollision();
}

void ObjectManager::Delete()
{
	objects.clear();
	delete_obj.clear();

	delete object_manager;
	object_manager = nullptr;
}

void ObjectManager::Clear()
{
	Object* check1 = objects[0].get();
	objects.clear();
	delete_obj.clear();
}

void ObjectManager::AddObject(Object* obj)
{
	objects.push_back(std::shared_ptr<Object>(obj));
}

void ObjectManager::Add_Object_Instancing(Object* obj)
{
	objects_instancing.push_back(std::shared_ptr<Object>(obj));
}

void ObjectManager::DeleteObject(std::shared_ptr<Object> obj)
{
	if (!obj->Get_Pointed_By().empty())
	{
		for (auto ptr : obj->Get_Pointed_By())
		{
			*ptr = nullptr;
		}
	}
	objects.erase(std::find(objects.begin(), objects.end(), obj));

}


std::vector<Object*> ObjectManager::Find_Objects_By_Tag(std::string tag)
{
	std::vector<Object*> objects_have_tag;

	for (auto object : objects)
	{
		if (object.get()->Get_Tag() == tag)
		{
			objects_have_tag.push_back(object.get());
		}
	}

	return objects_have_tag;
}

Object* ObjectManager::Find_Object_By_Name(std::string name)
{
	for (auto object : objects)
	{
		if (object.get()->GetName() == name)
		{
			return object.get();
		}
	}
	return nullptr;
}

void ObjectManager::Instancing_Update(float dt)
{
	for (auto obj : objects_instancing)
	{
		obj->GetComponentByTemplate<Sprite>()->Update_Instancing(dt);
	}
}

void ObjectManager::ObjectCollision()
{
	const int object_size = objects.size();

	for (int i = 0; i < object_size; ++i)
	{
		if (objects[i]->GetNeedCollision() == true)
		{
			ArenaAndObjectCollision(objects[i].get());

			for (int j = 0; j < object_size; ++j)
			{
				if (objects[j]->GetNeedCollision() == true && objects[i] != objects[j])
				{
					ObjectAndObjectCollision(objects[i].get(), objects[j].get());
				}
			}
		}
	}
}
