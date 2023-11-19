#include "bullet.h"



Bullet::Bullet()
{
	isBulletUsing = false;
	shootByPlayer = false;
	shootByEnemy = false;
	myGraphics = myGraphics->GetGraphicsInstance();
	myPlayer = myPlayer->GetPlayerInstance();
	myEnemy = myEnemy->GetEnemyInstance();
	myInput = myInput->GetInputInstance();
	bulletTexture = NULL;
	bulletSprite = NULL;
	/*bulletColliderline = NULL;
	for (int i = 0; i < 5; i++)
	{
		bulletPointArray[i] = D3DXVECTOR2(0, 0);
	}*/
	bulletSize = D3DXVECTOR2(1.0f, 1.0f);
	bulletSpriteRect.left = 4;
	bulletSpriteRect.top = 0;
	bulletSpriteRect.right = 36;
	bulletSpriteRect.bottom = 32;
	bulletSpeed = 50.0f;
	oriColliderRect.top = 0;
	oriColliderRect.left = 0;
	oriColliderRect.right = 18 * bulletSize.x;
	oriColliderRect.bottom = 18 * bulletSize.y;
	bulletCentre = D3DXVECTOR3(16.0f*bulletSize.x, 16.0f*bulletSize.y, 0.0f);
	normDirectV = D3DXVECTOR2(0.0f, 0.0f);
	bulletPosition = D3DXVECTOR2(0.0f, 0.0f);
}

Bullet::~Bullet()
{

}

void Bullet::BulletStart(LPDIRECT3DTEXTURE9 bulletTexture,RECT bulletSpriteRect, float bulletSpeed)
{
	this->bulletTexture = bulletTexture;
	this->bulletSpriteRect = bulletSpriteRect;
	this->bulletSpeed = bulletSpeed;
}

void Bullet::BulletUpdate()
{
	if (isBulletUsing == false)
	{
		return;
	}
	if (bulletPosition.x < 0 || bulletPosition.x>1080 || bulletPosition.y < 0 || bulletPosition.y > 720)
	{
		BulletHide();
	}
	CollideWithTarget();
	//CollisionManager::setCollisionBox(bulletPointArray, bulletColliderRect);
	bulletVelocity = normDirectV * bulletSpeed;
	bulletPosition += bulletVelocity/60;
	D3DXMatrixTransformation2D(&bulletMat, NULL, 0.0, &bulletSize, NULL, NULL, &bulletPosition);
}

void Bullet::BulletRender(LPD3DXSPRITE bulletSprite)
{
	if (isBulletUsing == false)
	{
		return;
	}
	bulletSprite->Begin(D3DXSPRITE_ALPHABLEND);
	bulletSprite->SetTransform(&bulletMat);
	bulletSprite->Draw(bulletTexture, &bulletSpriteRect, &bulletCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	bulletSprite->End();
	//CollisionManager::drawColliderBox(bulletColliderline, bulletPointArray, 5);

}

void Bullet::BulletHide()
{
	isBulletUsing = false;
	bulletVelocity = D3DXVECTOR2(0.0f, 0.0f);
	bulletPosition = D3DXVECTOR2(0.0f, 0.0f);
	normDirectV = D3DXVECTOR2(0.0f, 0.0f);
}

void Bullet::BulletRelease()
{
	bulletTexture->Release();
	bulletTexture = NULL;

	bulletSprite->Release();
	bulletSprite = NULL;
}

void Bullet::calNorDirection(D3DXVECTOR2 fromP, D3DXVECTOR2 toP)
{
	D3DXVECTOR2 dir, norDir;
	dir = toP - fromP;
	//mag = D3DXVec2LengthSq(&dir);
	D3DXVec2Normalize(&norDir, &dir);
	normDirectV = norDir;
	//std::cout << "Normalized vector X : " << norDir.x << "Normalized vector Y : " << norDir.y << std::endl;
}

void Bullet::setBulletToObject(D3DXVECTOR2 objectPos, D3DXVECTOR2 targetPos, bool shootByPlayer)
{
	if (shootByPlayer)
	{
		this->shootByPlayer = true;
		shootByEnemy = false;
	}
	else
	{
		this->shootByPlayer = false;
		shootByEnemy = true;
	}
	bulletPosition = objectPos;
	calNorDirection(objectPos, targetPos);
	isBulletUsing = true;
}

void Bullet::CollideWithTarget()
{
	bulletColliderRect = CollisionManager::CalculateCollision(bulletPosition, oriColliderRect, D3DXVECTOR2(bulletCentre.x-8.0f, bulletCentre.y - 8.0f));
	RECT TargetCollider;
	if (shootByPlayer)
	{
		//Check Enemy Collider
		TargetCollider = myEnemy->getEnemyColliderRect();
	}
	else if (shootByEnemy)
	{
		TargetCollider = myPlayer->getPlayerCollision();
	}
	if (CollisionManager::CheckCollision(bulletColliderRect, TargetCollider))
	{
		if (shootByPlayer)
		{
			std::cout << "Enemy Taking Damange " << std::endl;
			myEnemy->BulletCollide(5);
		}
		else if (shootByEnemy)
		{
			std::cout << "Player Taking Damange" << std::endl;
			myPlayer->gettingDamage(5);
		}
		isBulletUsing = false;
		bulletVelocity = D3DXVECTOR2(0.0f, 0.0f);
		bulletPosition = D3DXVECTOR2(0.0f, 0.0f);
		normDirectV = D3DXVECTOR2(0.0f, 0.0f);
	}
}


