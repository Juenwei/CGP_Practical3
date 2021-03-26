#include "mapTile.h"


MapTile::MapTile(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size)
{
	myGraphics = myGraphics->GetGraphicsInstance();
	//myInput = myInput->GetInputInstance();
	//mapCollider = new CollisionManager;
	rotation = 0.0f;
	tileTexture = NULL;
	tileSprite = NULL;
	dotSprite = NULL;
	dotTexture = NULL;
	mapLine = NULL;
	//Sprite Cut Rect , if Cutting rect only have one
	mapTileCuttingRect.left = 0, mapTileCuttingRect.top = 0, mapTileCuttingRect.right = size.x, mapTileCuttingRect.bottom = size.y;
	//original collider rect , for references only 
	oriColliderRect.top = 0, oriColliderRect.left = 0, oriColliderRect.bottom = mapTileCuttingRect.bottom*scale.x, oriColliderRect.right = mapTileCuttingRect.right*scale.y;
	//Preset first
	mapTileTrans = D3DXVECTOR2(pos.x, pos.y);
	mapTileScale=D3DXVECTOR2(scale.x,scale.y);
	for (int i = 0; i < 5; i++)
	{
		mapTilePointArray[i] = D3DXVECTOR2(0, 0);
	}
	//centre point
	mapCentre = D3DXVECTOR3(mapTileCuttingRect.right / 2 * scale.x, mapTileCuttingRect.bottom / 2 * scale.y, 0.0f);
	dotTrans = D3DXVECTOR2(mapTileTrans.x - 8.0f, mapTileTrans.y - 8.0f);
	//mapColliderRect = CollisionManager::CalculateCollision(mapTileTrans, oriColliderRect, D3DXVECTOR2(mapCentre.x, mapCentre.y));
	mapColliderRect = getCollisionRect();
}

MapTile::~MapTile()
{

}

void MapTile::mapStart()
{
	D3DXCreateSprite(myGraphics->d3dDevice, &tileSprite);
	D3DXCreateSprite(myGraphics->d3dDevice, &dotSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/4X1Basic.png", &tileTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/dot.png", &dotTexture);
	D3DXCreateLine(myGraphics->d3dDevice, &mapLine);

	CollisionManager::setCollisionBox(mapTilePointArray, mapColliderRect);

}

void MapTile::mapUpdate()
{

}

void MapTile::mapRender()
{
	
	/*playerSprite->Begin(D3DXSPRITE_ALPHABLEND);
	playerSprite->SetTransform(&mat);
	playerSprite->Draw(playerTexture, &spriteCutRect, &characterCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	playerSprite->End();*/
	tileSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&mapTileMat, NULL, 0.0, &mapTileScale, NULL, rotation, &mapTileTrans);
	tileSprite->SetTransform(&mapTileMat);
	tileSprite->Draw(tileTexture, &mapTileCuttingRect, &mapCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	tileSprite->End();

	dotSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&dotMat, NULL, 0.0, NULL, NULL, 0, &dotTrans);
	dotSprite->SetTransform(&dotMat);
	dotSprite->Draw(dotTexture, NULL, &dotCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	dotSprite->End();
	CollisionManager::drawColliderBox(mapLine, mapTilePointArray);
}

void MapTile::mapRelease()
{
	CollisionManager::releaseColliderBox(mapLine);

	tileTexture->Release();
	tileTexture = NULL;

	dotTexture->Release();
	dotTexture = NULL;

	tileSprite->Release();
	tileSprite = NULL;

	dotSprite->Release();
	dotSprite = NULL;

}

void MapTile::mapCollision()
{
	
}

RECT MapTile::getCollisionRect()
{
	mapColliderRect = CollisionManager::CalculateCollision(mapTileTrans, oriColliderRect, D3DXVECTOR2(mapCentre.x,mapCentre.y));

	return mapColliderRect;
}

D3DXVECTOR2 MapTile::GetMapPosistion()
{
	return mapTileTrans;
}

D3DXVECTOR3 MapTile::GetMapTileCentre()
{
	return mapCentre;
}
