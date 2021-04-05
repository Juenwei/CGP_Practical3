#include "mapTile.h"


MapTile::MapTile(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 colliderSize, float rotation)
{
	myGraphics = myGraphics->GetGraphicsInstance();
	this->rotation = rotation;
	amountOfTile = 0;
	tileTexture = NULL;
	tileSprite = NULL;
	//dotSprite = NULL;
	//dotTexture = NULL;
	//mapLine = NULL;
	//Sprite Cut Rect , if Cutting rect only have one
	mapTileCuttingRect.left = 0, mapTileCuttingRect.top = 0, mapTileCuttingRect.right = 128.0f, mapTileCuttingRect.bottom = 64.0f;
	//original collider rect , for references only 
	oriColliderRect.top = 0, oriColliderRect.left = 0, oriColliderRect.bottom = colliderSize.y*scale.x, oriColliderRect.right = colliderSize.x *scale.y;
	//Preset first
	mapColliderTrans = D3DXVECTOR2(pos.x, pos.y);
	mapTileScale=D3DXVECTOR2(scale.x,scale.y);
	/*for (int i = 0; i < 5; i++)
	{
		mapTilePointArray[i] = D3DXVECTOR2(0, 0);
	}*/
	for (int i = 0; i < 4; i++)
	{
		mapSideCenterPoint[i] = D3DXVECTOR2(0, 0);
	}
	//centre point
	mapCentre = D3DXVECTOR3(oriColliderRect.right / 2 * scale.x, oriColliderRect.bottom / 2 * scale.y, 0.0f);
	dotTrans = D3DXVECTOR2(mapColliderTrans.x - 8.0f, mapColliderTrans.y - 8.0f);
	mapColliderRect = getCollisionRect();
	CollisionManager::calculateSideOfCollision(mapSideCenterPoint, mapColliderRect);
}

MapTile::~MapTile()
{

}

void MapTile::mapStart()
{
	D3DXCreateSprite(myGraphics->d3dDevice, &tileSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/4X2BaseTile.png", &tileTexture);

	//D3DXCreateSprite(myGraphics->d3dDevice, &dotSprite);
	//D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/dot.png", &dotTexture);
	//D3DXCreateLine(myGraphics->d3dDevice, &mapLine);
	//CollisionManager::setCollisionBox(mapTilePointArray, mapColliderRect);

}

void MapTile::mapUpdate()
{

}

void MapTile::mapRender()
{
	tileSprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < amountOfTile; i++)
	{
		D3DXMatrixTransformation2D(&mapTileMat, NULL, 0.0, &mapTileScale, NULL, rotation, &generatePointList[i]);
		tileSprite->SetTransform(&mapTileMat);
		tileSprite->Draw(tileTexture, &mapTileCuttingRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
	tileSprite->End();

	//dotSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//D3DXMatrixTransformation2D(&dotMat, NULL, 0.0, NULL, NULL, 0, &dotTrans);
	//dotSprite->SetTransform(&dotMat);
	//dotSprite->Draw(dotTexture, NULL, &dotCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//dotSprite->End();
	//CollisionManager::drawColliderBox(mapLine, mapTilePointArray, 5);
	//CollisionManager::drawColliderBox(mapLine, mapSideCenterPoint, 4);

	
}

void MapTile::mapRelease()
{
	//CollisionManager::releaseColliderBox(mapLine);
	//dotTexture->Release();
	//dotTexture = NULL;
	//dotSprite->Release();
	//dotSprite = NULL;

	tileTexture->Release();
	tileTexture = NULL;

	tileSprite->Release();
	tileSprite = NULL;

}

void MapTile::mapCollision()
{
	
}

void MapTile::settingGeneratePoint(int amountGenerate, D3DXVECTOR2 offsetRange, D3DXVECTOR2 initialPoint)
{
	D3DXVECTOR2 tempPoint = initialPoint;
	amountOfTile = amountGenerate;
	for (int i = 0; i < amountGenerate; i++)
	{
		generatePointList.push_back(tempPoint);
		tempPoint += offsetRange;
	}
}

RECT MapTile::getCollisionRect()
{
	mapColliderRect = CollisionManager::CalculateCollision(mapColliderTrans, oriColliderRect, D3DXVECTOR2(mapCentre.x,mapCentre.y));

	return mapColliderRect;
}

D3DXVECTOR2 MapTile::GetMapPosistion()
{
	return mapColliderTrans;
}

D3DXVECTOR3 MapTile::GetMapTileCentre()
{
	return mapCentre;
}
