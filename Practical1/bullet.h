#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"PlayerController.h"
#include"CollisionManager.h"

class Bullet
{
private:
	JuenGraphics* myGraphics;
	JuenInput *myInput;
	PlayerController* myPlayer;

	//Sprite setting
	LPDIRECT3DTEXTURE9 bulletTexture;
	LPD3DXSPRITE bulletSprite;
	RECT bulletSpriteRect;
	D3DXVECTOR2 bulletSize;
	D3DXVECTOR2 bulletPosition;
	D3DXVECTOR3 bulletCentre;
	D3DXMATRIX bulletMat;

	//Shooting element
	D3DXVECTOR2 normDirectV;
	D3DXVECTOR2 bulletVelocity;
	float bulletSpeed;

	//Collider Setting
	RECT oriColliderRect, bulletColliderRect;
	D3DXVECTOR2 bulletPointArray[5];
	LPD3DXLINE bulletColliderline;

public:
	//Bullet Status
	bool isBulletUsing;

	Bullet();
	~Bullet();

	void BulletStart(LPDIRECT3DTEXTURE9 bulletTexture);
	void BulletUpdate();
	void BulletRender(LPD3DXSPRITE bulletSprite, LPD3DXLINE bulletColliderline);
	void BulletRelease();
	void BulletHide();

	void calNorDirection(D3DXVECTOR2 fromP, D3DXVECTOR2 toP);
	void setBulletToPlayer(D3DXVECTOR2 playerPos);

	//Collision method
	//RECT getCalculateCollision();
	//RECT setCalculateCollision(D3DXVECTOR2 pos);
	//void bulletCollision();


};

