#pragma once
#include"GameState.h"
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"GameStateManager.h"
#include"PlayerController.h"
#include"mapTile.h"
#include"bullet.h"
#include"Enemy.h"
#include"bulletPoolManager.h"
#include<vector>
#include<fmod.hpp>

class PlayerController;

class Scene1:public GameState
{
private:
	JuenWindow *myWindow;
	JuenGraphics *myGraphics;
	JuenInput*myInput;

	PlayerController *myPlayer;
	std::vector<MapTile*>mapTileList;
	std::vector <Bullet*> inUsingBulletList;
	Enemy *myEnemy;
	
	//Bullet
	BulletPoolManager *myPoolManager;
	LPDIRECT3DTEXTURE9 backTexture, trajectDotTex, bulletTexture, winScreenTex, loseScreenTex, UItexture;
	LPD3DXSPRITE backSprite, bulletSprite, trajectSprite;
	//LPD3DXLINE bulletColliderline;
	RECT backGroundRect,mouseCursorRect, pBulletRect, eBulletRect,endGameScreenRect, endScreenTextRect;
	LPD3DXFONT endGameFont;
	D3DXVECTOR2 trans, spriteCentre;
	D3DXVECTOR2 BGScaling;
	D3DXMATRIX cursorMat,backGMat;

	D3DXVECTOR2 vOffsetDirection, gravity;
	D3DXVECTOR2 estimatedPlayerPos;

	D3DXVECTOR3 trajDotCenter;
	bool angleWithinRange;
	bool isGamePaused;
	bool isVictory, isGameOver;

	FMOD::System* system;
	FMOD::Sound* bgSound;
	FMOD::Sound* bulletSound;
	FMOD::Channel* bgChannel;
	FMOD::Channel* bulletChannel;

public:
	Scene1();
	~Scene1();
	
	//Enemy
	float currentEnemyStateTime;
	float currentEnemyShootTime;

	
	

	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void SceneRelease();
	void RenewInput();
	void ResetScene();


	//Enemy function
	void EnemyStateMachine();
	void BasicShootingStyle();
	void TripleShootingStyle();

	//Getter & Setter
	D3DXVECTOR2 getGravity();
	MapTile* getMapTilePointer(int index);
	int getSizeOfMapTileList();

};

