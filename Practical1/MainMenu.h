#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"GameStateManager.h"
#include"GameState.h"
#include<fmod.hpp>

class MainMenu :public GameState
{
private:
	JuenInput* myInput;
	JuenGraphics* myGraphics;
	LPDIRECT3DTEXTURE9 menuTexture, gameTitleTexture;
	LPD3DXSPRITE menuSprite;
	RECT menuRect,titleUIRect;
	D3DXMATRIX MenuMat;

	LPD3DXFONT font;
	RECT textRect;
	FMOD::System* system;
	FMOD::Sound* sound;
	FMOD::Channel* channel;

public:
	MainMenu();
	~MainMenu();

	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void SceneRelease();
	void RenewInput();
};

