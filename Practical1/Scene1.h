#pragma once
#include"GameState.h"
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"GameStateManager.h"
#include"PlayerController.h"
#include"mapTile.h"

class Scene1:public GameState
{
private:
	JuenWindow *myWindow;
	JuenGraphics *myGraphics; 
	JuenInput*myInput;
	PlayerController *player;
	MapTile *mapt;

	LPDIRECT3DTEXTURE9 backTexture , texture1;
	LPD3DXSPRITE backSprite;
	RECT spriteRect, pointerRect;
	D3DXVECTOR2 characterSize;
	int characterCurrentFrame;

	D3DXVECTOR2 trans, spriteCentre;
	D3DXVECTOR3 scaling;
	D3DXMATRIX mat;
	int xPosValue = 0, yPosValue = 0;

	LPD3DXLINE line;

	D3DXVECTOR2 playerVertices[5];
	D3DXVECTOR2 mapVertices[5];

	

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

	bool CheckCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2);
};

