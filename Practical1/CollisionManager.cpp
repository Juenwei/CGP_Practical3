#include "CollisionManager.h"

//
RECT CollisionManager::CalculateCollision(D3DXVECTOR2 pos, RECT rect, D3DXVECTOR2 centrePos)
{
	rect.right = pos.x + rect.right - rect.left - centrePos.x;
	rect.left = pos.x - centrePos.x;
	rect.bottom = pos.y + rect.bottom - rect.top - centrePos.y;
	rect.top = pos.y - centrePos.y;

	return rect;
}

bool CollisionManager::CheckCollision(RECT rect1, RECT rect2)
{
	if (rect1.bottom < rect2.top) return false;

	if (rect1.top > rect2.bottom) return false;

	if (rect1.right < rect2.left) return false;

	if (rect1.left > rect2.right) return false;

	//std::cout << "Collided" << std::endl;

	return true;
}

void CollisionManager::setCollisionBox(D3DXVECTOR2 posArray[], RECT rect)
{
	posArray[0] = D3DXVECTOR2(rect.left, rect.top);
	posArray[1] = D3DXVECTOR2(rect.right, rect.top);
	posArray[2] = D3DXVECTOR2(rect.right, rect.bottom);
	posArray[3] = D3DXVECTOR2(rect.left, rect.bottom);
	posArray[4] = D3DXVECTOR2(rect.left, rect.top);
}

void CollisionManager::drawColliderBox(LPD3DXLINE line, D3DXVECTOR2 posArray[5], int drawAmount)
{
	line->Begin();

	line->Draw(posArray, drawAmount, D3DCOLOR_XRGB(100, 255, 120));

	line->End();
}

void CollisionManager::releaseColliderBox(LPD3DXLINE line)
{
	line->Release();
	line = NULL;
}



int CollisionManager::checkSideOfCollider(D3DXVECTOR2 targetObjectPos[4], D3DXVECTOR2 otherObjectPos[4],RECT otherObjectRect)
{
	//std::cout << "Player Left Point X : " << targetObjectPos[leftPoint].x << "Maptile Left Point X : " << otherObjectPos[leftPoint].x << std::endl;
	if (targetObjectPos[topPoint].y < otherObjectPos[topPoint].y && targetObjectPos[leftPoint].x >= otherObjectRect.left && targetObjectPos[rightPoint].x <= otherObjectRect.right)
	{
		std::cout << "Player On top" << std::endl;
		return 1;
	}
	//If(playerTop .y >= colliderTop.y && playerRight.x < colliderLeft.x )return PlayerOnleft
	else if (targetObjectPos[leftPoint].x < otherObjectPos[leftPoint].x&&targetObjectPos[rightPoint].x < otherObjectPos[rightPoint].x)
	{
		std::cout << "Player On Left" << std::endl;
		return 2;
	}
	else if (targetObjectPos[rightPoint].x > otherObjectPos[rightPoint].x&&targetObjectPos[leftPoint].x > otherObjectPos[leftPoint].x)
	{
		std::cout << "Player On Right" << std::endl;
		return 3;
	}
	else 
		return 0;
}

void CollisionManager::calculateSideOfCollision(D3DXVECTOR2 sidePointArray[4], RECT currentColliderRect)
{
	
	//Top Point , Y axis fixed (top)
	sidePointArray[topPoint] = D3DXVECTOR2((currentColliderRect.left + currentColliderRect.right) / 2, currentColliderRect.top);
	//Left Point , X axis fixed (left)
	sidePointArray[leftPoint] = D3DXVECTOR2(currentColliderRect.left, (currentColliderRect.top + currentColliderRect.bottom) / 2);
	//Bottom Point , Y axis fixed (bottom)
	sidePointArray[bottomPoint] = D3DXVECTOR2((currentColliderRect.left + currentColliderRect.right) / 2, currentColliderRect.bottom);
	//Right Point , X axis fixed (right)
	sidePointArray[rightPoint] = D3DXVECTOR2(currentColliderRect.right, (currentColliderRect.top + currentColliderRect.bottom) / 2);
}
