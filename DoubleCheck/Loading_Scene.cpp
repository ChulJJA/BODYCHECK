#include "Loading_Scene.h"
#include "Object.h"
#include "Component_Sprite.h"
#include "Graphic.h"
#include "Application.hpp"

Loading_Scene::Loading_Scene() : image(nullptr)
{

}

void Loading_Scene::Load()
{
	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
	
	image = new Object();
	image->Set_Name("loading_image");
	image->Set_Tag("image");
	image->AddComponent(new Sprite(image, "../sprite/pen_green.png", { 0.f, 0.f }));
	image->GetTransform().SetScale({ 10.f,10.f });
}

void Loading_Scene::Update(float dt)
{
	while(done)
	{
		image->GetComponentByTemplate<Sprite>()->Update(dt);
	}
	
}

void Loading_Scene::UnLoad()
{
	next_level = {};
	is_next = false;
}
