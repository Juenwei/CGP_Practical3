#include "Scene2.h"

Scene2::Scene2()
{
	myInput=myInput->GetInputInstance();
	ZeroMemory(&prev_keyState, sizeof(prev_keyState));
}
Scene2::~Scene2()
{

}

void Scene2::Init()
{
	
}
void Scene2::Update()
{
	if (myInput->AcceptKeyDown(DIK_F1))
	{
	
		prev_keyState[0] = 1;

	}
	else if (prev_keyState[0] == 1)
	{
		prev_keyState[0] = 0;
		std::cout << "Change Scene" << std::endl;
		GameStateManager::GetInstance()->ChangeGameState(GameStateManager::SCENE_1);

	}
}

void Scene2::FixedUpdate()
{
}



void Scene2::Draw() {

}
void Scene2::Release() {
	
}

void Scene2::RenewInput()
{

}