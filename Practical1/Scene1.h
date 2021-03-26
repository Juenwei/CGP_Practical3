#pragma once
#include"GameState.h"
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"GameStateManager.h"
#include"PlayerController.h"
#include"mapTile.h"
#include<vector>

class PlayerController;

class Scene1:public GameState
{
private:
	JuenWindow *myWindow;
	JuenGraphics *myGraphics;
	JuenInput*myInput;

	PlayerController *myPlayer;
	std::vector<MapTile*>mapTileList;
	int mapTileAmount;

	LPDIRECT3DTEXTURE9 backTexture, texture1, trajectDotTex;// enemyTex;
	LPD3DXSPRITE backSprite , trajectSprite;
	RECT spriteRect, pointerRect , dotCuttingRect;

	D3DXVECTOR2 trans, spriteCentre;
	D3DXVECTOR3 scaling;
	D3DXMATRIX mat;

	D3DXVECTOR2 nextVelocity, vOffsetDirection, gravity;
	D3DXVECTOR2 estimatedPlayerPos;

	D3DXVECTOR3 trajDotCenter;
	bool angleWithinRange;

	int testIndex;
	int loopIndex=0;
public:
	Scene1();
	~Scene1();
	


	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void Release();
	void RenewInput();
	
	//Trajectory
	void ChangePlayerState(int playerStateIndex);

	//Getter & Setter
	D3DXVECTOR2 getGravity();
	MapTile* getMapTilePointer(int index);
	int getSizeOfMapTileList();
	
	int getTestIndex();
};

