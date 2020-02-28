/*
 * Author		:Chulseung Lee
 * File			:Physics.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Acceleration / Knockback / user input by controller is implemented.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Physics.h"
#include "ObjectManager.h"
#include <cmath>
#include "vector2.hpp"
#include "Input.h"
#include "Component_Sprite.h"
#include "Component_Player.h"
#include "Player_Ui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Component_Hpbar.h"
#include "Message_Manager.h"
#include "Engine.hpp"
#include "Message.h"

Physics::Physics(bool ghost_collision_mode) : ghost_collision_mode(ghost_collision_mode)
{
}

void Physics::Init(Object* obj)
{
    m_owner = obj;
    m_owner->Get_Component_Info_Reference().component_info_physics = true;
}

void Physics::Acceleration(float max_accel, float min_accel)
{
    int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    int present2 = glfwJoystickPresent(GLFW_JOYSTICK_2);
    int present3 = glfwJoystickPresent(GLFW_JOYSTICK_3);
    int present4 = glfwJoystickPresent(GLFW_JOYSTICK_4);

    if (m_owner->GetName() == "first" && present)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    }
    else if (m_owner->GetName() == "second" && present2)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axesCount);
    }
    else if (m_owner->GetName() == "third" && present3)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_3, &axesCount);
    }
    else if (m_owner->GetName() == "forth" && present4)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_4, &axesCount);
    }
    else
    {
        if (input.Is_Key_Pressed(GLFW_KEY_W))
        {
            if (input.Is_Key_Pressed(GLFW_KEY_W) && input.Is_Key_Pressed(GLFW_KEY_A))
            {
                if (acceleration.x >= 0 && acceleration.y >= 0)
                {
                    acceleration += {-max_accel, min_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else if (acceleration.x >= 0 && acceleration.y < 0)
                {
                    acceleration += {-max_accel, max_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else if (acceleration.x < 0 && acceleration.y >= 0)
                {
                    acceleration += {-min_accel, min_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else
                {
                    acceleration += {-min_accel, max_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
            }
            else if (input.Is_Key_Pressed(GLFW_KEY_W) && input.Is_Key_Pressed(GLFW_KEY_D))
            {
                if (acceleration.x >= 0 && acceleration.y >= 0)
                {
                    acceleration += {min_accel, min_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else if (acceleration.x >= 0 && acceleration.y < 0)
                {
                    acceleration += {min_accel, max_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else if (acceleration.x < 0 && acceleration.y >= 0)
                {
                    acceleration += {max_accel, min_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else
                {
                    acceleration += {max_accel, max_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
            }
            else
            {
                if (abs(acceleration.x) >= 0)
                {
                    acceleration.x -= acceleration.x / 100;
                }
                if (acceleration.y >= 0)
                {
                    acceleration += {0.00, min_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else if (acceleration.y < 0)
                {
                    acceleration += {0.00, max_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
            }
        }
        else if (input.Is_Key_Pressed(GLFW_KEY_A))
        {
            if (input.Is_Key_Pressed(GLFW_KEY_A) && input.Is_Key_Pressed(GLFW_KEY_S))
            {
                if (acceleration.x >= 0 && acceleration.y >= 0)
                {
                    acceleration += {-max_accel, -max_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else if (acceleration.x >= 0 && acceleration.y < 0)
                {
                    acceleration += {-max_accel, -min_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else if (acceleration.x < 0 && acceleration.y >= 0)
                {
                    acceleration += {-min_accel, -max_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else
                {
                    acceleration += {-min_accel, -min_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
            }
            else
            {
                if (acceleration.x >= 0)
                {
                    acceleration.x += -max_accel;
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else
                {
                    acceleration.x += -min_accel;
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                if (abs(acceleration.y) >= 0)
                {
                    acceleration.y -= acceleration.y / 100;
                }
            }
        }
        else if (input.Is_Key_Pressed(GLFW_KEY_S))
        {
            if (input.Is_Key_Pressed(GLFW_KEY_S) && input.Is_Key_Pressed(GLFW_KEY_D))
            {
                if (acceleration.x >= 0 && acceleration.y >= 0)
                {
                    acceleration += {min_accel, -max_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else if (acceleration.x >= 0 && acceleration.y < 0)
                {
                    acceleration += {min_accel, -min_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else if (acceleration.x < 0 && acceleration.y >= 0)
                {
                    acceleration += {max_accel, -max_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else
                {
                    acceleration += {max_accel, -min_accel};
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
            }
            else
            {
                if (abs(acceleration.x) >= 0)
                {
                    acceleration.x -= acceleration.x / 100;
                }
                if (acceleration.y >= 0)
                {
                    acceleration.y += -max_accel;
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
                else
                {
                    acceleration.y += -min_accel;
                    m_owner->GetTransform().AddTranslation(acceleration);
                    m_owner->GetMesh().Get_Is_Moved() = true;
                }
            }
        }
        else if (input.Is_Key_Pressed(GLFW_KEY_D))
        {
            if (acceleration.x >= 0)
            {
                acceleration.x += min_accel;
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                acceleration.x += max_accel;
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            if (abs(acceleration.y) >= 0)
            {
                acceleration.y -= acceleration.y / 100;
            }
        }
        else
        {
            acceleration += {-acceleration.x / 100, -acceleration.y / 100};
            m_owner->GetTransform().AddTranslation(acceleration);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }

        return;
    }
    if (axes[1] < -0.2)
    {
        if (axes[1] < -0.2 && axes[0] < -0.2)
        {
            if (acceleration.x >= 0 && acceleration.y >= 0)
            {
                acceleration += {-max_accel, min_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (acceleration.x >= 0 && acceleration.y < 0)
            {
                acceleration += {-max_accel, max_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (acceleration.x < 0 && acceleration.y >= 0)
            {
                acceleration += {-min_accel, min_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                acceleration += {-min_accel, max_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
        }
        else if (axes[1] < -0.2 && axes[0] > 0.2)
        {
            if (acceleration.x >= 0 && acceleration.y >= 0)
            {
                acceleration += {min_accel, min_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (acceleration.x >= 0 && acceleration.y < 0)
            {
                acceleration += {min_accel, max_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (acceleration.x < 0 && acceleration.y >= 0)
            {
                acceleration += {max_accel, min_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                acceleration += {max_accel, max_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
        }
        else
        {
            if (abs(acceleration.x) >= 0)
            {
                acceleration.x -= acceleration.x / 100;
            }
            if (acceleration.y >= 0)
            {
                acceleration += {0.00, min_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (acceleration.y < 0)
            {
                acceleration += {0.00, max_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
        }
    }
    else if (axes[0] < -0.2)
    {
        if (axes[0] < -0.2 && axes[1] > 0.2)
        {
            if (acceleration.x >= 0 && acceleration.y >= 0)
            {
                acceleration += {-max_accel, -max_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (acceleration.x >= 0 && acceleration.y < 0)
            {
                acceleration += {-max_accel, -min_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (acceleration.x < 0 && acceleration.y >= 0)
            {
                acceleration += {-min_accel, -max_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                acceleration += {-min_accel, -min_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
        }
        else
        {
            if (acceleration.x >= 0)
            {
                acceleration.x += -max_accel;
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                acceleration.x += -min_accel;
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            if (abs(acceleration.y) >= 0)
            {
                acceleration.y -= acceleration.y / 100;
            }
        }
    }
    else if (axes[1] > 0.2)
    {
        if (axes[1] > 0.2 && axes[0] > 0.2)
        {
            if (acceleration.x >= 0 && acceleration.y >= 0)
            {
                acceleration += {min_accel, -max_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (acceleration.x >= 0 && acceleration.y < 0)
            {
                acceleration += {min_accel, -min_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (acceleration.x < 0 && acceleration.y >= 0)
            {
                acceleration += {max_accel, -max_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                acceleration += {max_accel, -min_accel};
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }

        }
        else
        {
            if (abs(acceleration.x) >= 0)
            {
                acceleration.x -= acceleration.x / 100;
            }
            if (acceleration.y >= 0)
            {
                acceleration.y += -max_accel;
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                acceleration.y += -min_accel;
                m_owner->GetTransform().AddTranslation(acceleration);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
        }
    }
    else if (axes[0] > 0.2)
    {
        if (acceleration.x >= 0)
        {
            acceleration.x += min_accel;
            m_owner->GetTransform().AddTranslation(acceleration);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
        else
        {
            acceleration.x += max_accel;
            m_owner->GetTransform().AddTranslation(acceleration);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
        if (abs(acceleration.y) >= 0)
        {
            acceleration.y -= acceleration.y / 100;
        }
    }
    else
    {
        acceleration += {-acceleration.x / 100, -acceleration.y / 100};
        m_owner->GetTransform().AddTranslation(acceleration);
        m_owner->GetMesh().Get_Is_Moved() = true;
    }
}

void Physics::JustMove()
{
    acceleration += {-acceleration.x / 100, -acceleration.y / 100};
    m_owner->GetTransform().AddTranslation(acceleration);
    m_owner->GetMesh().Get_Is_Moved() = true;
}

void Physics::KnockBack(Object* object_1, Object* object_2)
{
    if (object_1->GetComponentByTemplate<Physics>() != nullptr && object_2->GetComponentByTemplate<Physics>() != nullptr)
    {
        vector2 object_1_pos = object_1->GetTransform().GetTranslation();
        vector2 object_2_pos = object_2->GetTransform().GetTranslation();
        vector2 object_1_acceleration = object_1->GetComponentByTemplate<Physics>()->GetAcceleration();
        vector2 object_2_acceleration = object_2->GetComponentByTemplate<Physics>()->GetAcceleration();
        vector2 direction_to_go;

        float object_1_speed = sqrt((object_1_acceleration.x * object_1_acceleration.x) + (object_1_acceleration.y * object_1_acceleration.y));
        float object_2_speed = sqrt((object_2_acceleration.x * object_2_acceleration.x) + (object_2_acceleration.y * object_2_acceleration.y));

        if (object_2_speed >= object_1_speed)
        {
            sound.Play(SOUND::Crack);
            direction_to_go = normalize(object_1_pos - object_2_pos);

            object_1->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go * object_2_speed);
            object_1->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Physics>()->GetAcceleration());
            object_1->GetMesh().Get_Is_Moved() = true;

            object_2->GetComponentByTemplate<Physics>()->SetAcceleration(-direction_to_go * object_2_speed / 2);
            object_2->GetTransform().AddTranslation(object_2->GetComponentByTemplate<Physics>()->GetAcceleration());
            object_2->GetMesh().Get_Is_Moved() = true;
        }
        else if (object_2_speed < object_1_speed)
        {
            sound.Play(SOUND::Crack);

            direction_to_go = normalize(object_2_pos - object_1_pos);

            object_2->GetComponentByTemplate<Physics>()->SetAcceleration(direction_to_go * object_1_speed);
            object_2->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Physics>()->GetAcceleration());
            object_2->GetMesh().Get_Is_Moved() = true;

            object_1->GetComponentByTemplate<Physics>()->SetAcceleration(-direction_to_go * object_1_speed / 2);
            object_1->GetTransform().AddTranslation(object_1->GetComponentByTemplate<Physics>()->GetAcceleration());
            object_1->GetMesh().Get_Is_Moved() = true;
        }
    }
}

void Physics::Dash(Object* object)
{
    vector2 acceleration = object->GetComponentByTemplate<Physics>()->GetAcceleration();
    acceleration = normalize(acceleration);

    int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    int present2 = glfwJoystickPresent(GLFW_JOYSTICK_2);
    int present3 = glfwJoystickPresent(GLFW_JOYSTICK_3);
    int present4 = glfwJoystickPresent(GLFW_JOYSTICK_4);

    if (m_owner->GetName() == "first" && present)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    }
    else if (m_owner->GetName() == "second" && present2)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axesCount);
    }
    else if (m_owner->GetName() == "third" && present3)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_3, &axesCount);
    }
    else if (m_owner->GetName() == "forth" && present4)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_4, &axesCount);
    }
    else
    {
        if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::Dash)
        {
            sound.Play(SOUND::Dash);
            timer = 0;
            acceleration += {50 * acceleration.x, 50 * acceleration.y};
            object->GetComponentByTemplate<Physics>()->SetAcceleration(acceleration);
            object->GetMesh().Get_Is_Moved() = true;
            object->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
            Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, "dash", 1.f));

            object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->DeleteComponent(
                object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>());

            is_dashed = true;
        }
        if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::HP)
        {
            sound.Play(SOUND::HP);

            object->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);

            object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->DeleteComponent(
                object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>());

            Object* hp_bar = object->Get_Belong_Object_By_Tag("hp_bar");

            if (hp_bar->GetComponentByTemplate<Hp_Bar>() != nullptr)
            {
                hp_bar->GetTransform().GetTranslation_Reference().x = 0.f;
                hp_bar->GetComponentByTemplate<Hp_Bar>()->Get_Set_Offset() = 0.f;
            }

            hp_bar->GetMesh().Get_Is_Moved() = true;
            Message_Manager::Get_Message_Manager()->Save_Message(new Message(hp_bar, nullptr, "recover", 1.f));
        }

        if (input.Is_Key_Pressed(GLFW_KEY_SPACE) && object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::Bulkup)
        {
            sound.Play(SOUND::BulkUp);

            object->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);

            object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->DeleteComponent(
                object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>());

            Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, "bulkup", 3.f));
        }
        return;
    }
    if (axes[5] > 0.4)
    {
        if (object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::Dash)
        {
            sound.Play(SOUND::Dash);

            timer = 0;
            acceleration += {50 * acceleration.x, 50 * acceleration.y};
            object->GetComponentByTemplate<Physics>()->SetAcceleration(acceleration);
            object->GetMesh().Get_Is_Moved() = true;
            object->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
            Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, "dash", 1.f));

            object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->DeleteComponent(
                object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>());

            is_dashed = true;
        }
        if (object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::HP)
        {
            sound.Play(SOUND::HP);

            object->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);
            object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Hp_Info()->GetTransform().GetScale_Reference().x = 4.f;

            Object* hp_bar = object->Get_Belong_Object_By_Tag("hp_bar");
            float offset = 1.f - hp_bar->GetTransform().GetScale_Reference().x;


            object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->DeleteComponent(
                object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>());

            if (hp_bar->GetComponentByTemplate<Hp_Bar>() != nullptr)
            {
                hp_bar->GetTransform().GetTranslation_Reference().x = 0.f;
                hp_bar->GetComponentByTemplate<Hp_Bar>()->Get_Set_Offset() = 0.f;
            }
            hp_bar->GetMesh().Get_Is_Moved() = true;
            Message_Manager::Get_Message_Manager()->Save_Message(new Message(hp_bar, nullptr, "recover", 1.f));
        }

        if (object->GetComponentByTemplate<Player>()->Get_Item_State() == Item::Item_Kind::Bulkup)
        {
            sound.Play(SOUND::BulkUp);
            object->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::None);

            object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->DeleteComponent(
                object->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>());

            Message_Manager::Get_Message_Manager()->Save_Message(new Message(object, nullptr, "bulkup", 3.f));
        }
    }
}

void Physics::BasicMovement()
{
    int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    int present2 = glfwJoystickPresent(GLFW_JOYSTICK_2);
    int present3 = glfwJoystickPresent(GLFW_JOYSTICK_3);
    int present4 = glfwJoystickPresent(GLFW_JOYSTICK_4);

    if (m_owner->GetName() == "first" && present)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    }
    else if (m_owner->GetName() == "second" && present2)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axesCount);
    }
    else if (m_owner->GetName() == "third" && present3)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_3, &axesCount);
    }
    else if (m_owner->GetName() == "forth" && present4)
    {
        int axesCount;
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_4, &axesCount);
    }
    else
    {
        if (input.Is_Key_Pressed(GLFW_KEY_W))
        {
            if (input.Is_Key_Pressed(GLFW_KEY_W) && input.Is_Key_Pressed(GLFW_KEY_A))
            {
                velocity = { -1, 1 };
                m_owner->GetTransform().AddTranslation(velocity);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else if (input.Is_Key_Pressed(GLFW_KEY_W) && input.Is_Key_Pressed(GLFW_KEY_D))
            {
                velocity = { 1, 1 };
                m_owner->GetTransform().AddTranslation(velocity);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                velocity = { 0, 1 };
                m_owner->GetTransform().AddTranslation(velocity);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
        }
        else if (input.Is_Key_Pressed(GLFW_KEY_A))
        {
            if (input.Is_Key_Pressed(GLFW_KEY_A) && input.Is_Key_Pressed(GLFW_KEY_S))
            {
                velocity = { -1, -1 };
                m_owner->GetTransform().AddTranslation(velocity);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                velocity = { 1, 0 };
                velocity = { -1, 0 };
                m_owner->GetTransform().AddTranslation(velocity);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
        }
        else if (input.Is_Key_Pressed(GLFW_KEY_S))
        {
            if (input.Is_Key_Pressed(GLFW_KEY_S) && input.Is_Key_Pressed(GLFW_KEY_D))
            {
                velocity = { 1, -1 };
                m_owner->GetTransform().AddTranslation(velocity);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
            else
            {
                velocity = { 0, -1 };
                m_owner->GetTransform().AddTranslation(velocity);
                m_owner->GetMesh().Get_Is_Moved() = true;
            }
        }
        else if (input.Is_Key_Pressed(GLFW_KEY_D))
        {
            velocity = { 1, 0 };
            m_owner->GetTransform().AddTranslation(velocity);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
        return;
    }
    if (axes[1] < -0.2)
    {
        if (axes[1] < -0.2 && axes[0] < -0.2)
        {
            velocity = { -1, 1 };
            m_owner->GetTransform().AddTranslation(velocity);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
        else if (axes[1] < -0.2 && axes[0] > 0.2)
        {
            velocity = { 1, 1 };
            m_owner->GetTransform().AddTranslation(velocity);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
        else
        {
            velocity = { 0, 1 };
            m_owner->GetTransform().AddTranslation(velocity);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
    }
    else if (axes[0] < -0.2)
    {
        if (axes[0] < -0.2 && axes[1] > 0.2)
        {
            velocity = { -1, -1 };
            m_owner->GetTransform().AddTranslation(velocity);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
        else
        {
            velocity = { 1, 0 };
            velocity = { -1, 0 };
            m_owner->GetTransform().AddTranslation(velocity);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
    }
    else if (axes[1] > 0.2)
    {
        if (axes[1] > 0.2 && axes[0] > 0.2)
        {
            velocity = { 1, -1 };
            m_owner->GetTransform().AddTranslation(velocity);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
        else
        {
            velocity = { 0, -1 };
            m_owner->GetTransform().AddTranslation(velocity);
            m_owner->GetMesh().Get_Is_Moved() = true;
        }
    }
    else if (axes[0] > 0)
    {
        velocity = { 1, 0 };
        m_owner->GetTransform().AddTranslation(velocity);
        m_owner->GetMesh().Get_Is_Moved() = true;
    }
}

void Physics::SpeedDown(Object* object)
{
    vector2 acceleration = object->GetComponentByTemplate<Physics>()->GetAcceleration();

    acceleration /= 5;

    object->GetComponentByTemplate<Physics>()->SetAcceleration(acceleration);
    object->GetMesh().Get_Is_Moved() = true;
}

void Physics::Update(float dt)
{
    timer += dt;

    if (m_owner->GetName() == "first")
    {
        Acceleration(0.6, 0.12);

        if (is_dashed == false && timer >= 0.3)
        {
            Dash(m_owner);
        }
        else if (is_dashed == true && timer >= 0.5)
        {
            SpeedDown(m_owner);
            is_dashed = false;
        }
    }
    else if (m_owner->GetName() == "second")
    {
        Acceleration(0.6, 0.12);

        if (is_dashed == false && timer >= 0.3)
        {
            Dash(m_owner);
        }
        else if (is_dashed == true && timer >= 0.5)
        {
            SpeedDown(m_owner);
            is_dashed = false;
        }
    }
    else if (m_owner->GetName() == "third")
    {
        Acceleration(0.6, 0.12);

        if (is_dashed == false && timer >= 0.3)
        {
            Dash(m_owner);
        }
        else if (is_dashed == true && timer >= 0.5)
        {
            SpeedDown(m_owner);
            is_dashed = false;
        }
    }
    else if (m_owner->GetName() == "forth")
    {
        Acceleration(0.6, 0.12);

        if (is_dashed == false && timer >= 0.3)
        {
            Dash(m_owner);
        }
        else if (is_dashed == true && timer >= 0.5)
        {
            SpeedDown(m_owner);
            is_dashed = false;
        }
    }
    else
    {
        JustMove();
    }

    if (ghost_collision_mode)
    {
        ghost_collision_timer -= dt;

        if (ghost_collision_timer <= 0.0f)
        {
            ghost_collision_mode = false;
            if (m_owner->GetComponentByTemplate<Sprite>() != nullptr)
            {
                m_owner->GetComponentByTemplate<Sprite>()->Get_Material().color4fUniforms["color"] = { 1.0f,1.0f,1.0f,1.0f };
            }
            ghost_collision_timer = 1.0f;
        }
    }
}