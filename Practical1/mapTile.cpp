#include "mapTile.h"

MapTile::MapTile(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size)
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	tileTexture=NULL;
	tileSprite=NULL;
	dotSprite = NULL;
	mapTileRect.left = 0, mapTileRect.top = 0, mapTileRect.right = size.x, mapTileRect.bottom = size.y;
	//collider rect
	mapColliderRect.top = 0, mapColliderRect.left = 0, mapColliderRect.bottom = mapTileRect.bottom*scale.x, mapColliderRect.right = mapTileRect.right*scale.y;
	//centre point
	mapCentre = D3DXVECTOR3(mapTileRect.right / 2 * scale.x, mapTileRect.bottom / 2 * scale.y, 0.0f);
	mapTileTrans = D3DXVECTOR2(pos.x, pos.y);
	mapTileSize=D3DXVECTOR2(scale.x,scale.y);
	dotCentre = D3DXVECTOR3(8.0f, 8.0f, 0.0f);

	
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
	float rotation = 0;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &mapTileSize, NULL, rotation, &mapTileTrans);


	dotTrans = D3DXVECTOR2(mapTileTrans.x, mapTileTrans.y);
	D3DXMatrixTransformation2D(&dotMat, NULL, 0.0, NULL, NULL, 0, &dotTrans);
	//std::cout << "Centre pos : (" << scallingCentre.x << " , " << scallingCentre.y << std::endl;

}

void MapTile::mapUpdate()
{
}

void MapTile::mapRender()
{
	tileSprite->Begin(D3DXSPRITE_ALPHABLEND);
	tileSprite->SetTransform(&mat);
	tileSprite->Draw(tileTexture, &mapTileRect, &mapCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//std::cout << "Slime pos : ("<<xPosValue<<" , " <<yPosValue<< std::endl;
	tileSprite->End();

	dotSprite->Begin(D3DXSPRITE_ALPHABLEND);
	dotSprite->SetTransform(&dotMat);
	dotSprite->Draw(dotTexture, NULL, &dotCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	dotSprite->End();

}

void MapTile::mapRelease()
{
	tileTexture->Release();
	tileTexture = NULL;

	dotTexture->Release();
	dotTexture = NULL;

	tileSprite->Release();
	tileSprite = NULL;

	dotSprite->Release();
	dotSprite = NULL;

}

D3DXVECTOR2 MapTile::GetMapPosistion()
{
	return D3DXVECTOR2(mapTileTrans.x,mapTileTrans.y);
}

RECT MapTile::GetMaprRectSize()
{
	return mapColliderRect;
}

D3DXVECTOR3 MapTile::GetMapTileCentre()
{
	return mapCentre;
}
