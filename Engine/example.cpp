#include "example.hpp"

namespace
{
	Application* app_ = nullptr;//키보드
	ObjectManager* object_manager = nullptr;//모든object관리
	StateManager* state_manager = nullptr;//
	Graphic* graphic = nullptr;
}
Example* Example::example = nullptr;
Example* Example::GetExample()
{
	if (example == nullptr)
	{
		example = new Example();
	}
	return example;
}
void Example::Init()
{
	app_ = Application::Get_Application();
	object_manager = ObjectManager::GetObjectManager();
	state_manager = StateManager::GetStateManager();
	graphic = Graphic::GetGraphic();
	app_->Init();

	object_manager->Init();
	state_manager->Init();
	graphic->Init();

	state_manager->AddState("Menu", new Menu);
	state_manager->AddState("Level1", new Level1);

	Object* temp = new Object();
	temp->AddComponent(new Sprite());
	temp->AddComponent(new Component_Transform());//장착component
	temp->AddComponent(new Component_TopDownMovement());
	temp->Set_Name("first");

	Object* temp_sec = new Object();
	temp_sec->AddComponent(new Sprite());
	temp_sec->AddComponent(new Component_Transform());
	temp_sec->Set_Name("second");

	object_manager->AddObject(temp);
	object_manager->AddObject(temp_sec);

	game_timer.Reset();
}

void Example::Update()
{
	m_dt = game_timer.GetElapsedSeconds();
	game_timer.Reset();

	app_->Update(m_dt);
	state_manager->Update(m_dt);
	graphic->Update(m_dt);
	object_manager->Update(m_dt);

	//Reset camera zoom
	Reset();

	if (input.Is_Key_Triggered(GLFW_KEY_1))
		state_manager->is_pause = !state_manager->is_pause;
}
void Example::Delete()
{

}

void Example::Reset()
{
	Graphic::GetGraphic()->Get_View().Get_Camera_View().SetZoom(1.0f);
	Graphic::GetGraphic()->Get_View().Get_Camera().SetCenter({ 0,0 });
}