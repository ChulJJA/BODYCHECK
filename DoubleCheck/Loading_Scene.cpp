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

	HGLRC check = wglGetCurrentContext();
	
	HDC hdc = GetDC(glfwGetWin32Window(Application::Get_Application()->Get_Window()));

	check = wglGetCurrentContext();
	
	//HDC hdc = wglGetCurrentDC();
	HGLRC hglrc;

	hglrc = wglCreateContext(hdc);

	check = wglGetCurrentContext();
	
	BOOL check1 = wglMakeCurrent(hdc, hglrc);

	check = wglGetCurrentContext();
	
	//glfwMakeContextCurrent(Application::Get_Application()->Get_Window());

	check = wglGetCurrentContext();

	image = new Object();
	image->Set_Name("loading_image");
	image->Set_Tag("image");
	image->AddComponent(new Sprite(image, "../sprite/pen_green.png", { 0.f, 0.f }));
	image->GetTransform().SetScale({ 10.f,10.f });


	while(done)
	{
		image->GetComponentByTemplate<Sprite>()->Update(dt);
	
		glfwSwapBuffers(Application::Get_Application()->Get_Window());
		glfwPollEvents();
		Graphic::GetGraphic()->Update(dt);
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	DeleteDC(hdc);
}

void Loading_Scene::UnLoad()
{
	next_level = {};
	is_next = false;
}
