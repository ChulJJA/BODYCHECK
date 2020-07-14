/*
 * Author		:Sangmin Kim
 * File			:Object.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Object
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include <algorithm>
#include "Object.h"
#include "Component_Sprite.h"

void Object::Change_Sprite(Component* sprite)
{
	if (sprite != nullptr)
	{
		if (current_showing_sprite != sprite)
		{
			last_sprite = current_showing_sprite;
		}
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
	if (sprite != nullptr)
	{
		for (auto i : comp_sprite)
		{
			if (i != sprite)
			{
				i->Set_Need_Update(false);
			}
		}
		sprite->Set_Need_Update(true);
		current_showing_sprite = sprite;
	}

}


Object::~Object()
{
	for (auto& data : components_)
	{
		delete data;
	}
	//components_.clear();
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
	for (auto component : comp_sprite)
	{
		if (component->GetComponentName() == name)
		{
			return component;
		}
	}
	return nullptr;
}


Component* Object::Find_Sprite_By_Type(Sprite_Type type)
{
	for (auto component : comp_sprite)
	{
		if (reinterpret_cast<Sprite*>(component)->Get_Sprite_Type() == type)
		{
			return component;
		}
	}
	return nullptr;
}

Component* Object::Find_Comp_By_Name(std::string name)
{
	for (auto component : components_)
	{
		if (component->GetComponentName() == name)
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

void Object::Delete_All_Components_But_Sprite()
{
	Component* comp_player = Find_Comp_By_Name("player");

	if(comp_player != nullptr)
	{
		DeleteComponent(comp_player);
	}

	Component* comp_physics = Find_Comp_By_Name("physics");

	if(comp_physics != nullptr)
	{
		DeleteComponent(comp_physics);
	}
	
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
void Object::Set_Need_To_Update(bool toggle)
{
	need_to_update = toggle;
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
