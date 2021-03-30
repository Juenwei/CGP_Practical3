#pragma once
#include"JuenGraphics.h"
class CollisionManager
{
	enum ColliderSidePoint
	{
		topPoint,
		leftPoint,
		bottomPoint,
		rightPoint
	};
public:
	//Use method by CollisionManager::method , all calculation provided
	
	static RECT CalculateCollision(D3DXVECTOR2 pos, RECT rect, D3DXVECTOR2 centrePos);
	static bool CheckCollision(RECT rect1, RECT rect2);
	
	static void setCollisionBox(D3DXVECTOR2 posArray[], RECT rect);
	static void drawColliderBox(LPD3DXLINE line, D3DXVECTOR2 posArray[5],int drawAmount);
	static void releaseColliderBox(LPD3DXLINE line);
	static int checkSideOfCollider(D3DXVECTOR2 targetObjectPos[4], D3DXVECTOR2 otherObjectPos[4], RECT otherObjectRect);
	static void calculateSideOfCollision(D3DXVECTOR2 sidePointArray[4], RECT currentColliderRect);
};

