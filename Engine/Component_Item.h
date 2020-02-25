/*
 * Author		:Suwhan Kim
 * File			:Component_Item.h
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Component_Item.cpp
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
        Bulkup
    };

    void Init(Object* obj) override;
    void Update(float dt) override;
    void Set_Kind(Item_Kind kind);
    Item_Kind Get_Kind();

private:
    Item_Kind this_kind = Item_Kind::None;
};