/*
 * Author		:Sangmin Kim
 * File			:ObjectManager.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for object manager. which update all objects in container.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "ObjectManager.h"
#include <functional>
#include "StateManager.h"
#include "Component.hpp"
#include "Component_Player.h"

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
    if (StateManager::GetStateManager()->is_pause)//
    {
        delete_obj.clear();

        for (auto& obj : objects)
        {
            if (obj->Get_Need_To_Update())
            {
                for (auto component : obj->GetComponentContainer())
                {
                	if(component->Get_Need_Update())
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
        }
    }
    else
    {
    }
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
    objects.clear();
    delete_obj.clear();
}

void ObjectManager::AddObject(Object* obj)
{
    objects.push_back(std::shared_ptr<Object>(obj));
}

void ObjectManager::DeleteObject(std::shared_ptr<Object> obj)
{
	if(!obj->Get_Pointed_By().empty())
	{
		for(auto ptr : obj->Get_Pointed_By())
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