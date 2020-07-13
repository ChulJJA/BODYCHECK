/*
 * Author		:Jeesoo Kim
 * File			:View.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for View
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "View.h"
#include "Input.h"
#include "Graphic.h"
#include "Application.hpp"
#include "Referee.h"

void View::Init()
{
	camera_view.SetViewSize(1280, 720);
	vector2 save_window_size = Application::Get_Application()->Get_Window_Size();
	ndc_matrix = MATRIX3::build_scale(save_window_size.x / 2, save_window_size.y / 2);
}

void View::Update(float dt)
{
	/*if (input.Mouse_Wheel_Scroll() < 0)
	{
		camera_view.AddZoom(-0.05f);
		input.Set_Mouse_Wheel(0.0, 0.0);
		Graphic::GetGraphic()->get_need_update_sprite() = true;
	}
	else if (input.Mouse_Wheel_Scroll() > 0)
	{
		camera_view.AddZoom(0.05f);
		input.Set_Mouse_Wheel(0.0, 0.0);
		Graphic::GetGraphic()->get_need_update_sprite() = true;
	}*/

	if (status != Shake_Status::None)
	{
		Screen_Shake();
	}

	//win_player = Referee::Get_Referee()->Get_Win_Player();
	if (is_ended == true)
	{
		if (input.Is_Key_Triggered(GLFW_KEY_ESCAPE))
		{
			is_zoom_end = true;
		}
		Win_Zoom(dt);
	}

	if (Referee::Get_Referee()->Get_Is_CheerUp_Mode())
	{
		Active_Screen_Shake(5.f, 1);
	}
}

bool myfunction(int i, int j)
{
	return (i < j);
}

void View::Convert_Cam_Zoom()
{
	std::vector<Object*> player_vec = ObjectManager::GetObjectManager()->Find_Objects_By_Tag("player");

	float zoom = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetZoom();
	const int player_vec_size = static_cast<int>(player_vec.size());

	for (int i = 0; i < player_vec_size; i++)
	{
		player_pos.push_back(player_vec[i]->GetTransform().GetTranslation());
		x_sorted.push_back(player_vec[i]->GetTransform().GetTranslation().x);
		y_sorted.push_back(player_vec[i]->GetTransform().GetTranslation().y);
	}

	std::sort(std::begin(x_sorted), std::end(x_sorted), myfunction);
	std::sort(std::begin(y_sorted), std::end(y_sorted), myfunction);

	vector2 smallest = { x_sorted.front(), y_sorted.front() };
	vector2 largest = { x_sorted.back(), y_sorted.back() };
	vector2 prev_distance = distance;

	if (largest.x >= 0 && smallest.x >= 0)
	{
		distance.x = (largest.x - smallest.x);
		center.x = largest.x - (distance.x / 2);
	}
	else if (largest.x >= 0 && smallest.x < 0)
	{
		distance.x = (abs(largest.x) + abs(smallest.x));
		center.x = largest.x - (distance.x / 2);
	}
	else
	{
		distance.x = (abs(smallest.x) - abs(largest.x));
		center.x = largest.x - (distance.x / 2);
	}

	if (largest.y >= 0 && smallest.y >= 0)
	{
		distance.y = (largest.y - smallest.y);
		center.y = largest.y - (distance.y / 2);
	}
	else if (largest.y >= 0 && smallest.y < 0)
	{
		distance.y = (abs(largest.y) + abs(smallest.y));
		center.y = largest.y - (distance.y / 2);
	}
	else
	{
		distance.y = (abs(smallest.y) - abs(largest.y));
		center.y = largest.y - (distance.y / 2);
	}

	if (zoom > 0.8)
	{
		zoom = 0.795f;
	}
	if (zoom < -0.2)
	{
		zoom = -0.15f;
	}

	if (zoom >= -0.2 && zoom <= 0.8 && (distance != prev_distance) && player_pos.size() != 1)
	{
		if (prev_distance.x < distance.x || prev_distance.y < distance.y)
		{
			camera_view.AddZoom(-0.002f);
		}
		if (prev_distance.x > distance.x || prev_distance.y > distance.y)
		{
			camera_view.AddZoom(0.002f);
		}
		if (prev_distance == distance)
		{
		}
	}
	if (player_pos.size() == 1)
	{
		camera.SetCenter({ player_pos.front().x,  player_pos.front().y });
	}
	player_pos.clear();
	x_sorted.clear();
	y_sorted.clear();
}

void View::Screen_Shake()
{
	vector2& cam_pos = camera.GetCenter();

	switch (status)
	{
	case Shake_Status::To_Left:
		cam_pos.x -= force;
		status = Shake_Status::To_Right;
		break;
	case Shake_Status::To_Right:
		cam_pos.x += force;
		status = Shake_Status::To_Up;
		break;
	case Shake_Status::To_Up:
		cam_pos.y -= force;
		status = Shake_Status::To_Down;
		break;
	case Shake_Status::To_Down:
		cam_pos.y += force;
		status = Shake_Status::Done;
		break;
	case Shake_Status::Done:
		cam_pos.x = 0.f;
		cam_pos.y = 0.f;

		if (shake_num < 0)
		{
			status = Shake_Status::None;
		}
		else
		{
			shake_num--;
			status = Shake_Status::To_Left;
		}
		break;
	default:;
	}

}

void View::Win_Zoom(float dt)
{
	win_player = Referee::Get_Referee()->Get_Win_Player();

	if (win_player != nullptr)
	{
		if (!is_zoom_end)
		{
			camera.SetCenter(win_player->GetTransform().GetTranslation());

			camera_view.SetZoom(setting_zoom);

			if (setting_zoom < 0.7f)
			{
				setting_zoom += 0.01f;
			}
		}
		else
		{
			Graphic::GetGraphic()->Get_View().Get_Camera().SetCenter(vector2{ 0.f, 0.f });
			Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
		}
	}
	else
	{

	}
}

void View::Active_Screen_Shake(float force, int how_many)
{
	if (status == Shake_Status::None)
	{
		this->force = force;
		status = Shake_Status::To_Left;
		shake_num = how_many;
	}
}
