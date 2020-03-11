#include "Loading_Scene.h"
#include "Object.h"
#include "Component_Sprite.h"
#include "Graphic.h"
#include "Application.hpp"
#include "Level1.h"


#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32 
#include "GLFW/glfw3native.h"

#include <Windows.h>
#include <consoleapi2.h>
#include <consoleapi3.h>
#include "GL.hpp"

Loading_Scene::Loading_Scene() : image(nullptr)
{

}

void Loading_Scene::Load()
{
	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(0.35f);
	done = true;
}

void Loading_Scene::Update(float dt)
{
	image = new Object();
	image->Set_Name("loading_image");
	image->Set_Tag("image");

	/*image->AddComponent(new Sprite(image, "../sprite/pen_red_ani.png", true, 8, 2, {0.f, 0.f}, 
		{200.f, 200.f}, {255,255,255,255}));*/

	image->AddComponent(new Sprite(image, "../Sprite/HowToPlay.png", { 0, 0 }, false));

	//image->AddComponent(new Sprite(image, "../sprite/loadingscene.png", { 0.f, 0.f }));
	image->SetScale(20.f);
	
	while(done)
	{
		glfwSwapBuffers(Application::Get_Application()->Get_Window());
		glfwPollEvents();
		Graphic::GetGraphic()->Update(dt);
		GL::set_clear_color({ 0.31372, 0.73725, 0.8745, 1 });
		image->GetComponentByTemplate<Sprite>()->Update(dt);
	}
}

void Loading_Scene::UnLoad()
{
	next_level = {};
	is_next = false;
}
