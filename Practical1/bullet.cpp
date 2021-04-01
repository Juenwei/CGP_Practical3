#include "bullet.h"



Bullet::Bullet()
{
	isBulletUsing = false;
	
	myGraphics = myGraphics->GetGraphicsInstance();
	myPlayer = myPlayer->GetPlayerInstance();
	myInput = myInput->GetInputInstance();
	bulletTexture = NULL;
	bulletSprite = NULL;
	bulletColliderline = NULL;
	for (int i = 0; i < 5; i++)
	{
		bulletPointArray[i] = D3DXVECTOR2(0, 0);
	}
	bulletSize = D3DXVECTOR2(1.0f, 1.0f);
	bulletSpriteRect.left = 4;
	bulletSpriteRect.top = 0;
	bulletSpriteRect.right = 36;
	bulletSpriteRect.bottom = 32;
	bulletSpeed = 200.0f;
	oriColliderRect.top = 0;
	oriColliderRect.left = 0;
	oriColliderRect.right = 32 * bulletSize.x;
	oriColliderRect.bottom = 32 * bulletSize.y;
	bulletCentre = D3DXVECTOR3(16.0f*bulletSize.x, 16.0f*bulletSize.y, 0.0f);
	normDirectV = D3DXVECTOR2(0.0f, 0.0f);
	bulletPosition = D3DXVECTOR2(0.0f, 0.0f);
}

Bullet::~Bullet()
{

}

void Bullet::BulletStart(LPDIRECT3DTEXTURE9 bulletTexture)
{
	this->bulletTexture = bulletTexture;
}

void Bullet::BulletUpdate()
{
	if (isBulletUsing == false)
	{
		return;
	}
	if (bulletPosition.x < 100 || bulletPosition.x>800 || bulletPosition.y < 100 || bulletPosition.y >800)
	{
		isBulletUsing = false;
		bulletVelocity = D3DXVECTOR2(0.0f, 0.0f);
		bulletPosition = D3DXVECTOR2(0.0f, 0.0f);
		normDirectV = D3DXVECTOR2(0.0f, 0.0f);
	}
	bulletColliderRect = CollisionManager::CalculateCollision(bulletPosition, oriColliderRect, D3DXVECTOR2(bulletCentre.x, bulletCentre.y));
	if (CollisionManager::CheckCollision(bulletColliderRect, myPlayer->setCalculatePlayerCollision()))
	{
		std::cout << "Bullet is Collided with Player " << std::endl;
		//isBulletUsing = false;
	}
	CollisionManager::setCollisionBox(bulletPointArray, bulletColliderRect);
	bulletVelocity = normDirectV * bulletSpeed;
	bulletPosition += bulletVelocity/60;
	D3DXMatrixTransformation2D(&bulletMat, NULL, 0.0, &bulletSize, NULL, NULL, &bulletPosition);
}

void Bullet::BulletRender(LPD3DXSPRITE bulletSprite, LPD3DXLINE bulletColliderline)
{
	if (isBulletUsing == false)
	{
		return;
	}
	bulletSprite->Begin(D3DXSPRITE_ALPHABLEND);
	bulletSprite->SetTransform(&bulletMat);
	bulletSprite->Draw(bulletTexture, &bulletSpriteRect, &bulletCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	bulletSprite->End();
	CollisionManager::drawColliderBox(bulletColliderline, bulletPointArray, 5);

}

void Bullet::BulletHide()
{

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

void Bullet::setBulletToPlayer(D3DXVECTOR2 playerPos)
{
	bulletPosition = playerPos;
	calNorDirection(playerPos, myInput->getMousePosition());
	isBulletUsing = true;
}

