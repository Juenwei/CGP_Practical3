#pragma once
#include"GameState.h"
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"GameStateManager.h"

class Scene2:public GameState
{
private:
	JuenInput*myInput;
public:
	Scene2();
	~Scene2();
	int prev_keyState[5];

	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void SceneRelease();
	void RenewInput();
};

