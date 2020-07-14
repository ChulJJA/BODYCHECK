/*
 * Author		:Jeesoo Kim
 * File			:Component_Sprite.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Component Sprite
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */


#pragma once
#include "Component.hpp"
#include "Shader.hpp"
#include "Vertices.hpp"
#include "Material.hpp"
#include "Image.hpp"
#include "Texture.hpp"

enum class Sprite_Type
{
    None,
    Player_Normal,
    Player_Speed2,
    Player_Speed3,
    Player_Locking,
    Player_Chasing,
    Player_Thinking,
    Player_Reverse_Moving,
    Player_Ready,
    Player_Effect_Bulkp,
    Player_Effect_Heal,
    Player_Effect_Throwing,
    Player_Effect_Missile,
    Player_Effect_Dash,
    Player_Effect_Timestop,
    Player_Effect_Reverse,
	Player_Bulkup_Used,
	Player_Crying,
	Player_Die,
    Player_Aiming,
	Player_Paused,
    Player_Fat,
	Player_Spawn,
    Player_Dance,
	
	
	Item,
    Item_Spawn_Effect,
	Item_Eateffect,
	Item_Dash,
	Item_Bulkup,
	Item_Heal,
	Item_Throw,
	Item_Magnet,
	Item_Timepause,
	Item_Reverse,
	Item_Missile,
    Item_Mine,
    Item_Click,

	Missile_Launcher_Showing,
    Dash_Showing,
    Bulkup_Showing,
	Throwing_Showing,
	Heal_Showing,
	Magnet_Showing,
	Timestop_Showing,
	Reverse_Showing,

	Audience_Normal,
    Audience_Cheerup,
    Audience_Joy,
    Audience_Sad,
	Audience_Red_Good,
    Audience_Blue_Good,
    Audience_Normal_Good,
    Audience_Green_Good,

    Num_0,
	Num_1,
	Num_2,
    Num_3,
    Num_4,
    Num_5,
    Item_Space,
    Item_Num,

    Player_Selected,
    Button,
    Button_Hover,
    R_U_SURE_YES,
    R_U_SURE_NO,

    Loading,
    Loading_Press,
	CreditGround,

    Credit_First,
    Credit_Second,
    Credit_Third,
	Credit_Fourth,
	Credit_Fifth,
	Credit_Sixth,

    Explanation_Staff_Normal,
    Explanation_Staff_Booster,
    Explanation_Staff_Gun,
    Explanation_Staff_TP,
    Explanation_Staff_Tornado,
    Explanation_Staff_Heal,
    Explanation_Staff_Bulkup,
    Explanation_Staff_Reverse,
    Explanation_Staff_Missile,
};


class Sprite : public Component
{
public:

	
    Sprite(Object* obj, bool need_debug_drawing = false);
    Sprite(Object* obj, const char* staticSpritePath, vector2 position, bool need_debug_drnawing = true, Sprite_Type type_player = Sprite_Type::None, vector2 scale = {100.f, 100.f});
    Sprite(Object* obj, const char* aniamtedSpritePath, bool animated, int frames, float m_speed, vector2 position, vector2 scale, Color4ub color = { 255,255,255,255 },
		Sprite_Type type_player = Sprite_Type::None, bool need_debug_info = false);
    void Init(Object* obj) override;
    void Update(float dt) override;
	void Update_Instancing(float dt);
    bool Can_Load_To_Texture(Texture& texture, const char* file_path);

	void Set_Player_Sprite_Type(Sprite_Type type_player);
	Sprite_Type Get_Sprite_Type();
	
    material& Get_Material()
    {
        return material;
    }
    Vertices& Get_Shape()
    {
        return shape;
    }
    int& Get_Speed()
    {
        return speed;
    }
    int Get_Original_Speed()
    {
        return original_speed;
    }
private:

    Shader debug_shader;
    Vertices debug_shape;
    material debug_material;

    Shader shader;
    Vertices shape;
    material material;
    Texture texture;
    Image image;

    float seconds = 0;
    int width = 1280, height = 720;

    bool is_animated = false;
    int frame = 0;
    int speed = 100;
    int original_speed;
    float spriteWidth = 0;
    bool animated_init = true;
	Sprite_Type sprite_type;
    bool is_debug_mode = false;

};