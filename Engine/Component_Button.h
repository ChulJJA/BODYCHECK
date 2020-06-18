#pragma once
#include "Component.hpp"

class Object;

class Component_Button : public Component
{
public:
    void Init(Object* obj) override;
    void Update(float dt) override;
    void Collided(Object* obj);
    void Collided_Off(Object* obj);

    void Increment_Max_Player_Num()
    {
        max_player_num++;
    }
    void Decrement_Max_Player_Num()
    {
        max_player_num--;
    }
    bool Selected()
    {
        if (curr_num > 1)
        {
            return max_player_num == curr_num;
        }
        return false;
    }

    int Get_Max_Player_Num()
    {
        return max_player_num;
    }
    int Get_Curr_Player_Num()
    {
        return curr_num;
    }

private:
    Object* player_1 = nullptr;
    Object* player_2 = nullptr;
    Object* player_3 = nullptr;
    Object* player_4 = nullptr;

    int max_player_num = 0;
    int curr_num = 0;
};