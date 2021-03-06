#pragma once
#include"GameState.h"
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"

class Scene1:GameState
{
private:
	JuenWindow *myWindow;
	JuenGraphics *myGraphics; 
	JuenInput*myInput;

	LPDIRECT3DTEXTURE9 texture , texture1 , texture2;
	LPD3DXSPRITE sprite,backSprite;
	RECT spriteRect, pointerRect,characterRect;
	int xPosValue = 0, yPosValue = 0;


public:
	Scene1();
	~Scene1();
	
	void Init();
	void Update();
	void Draw();
	void Release();

};

