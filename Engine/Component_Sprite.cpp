/*
 * Author		:Jeesoo Kim
 * File			:Component_Sprite.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Component Sprite
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Component_Sprite.h"
#include "angles.hpp"
#include "Mesh.hpp"
#include "StockShaders.hpp"
#include "Graphic.h"
#include "Object.h"
#include "Component_Hpbar.h"
#include "Physics.h"

namespace
{
	Graphic* graphic = Graphic::GetGraphic();
	View& view = graphic->Get_View();
	CameraView& camera_view = view.Get_Camera_View();
	Camera& camera = view.Get_Camera();
}

void Helper_Addpoint_Circle(std::size_t& point_count, Mesh& mesh, float& radius, float position_x = 0, float position_y = 0, bool move_up_down = true)
{
	float theta;
	float location_x;
	float location_y;
	for (int i = 1; i <= point_count + 1; i++)
	{
		theta = (TWO_PI * i) / static_cast<float>(point_count);
		location_x = (radius * cosf(theta)) - position_x;
		location_y = (radius * sinf(theta)) - position_y;
		mesh.AddPoint({ location_x,location_y });
		if (move_up_down)
		{
			mesh.AddTextureCoordinate({ to_radians(270.f), 10.f });
		}
		else if (!move_up_down)
		{
			mesh.AddTextureCoordinate({ to_radians(180.f), 10.f });
		}
	}
}

void Helper_Addpoint_Ellipse(std::size_t& point_count, Mesh& mesh, float& radius, float position_x = 0, float position_y = 0)
{
	float theta;
	float location_y;
	float location_x;
	for (int i = 1; i <= point_count + 1; i++)
	{
		theta = (TWO_PI * i) / static_cast<float>(point_count);
		location_x = (radius * cosf(theta)) - position_x;
		location_y = (radius * sinf(theta) / 2) - position_y;
		mesh.AddPoint({ location_x ,location_y });
		mesh.AddTextureCoordinate({ to_radians(270.f), 10.f });
	}
}

Mesh m_create_circle(float radius, Color4ub color, std::size_t point_count, vector2 origin = { 0.1f, 0.1f }, bool is_ellipse = false, float location_x = 0, float location_y = 0, bool move_up_down = true) noexcept
{
	Mesh temp_mesh;
	(origin);
	temp_mesh.AddColor(color);
	temp_mesh.SetPointListType(PointListPattern::TriangleFan);
	if (!is_ellipse)
	{
		Helper_Addpoint_Circle(point_count, temp_mesh, radius, location_x, location_y, move_up_down);
	}
	else if (is_ellipse)
	{
		Helper_Addpoint_Ellipse(point_count, temp_mesh, radius, location_x, location_y);
	}

	return temp_mesh;
}

Mesh m_create_wire_circle(float radius, Color4ub color, std::size_t point_count) noexcept
{
	Mesh temp_mesh;
	temp_mesh.SetPointListType(PointListPattern::LineLoop);
	temp_mesh.AddColor(color);
	Helper_Addpoint_Circle(point_count, temp_mesh, radius);

	return temp_mesh;
}

bool Sprite::Can_Load_To_Texture(Texture& texture, const char* file_path)
{
	const bool is_okay = texture.LoadFromPNG(file_path);
	if (!is_okay)
	{
	}
	return is_okay;
}

void Sprite::Set_Player_Sprite_Type(Sprite_Type type_player)
{
	sprite_type = type_player;
}

Sprite_Type Sprite::Get_Sprite_Type()
{
	return sprite_type;
}

void Sprite::Init(Object* obj)
{
	m_owner = obj;
	m_owner->Get_Component_Info_Reference().component_info_sprite = true;
	m_owner->Add_Sprite_List(this);
	debug_material.shader = &(SHADER::solid_color());
	m_owner->Set_Center({ m_owner->GetTransform().GetTranslation().x , m_owner->GetTransform().GetTranslation().y });

}

Sprite::Sprite(Object* obj, bool need_debug_drawing)
{
	m_owner = obj;

	material.shader = &(SHADER::solid_color());
	material.color4fUniforms["color"] = { 1.0f };
	material.matrix3Uniforms["to_ndc"] = MATRIX3::build_scale(2.0f / width, 2.0f / height);

	Mesh square;
	square = MESH::create_wire_box(2000, { 100,100,100,100 });
	shape.InitializeWithMeshAndLayout(square, SHADER::solid_color_vertex_layout());

	m_owner->SetMesh(square);
	m_owner->Get_Object_Points() = m_owner->GetMesh().Get_Points();
}

Sprite::Sprite(Object* obj, const char* staticSpritePath, vector2 position, bool need_debug_drawing, Sprite_Type type_player, vector2 scale)
{
	m_owner = obj;

	const auto path = staticSpritePath;

	material.shader = &(SHADER::textured());

	if (!Can_Load_To_Texture(texture, path))
	{
	}
	texture.SelectTextureForSlot(texture);
	material.textureUniforms["texture_to_sample"] = { &(texture) };

	material.color4fUniforms["color"] = { 1.0f };



	Mesh square = MESH::create_box(scale.x, { 100,100,100,255 });
	shape.InitializeWithMeshAndLayout(square, SHADER::textured_vertex_layout());

	m_owner->SetMesh(square);
	m_owner->Get_Object_Points() = m_owner->GetMesh().Get_Points();
	m_owner->SetTranslation(position);
	m_owner->Set_Center({ position.x , position.y });

	if (need_debug_drawing)
	{
		Mesh debug_mesh;
		debug_mesh = MESH::create_wire_circle(30, { 255,0,0,255 });
		debug_shape.InitializeWithMeshAndLayout(debug_mesh, SHADER::solid_color_vertex_layout());

		m_owner->Set_Debug_Mesh(debug_mesh);
	}

	sprite_type = type_player;
}

Sprite::Sprite(Object* obj, const char* aniamtedSpritePath, bool animated, int frames, float m_speed, vector2 position, vector2 scale, Color4ub color, Sprite_Type type_player, bool need_debug_info)
{
	m_owner = obj;
	is_animated = animated;
	frame = frames;
	const auto path = aniamtedSpritePath;
	material.shader = &(SHADER::textured());
	if (!Can_Load_To_Texture(texture, path))
	{
	}
	texture.SelectTextureForSlot(texture);
	material.textureUniforms["texture_to_sample"] = { &(texture) };
	material.color4fUniforms["color"] = to_color4f(color);

	Mesh square;
	square = MESH::create_box(scale.x, { 100,100,100,255 });
	shape.InitializeWithMeshAndLayout(square, SHADER::textured_vertex_layout());

	m_owner->SetMesh(square);

	m_owner->GetMesh().ClearTextureCoordinates();
	m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 1 });
	m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 0 });
	spriteWidth += float(1.0 / frame);
	m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 0 });
	m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 1 });

	m_owner->Get_Object_Points() = m_owner->GetMesh().Get_Points();
	m_owner->SetTranslation(position);
	m_owner->Set_Center({ position.x , position.y });
	speed = m_speed;
	original_speed = m_speed;
	matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
	mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
	mat_ndc *= m_owner->GetTransform().GetModelToWorld();

	material.matrix3Uniforms["to_ndc"] = mat_ndc;
	shape.InitializeWithMeshAndLayout(m_owner->GetMesh(), SHADER::textured_vertex_layout());
	material.floatUniforms["time"] = 1;

	if (need_debug_info)
	{
		Mesh debug_mesh;
		debug_mesh = MESH::create_wire_circle(40, { 255,0,0,255 });
		debug_shape.InitializeWithMeshAndLayout(debug_mesh, SHADER::solid_color_vertex_layout());

		m_owner->Set_Debug_Mesh(debug_mesh);
		is_debug_mode = need_debug_info;

		debug_material.shader = &(SHADER::solid_color());
		debug_material.color4fUniforms["color"] = to_color4f(Color4ub(0,0,0,255));

	}

	sprite_type = type_player;
}


void draw(Vertices shape, material material)
{
	Graphic::GetGraphic()->Draw(shape, material);
}

void Sprite::Update(float dt)
{
	seconds += dt;
	uint32_t ticks = seconds + 1;

	matrix3 model_to_world = m_owner->GetTransform().GetModelToWorld();
	//shape.UpdateVerticesFromMesh(m_owner->GetMesh());

	material.floatUniforms["time"] -= dt * speed;
	//animation

	Mesh& mesh = m_owner->GetMesh();

	if (is_animated && material.floatUniforms["time"] <= 0)
	{
		mesh.ClearTextureCoordinates();
		if (spriteWidth <= 1)
		{
			mesh.AddTextureCoordinate({ spriteWidth , 1 });
			mesh.AddTextureCoordinate({ spriteWidth , 0 });
			spriteWidth += float(1.0 / frame);
		}
		else
		{
			spriteWidth = 0;
			mesh.AddTextureCoordinate({ spriteWidth , 1 });
			mesh.AddTextureCoordinate({ spriteWidth , 0 });
			spriteWidth += float(1.0 / frame);
		}

		mesh.AddTextureCoordinate({ spriteWidth , 0 });
		mesh.AddTextureCoordinate({ spriteWidth , 1 });

		m_owner->SetMesh(mesh);
		shape.UpdateVerticesFromMesh(mesh);

		//matrix3 mat_ndc = camera_view.GetCameraToNDCTransform();
		//mat_ndc *= camera.WorldToCamera();
		//mat_ndc *= model_to_world;

		m_owner->GetMesh().Get_Is_Moved() = false;
		material.floatUniforms["time"] = 1;


		material.matrix3Uniforms["to_ndc"] = camera_view.GetCameraToNDCTransform();
		material.matrix3Uniforms["cam"] = camera.WorldToCamera();
		material.matrix3Uniforms["model"] = m_owner->GetTransform().GetModelToWorld();

		if (is_debug_mode)
		{
			matrix3 ndc = camera_view.GetCameraToNDCTransform() * camera.WorldToCamera() * m_owner->GetTransform().GetModelToWorld();
			debug_material.matrix3Uniforms["to_ndc"] = ndc;
			Graphic::GetGraphic()->Draw(debug_shape, debug_material);
		}

		Graphic::GetGraphic()->Draw(shape, material);

	}


	//static

	else if (m_owner->GetMesh().Get_Is_Moved() || Graphic::GetGraphic()->get_need_update_sprite() || m_owner->Get_Tag() == "arena")
	{
		//matrix3 mat_ndc = camera_view.GetCameraToNDCTransform();
		//mat_ndc *= camera.WorldToCamera();
		//mat_ndc *= model_to_world;

		Physics* physics = m_owner->GetComponentByTemplate<Physics>();

		if (physics != nullptr)
		{
			if (physics->GetGhostReference())
			{
				material.color4fUniforms["color"] = { 0.5f,0.5f,0.5f,0.5f };
			}
			else
			{
				material.color4fUniforms["color"] = { 1.0f,1.0f,1.0f,1.0f };
			}
		}
		mesh.Get_Is_Moved() = false;
		//material.matrix3Uniforms["to_ndc"] = mat_ndc;

		material.matrix3Uniforms["to_ndc"] = camera_view.GetCameraToNDCTransform();
		material.matrix3Uniforms["cam"] = camera.WorldToCamera();
		material.matrix3Uniforms["model"] = m_owner->GetTransform().GetModelToWorld();

		Graphic::GetGraphic()->Draw(shape, material);

		if (is_debug_mode)
		{
			matrix3 ndc = camera_view.GetCameraToNDCTransform() * camera.WorldToCamera() * m_owner->GetTransform().GetModelToWorld();
			debug_material.matrix3Uniforms["to_ndc"] = ndc;
			Graphic::GetGraphic()->Draw(debug_shape, debug_material);
		}
	}

}

void Sprite::Update_Instancing(float dt)
{

	seconds += dt;
	uint32_t ticks = seconds + 1;
	std::string instance_ndc = "to_ndc";
	instance_ndc += "[";
	instance_ndc += std::to_string(Graphic::GetGraphic()->Instance_Num_Get());
	instance_ndc += "]";
	material.floatUniforms["time"] -= dt * speed;

	if (is_animated && material.floatUniforms["time"] <= 0)
	{
		m_owner->GetMesh().ClearTextureCoordinates();
		if (spriteWidth <= 1)
		{
			m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 1 });
			m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 0 });
			spriteWidth += float(1.0 / frame);
		}
		else
		{
			spriteWidth = 0;
			m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 1 });
			m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 0 });
			spriteWidth += float(1.0 / frame);
		}

		m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 0 });
		m_owner->GetMesh().AddTextureCoordinate({ spriteWidth , 1 });
		m_owner->SetMesh(m_owner->GetMesh());
		shape.UpdateVerticesFromMesh(m_owner->GetMesh());

		matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
		mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
		mat_ndc *= m_owner->GetTransform().GetModelToWorld();

		m_owner->GetMesh().Get_Is_Moved() = false;
		material.floatUniforms["time"] = 1;
	}

	if (m_owner->GetMesh().Get_Is_Moved() || Graphic::GetGraphic()->get_need_update_sprite() || m_owner->Get_Tag() == "arena")
	{
		matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
		mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
		mat_ndc *= m_owner->GetTransform().GetModelToWorld();

		if (m_owner->GetComponentByTemplate<Physics>() != nullptr)
		{
			if (m_owner->GetComponentByTemplate<Physics>()->GetGhostReference())
			{
				material.color4fUniforms["color"] = { 0.5f,0.5f,0.5f,0.5f };
			}
			else
			{
				material.color4fUniforms["color"] = { 1.0f,1.0f,1.0f,1.0f };
			}
		}
		m_owner->GetMesh().Get_Is_Moved() = false;
		material.matrix3Uniforms[instance_ndc] = mat_ndc;
	}
	Graphic::GetGraphic()->Instancing_Draw(shape, material);

	Graphic::GetGraphic()->Instance_Num_Incre();
}
