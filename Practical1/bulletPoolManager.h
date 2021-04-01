#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include<vector>
#include"bullet.h"
#include"PlayerController.h"
#include"CollisionManager.h"

class BulletPoolManager
{
	/*-GetPoolInstance, ReleasePoolInsatance(Singetlon)
		1. Fill method
		2. Get bullet from pool method(PULL) << CheckForBulletSize
		3. Send back to pool method(PUSH)
		4. Release pool*/

private:
	static BulletPoolManager* instance;
	JuenGraphics* myGraphics;
	PlayerController* myPlayer;

	D3DXVECTOR2 fromPlayerPos;

	BulletPoolManager();
	~BulletPoolManager();
public:
	static std::vector<Bullet*> poolList;

	//Singletlon method
	BulletPoolManager* GetPoolManagerInstance();
	void ReleasePoolManagerInstance();

	static Bullet* PullBulletFromPool();
	static void ClearPool();
};

