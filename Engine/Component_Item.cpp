/*
 * Author		:Suhwan Kim
 * File			:Component_Item.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Basic ai movement for item object is implemented in here.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Item.h"
#include "Object.h"
#include "Physics.h"
#include "UsefulTools.hpp"

void Item::Init(Object* obj)
{
    m_owner = obj;
}

void Item::Update(float dt)
{
	/*if(timer < 0.f)
	{
        random_dir = RandomNumberGenerator(1, 4);
        timer = 2.f;
	}
    else
    {
        timer -= dt;
        vector2& pos = m_owner->GetTransform().GetTranslation_Reference();

        switch (random_dir)
        {
        case 1:
            pos.x += dt * speed;
            pos.y += dt * speed;
            break;
        case 2:
            pos.x -= dt * speed;
            pos.y -= dt * speed;
            break;
        case 3:
            pos.x += dt * speed;
            pos.y -= dt * speed;
            break;
        case 4:
            pos.x -= dt * speed;
            pos.y += dt * speed;
            break;
        default:
            ;
        }
    }*/
}

void Item::Set_Kind(Item_Kind kind)
{
    this->this_kind = kind;
}

Item::Item_Kind Item::Get_Kind()
{ 
    return this_kind;
}