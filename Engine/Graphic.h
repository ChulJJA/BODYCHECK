/*
 * Author		:Jeesoo Kim
 * File			:Graphic.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Graphic
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

#include "Vertices.hpp"
#include "Material.hpp"
#include "View.h"
class Graphic
{
public:
    static Graphic* GetGraphic();

    void Init();
    void Update(float dt);
    void Delete();
    void Draw(Vertices& shape, material material);
	void Instancing_Draw(Vertices& shape, material material);
	
	void Render();
    View& Get_View()
    {
        return view;
    }
    bool& get_need_update_sprite()
    {
        return need_update_sprite;
    }
	void Instance_Num_Reset()
    {
		instance_num_count = 0;
    }
	void Instance_Num_Incre()
    {
		instance_num_count++;
    }
	int Instance_Num_Get()
    {
		return instance_num_count;
    }
	
private:
    static Graphic* graphic;
    View view;
    int width = 1280, height = 720;
    float seconds = 0;
    bool need_update_sprite = false;
	int instance_num_count = 0;
};