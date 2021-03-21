#pragma once
#include"GameState.h"
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"GameStateManager.h"
#include"PlayerController.h"
#include"mapTile.h"
#include<vector>

class Scene1:public GameState
{
private:
	JuenWindow *myWindow;
	JuenGraphics *myGraphics;
	JuenInput*myInput;

	PlayerController *myPlayer;
	CollisionManager *mycollision;
	//MapTile *maptArray[2];
	std::vector<MapTile*>mapTileList;

	LPDIRECT3DTEXTURE9 backTexture , texture1;
	LPD3DXSPRITE backSprite;
	RECT spriteRect, pointerRect;

	D3DXVECTOR2 trans, spriteCentre;
	D3DXVECTOR3 scaling;
	D3DXMATRIX mat;

public:
	Scene1();
	~Scene1();
	


	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void Release();
	void RenewInput();

	//Return one pointer but control by index
	//MapTile* getAllMapTileColllider(int index);
	void playerJump();


	//bool CheckCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2);
};

