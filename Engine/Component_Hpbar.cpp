/*
 * Author		:Sangmin Kim
 * File			:Component_Hpbar.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Component for hpbar objects for each player.
 *				 Check the enemy's current health, decrease the scale,
 *				 manipulate the translation offset.
 *				 If the player is dead, send message for respawn to referee.
 *
 *	copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Hpbar.h"
#include "Object.h"
#include "Message_Manager.h"
#include "Referee.h"
#include "Component_Text.h"
#include "ObjectManager.h"
#include "Component_Player.h"
#include "Player_Ui.h"

void Hp_Bar::Init(Object* obj)
{
    m_owner = obj;
    offset = 0;
    hp = 100;
}

void Hp_Bar::Update(float dt)
{
}

void Hp_Bar::Decrease(float dmg)
{
    if (m_owner->GetTransform().GetScale_Reference().x > 0)
    {
        Object* Hp_Owner_Obj = m_owner->Get_This_Obj_Owner();

        float damage = dmg;
        m_owner->GetTransform().GetScale_Reference().x -= damage;
        offset -= static_cast<int>(damage * 50);

        if (m_owner->Get_This_Obj_Owner()->GetComponentByTemplate<Player>()->Get_Ui()->Get_Hp_Info()->GetTransform().GetScale_Reference().x - damage * 4 >= 0.f)
        {
            m_owner->Get_This_Obj_Owner()->GetComponentByTemplate<Player>()->Get_Ui()->Get_Hp_Info()->GetTransform().GetScale_Reference().x -= damage * 4;
        }

        m_owner->Get_This_Obj_Owner()->GetComponentByTemplate<Player>()->Get_Ui()->Get_Hp_Info()->GetMesh().Get_Is_Moved() = true;
        if (m_owner->GetTransform().GetScale_Reference().x <= 0)
        {
            m_owner->Get_This_Obj_Owner()->GetComponentByTemplate<Player>()->Get_Ui()->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 0.5f,0.5f,0.5f,0.5f };
            m_owner->Get_This_Obj_Owner()->GetComponentByTemplate<Player>()->Get_Ui()->Get_Hp_Info()->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 0.5f,0.5f,0.5f,0.5f };

            if (m_owner->Get_This_Obj_Owner()->Get_Hitted_By() != nullptr)
            {
                m_owner->Get_This_Obj_Owner()->Get_Hitted_By()->GetTransform().GetScale_Reference() += {0.3f, 0.3f};
                m_owner->Get_This_Obj_Owner()->Get_Hitted_By()->Get_Plus_Dmg() += 0.1f;
            }
            m_owner->SetDeadCondition(true);
            Hp_Owner_Obj->SetDeadCondition(true);
            Message_Manager::Get_Message_Manager()->Save_Message(new Message(Referee::Get_Referee(), Hp_Owner_Obj, "respawn"));
        }
    }
}

int& Hp_Bar::Get_Set_Offset()
{
    return offset;
}