/*
 * Author		:Sangmin Kim
 * File			:Object.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:cpp file for object. Which contains components, update & initialize the components.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include <algorithm>
#include "Object.h"
#include "Component_Sprite.h"

void Object::Change_Sprite(Component* sprite)
{
	if(sprite != nullptr)
	{
		current_showing_sprite->Set_Need_Update(false);
		sprite->Set_Need_Update(true);
		current_showing_sprite = sprite;
	}
}

Component* Object::Get_Current_Sprite()
{
	return current_showing_sprite;
}

void Object::Set_Current_Sprite(Component* sprite)
{
	current_showing_sprite = sprite;
}

void Object::AddComponent(Component* comp, std::string name, bool toggle)
{
    comp->Init(this);
	comp->Set_Need_Update(toggle);
	comp->SetComponentName(name);
    components_.push_back(comp);
}

void Object::DeleteComponent(Component* comp)
{
    Component* for_erase = comp;
    components_.erase(std::find(components_.begin(), components_.end(), comp));
    delete for_erase;
}

Component* Object::Find_Sprite_By_Name(std::string name)
{
	for(auto component : comp_sprite)
	{
		if(component->GetComponentName() == name)
		{
			return component;
		}
	}
	return nullptr;
}

void Object::SetTranslation(vector2 pos)
{
    m_transform.SetTranslation(pos);
}

void Object::SetRotation(float angle)
{
    m_transform.SetRotation(angle);
}

void Object::SetScale(vector2 scale)
{
    m_transform.SetScale(scale);
}

void Object::SetScale(float scale)
{
    m_transform.SetScale(scale);
}

void Object::SetDepth(float depth)
{
    m_transform.SetDepth(depth);
}

void Object::SetMesh(Mesh mesh)
{
    m_mesh = mesh;
}

void Object::Set_Debug_Mesh(Mesh mesh)
{
    m_debug_mesh = mesh;
}

std::string Object::GetName()
{
    return m_name;
}

bool Object::Get_Need_To_Update()
{
    return need_to_update;
}

Object* Object::Get_Belong_Object_By_Name(std::string name)
{
    if (!belongs_object.empty())
    {
        for (Object* obj : belongs_object)
        {
            if (obj->GetName() == name)
            {
                return obj;
            }
        }
    }
    return nullptr;
}

Object* Object::Get_Belong_Object_By_Tag(std::string tag)
{
    if (!belongs_object.empty())
    {
        for (Object* obj : belongs_object)
        {
            if (obj->Get_Tag() == tag)
            {
                return obj;
            }
        }
    }
    return nullptr;
}

bool Object::GetNeedCollision()
{
    return need_collision;
}

void Object::SetNeedCollision(bool collision)
{
    need_collision = collision;
}
