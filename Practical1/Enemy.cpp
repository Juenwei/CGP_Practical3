#include "Enemy.h"

Enemy *Enemy::instance = NULL;


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

Enemy *Enemy::GetEnemyInstance()
{
	if (!instance)
	{
		instance = new Enemy();
	}
	return instance;
}

void Enemy::ReleaseEnemyInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

void Enemy::EnemyStart()
{
}

void Enemy::EnemyMovement()
{
}

void Enemy::EnemyRender()
{
}

void Enemy::EnemyAnimation()
{
}

void Enemy::EnemyRelease()
{
}

D3DXVECTOR2 Enemy::GetEnemyPosistion()
{
	return D3DXVECTOR2();
}
