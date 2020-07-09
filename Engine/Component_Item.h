/*
 * Author		:Sangmin Kim
 * File			:Component_Item.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Component Item
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include "Component.hpp"

class Item : public Component
{
public:
    enum class Item_Kind
    {
        None,
        Dash,
        HP,
        Bulkup,
    	Throwing,
    	Magnatic,
		Time_Pause,
		Reverse_Moving,
    	Missile,
        Mine
    };

    void Init(Object* obj) override;
    void Update(float dt) override;
    void Set_Kind(Item_Kind kind);
    Item_Kind Get_Kind();

private:
    Item_Kind this_kind = Item_Kind::None;
    float timer = -1.f;
    int random_dir = 0;
    const float speed = 200.f;
};