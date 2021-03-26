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

void CollisionManager::drawColliderBox(LPD3DXLINE line, D3DXVECTOR2 posArray[5])
{
	line->Begin();

	line->Draw(posArray, 5, D3DCOLOR_XRGB(100, 255, 120));

	line->End();
}

void CollisionManager::releaseColliderBox(LPD3DXLINE line)
{
	line->Release();
	line = NULL;
}

int CollisionManager::checkSideOfCollider(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2)
{
	//(Pos1 -> Pos2 )vector
	D3DXVECTOR2 offset = pos2 - pos1;
	D3DXVec2Normalize(&offset, &offset);

	if (abs(offset.x)>abs(offset.y))
	{
		if (offset.x > 0)
			return 4;
		else
			return 3;
	}
	else
	{
		if (offset.y > 0)
			return 2;
		else
			return 1;
	}
	return 0;
}
