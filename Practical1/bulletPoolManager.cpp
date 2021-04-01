#include "bulletPoolManager.h"

BulletPoolManager* BulletPoolManager::instance = NULL;
std::vector<Bullet*>BulletPoolManager::poolList;

BulletPoolManager::BulletPoolManager()
{
}

BulletPoolManager::~BulletPoolManager()
{
	
}

BulletPoolManager* BulletPoolManager::GetPoolManagerInstance()
{
	if (!instance)
	{
		instance = new BulletPoolManager();
	}
	return instance;
}

void BulletPoolManager::ReleasePoolManagerInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}


Bullet* BulletPoolManager::PullBulletFromPool()
{
	Bullet* bullet = NULL;
	for (int i = 0; i < poolList.size(); i++)
	{
		if (poolList[i]->isBulletUsing == false)
		{
			bullet = poolList[i];
			break;
		}
	}
	//Fill pool
	if (bullet == NULL)
	{
		bullet = new Bullet();
		poolList.push_back(bullet);
	}

	return bullet;
}

void BulletPoolManager::ClearPool()
{
	for (int i = 0; i < poolList.size(); i++)
	{
		poolList[i]->BulletRelease();
		delete poolList[i];
		poolList[i] = NULL;
	}
	poolList.clear();
}