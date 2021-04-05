#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"GameStateManager.h"
#include"GameState.h"
#include"Button.h"
#include<fmod.hpp>

class MainMenu :public GameState
{
private:
	JuenInput* myInput;
	JuenGraphics* myGraphics;
	JuenWindow*myWindow;
	Button *startButton, *tutorialButton, *quitButton, *closeTutorialButton;
	LPDIRECT3DTEXTURE9 menuTexture, gameTitleTexture, tutorialTexture;
	LPD3DXSPRITE menuSprite;
	
	RECT menuRect, titleUIRect, tutorialTexRect;
	D3DXMATRIX MenuMat;

	int redIndex, greenIndex, blueIndex;
	int colorDirection;
	LPD3DXFONT font;
	RECT textRect;
	FMOD::System* system;
	FMOD::Sound* sound;
	FMOD::Channel* channel;

public:
	//Mouse
	D3DXVECTOR2 mouseCenter, mouseArray[5];
	RECT oriMouseSizeRect, mouseRect;
	LPD3DXLINE mouseColliderLine;

	bool isShowTutorial;

	MainMenu();
	~MainMenu();

	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void SceneRelease();
	void RenewInput();
};

