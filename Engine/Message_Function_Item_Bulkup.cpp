/*
 * Author       :Sangmin Kim
 * File         :Message_Function_Item_BulkUp.cpp
 * Term         :2020 Spring
 * Class        :GAM250
 * Project      :GAM250 Project
 * Date         :2020/07/09
 * Description  :Source file for Message Function Item Bulk Up
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Message_Function_Item_Bulkup.h"
#include "Component_Player.h"
#include "Object.h"
#include "Message.h"
#include "Component_Ui.h"
#include "Player_Ui.h"
#include "Component_Sprite.h"
#include "Engine.hpp"

void Msg_Func_Item_Bulkup::Init()
{
    if (msg->Get_Target() != nullptr)
    {
        isPlayed = false;
        Object* obj = msg->Get_Target();
        Player* info_player = obj->GetComponentByTemplate<Player>();
        PLAYER_UI* info_ui = info_player->Get_Ui();

        if (info_player != nullptr && info_ui != nullptr)
        {
            info_player->Set_Item_State(Item::Item_Kind::None);

            if (info_player->Get_Char_State() == Player::Char_State::None)
            {
                //time for prepare
                info_player->Set_Prepare_Timer(3.f);
                info_player->Set_Char_State(Player::Char_State::Prepare);

                //bulkup item setting.
                info_player->Set_Bulkup_Timer(5.f);
                info_player->Sprite_After_Preparation(obj->Find_Sprite_By_Type(Sprite_Type::Player_Bulkup_Used));

                obj->Change_Sprite(obj->Find_Sprite_By_Type(Sprite_Type::Player_Effect_Bulkp));
            }

            info_ui->Change_Ui_Info(Ui::Ui_Status_Base::Item, Ui::Ui_Status_Verb::Use, Ui::Ui_Status_Obj::Item_Bulkup);
        }
    }
}

void Msg_Func_Item_Bulkup::Update(float dt)
{
    Player* info_player = m_target->GetComponentByTemplate<Player>();

    if (info_player != nullptr)
    {
        if (info_player->Get_Char_State() == Player::Char_State::Prepared ||
            info_player->Get_Item_Used_Status() == Player::Item_Use_Status::Bulkup)
        {
            info_player->Set_Item_Used_Status(Player::Item_Use_Status::Bulkup);

            if (timer > 0.f)
            {
                if (!is_ready_end)
                {
                    if (bulkup_ready_timer > 0.f)
                    {
                        if (bulkup_ready_offset > 0.f)
                        {
                            if (ready_big_mode)
                            {
                                m_target->GetTransform().GetScale_Reference().x = big_rate;
                                m_target->GetTransform().GetScale_Reference().y = big_rate;

                            }
                            else
                            {
                                m_target->GetTransform().GetScale_Reference().x = 2.f;
                                m_target->GetTransform().GetScale_Reference().y = 2.f;
                            }
                            bulkup_ready_offset -= dt;
                        }
                        else
                        {
                            ready_big_mode = !ready_big_mode;
                            bulkup_ready_offset = 0.1f;
                            big_rate += 0.5f;

                        }
                        bulkup_ready_timer -= dt;
                    }
                    else
                    {
                        is_ready_end = true;
                    }
                }
                else
                {
                    m_target->Get_Plus_Dmg() = 2.f;
                    m_target->GetTransform().GetScale_Reference().x = 5.f;
                    m_target->GetTransform().GetScale_Reference().y = 5.f;
                }

                timer -= dt;
            }
            else
            {
                if (!isPlayed)
                {
                    sound.Play(SOUND::EndBulkUp);
                    isPlayed = true;
                }
                if (!is_end)
                {
                    if (bulkup_end_timer > 0.f)
                    {
                        if (bulkup_end_offset > 0.f)
                        {
                            if (end_big_mode)
                            {
                                m_target->GetTransform().GetScale_Reference().x = big_rate;
                                m_target->GetTransform().GetScale_Reference().y = big_rate;

                            }
                            else
                            {
                                m_target->GetTransform().GetScale_Reference().x = 2.f;
                                m_target->GetTransform().GetScale_Reference().y = 2.f;
                            }
                            bulkup_end_offset -= dt;
                        }
                        else
                        {
                            end_big_mode = !end_big_mode;
                            bulkup_end_offset = 0.1f;
                            big_rate -= 0.1f;

                        }
                        bulkup_end_timer -= dt;
                    }
                    else
                    {
                        m_target->GetTransform().GetScale_Reference().x = 2.f;
                        m_target->GetTransform().GetScale_Reference().y = 2.f;
                        m_target->Get_Plus_Dmg() = 0.f;
                        info_player->Set_Char_State(Player::Char_State::None);
                        info_player->Change_To_Normal_State();
                        info_player->Set_Item_Used_Status(Player::Item_Use_Status::None);
                        msg->Set_Should_Delete(true);
                    }
                }
            }
        }
        else if (info_player->Get_Char_State() == Player::Char_State::None)
        {
            info_player->Change_To_Normal_State();
            msg->Set_Should_Delete(true);
        }
    }
}