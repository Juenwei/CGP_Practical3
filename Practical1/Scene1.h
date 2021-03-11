#pragma once
#include"GameState.h"
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"GameStateManager.h"
#include"PlayerController.h"

class Scene1:public GameState
{
private:
	JuenWindow *myWindow;
	JuenGraphics *myGraphics; 
	JuenInput*myInput;
	PlayerController *player;

	LPDIRECT3DTEXTURE9 backTexture , texture1;
	LPD3DXSPRITE backSprite;
	RECT spriteRect, pointerRect;
	D3DXVECTOR2 characterSize;
	int characterCurrentFrame;

	D3DXVECTOR2 trans, spriteCentre;
	D3DXVECTOR3 scaling;
	D3DXMATRIX mat;
	int xPosValue = 0, yPosValue = 0;
	int prev_keyState[5];

	//D3DXVECTOR2 position;

public:
	Scene1();
	~Scene1();
	


	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void Release();
	void RenewInput();
};

