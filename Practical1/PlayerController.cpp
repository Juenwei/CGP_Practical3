#include "PlayerController.h"
#include "Scene1.h"


PlayerController::PlayerController(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size, float speed)
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	//Ground State 
	pStateType[groundState].colliderRect.top = 0;
	pStateType[groundState].colliderRect.left = 0;
	pStateType[groundState].colliderRect.bottom = 26;
	pStateType[groundState].colliderRect.right = 32;
	pStateType[groundState].spriteRotationRadian = 0.0f;
	pStateType[groundState].moveDikIndex = groundState;
	pStateType[groundState].minAngleClamp = -10;
	pStateType[groundState].maxAngleClamp = -170;

	//Wall State
	pStateType[wallState].colliderRect.top = 0;
	pStateType[wallState].colliderRect.left = 0;
	pStateType[wallState].colliderRect.bottom = 32;
	pStateType[wallState].colliderRect.right = 26;
	pStateType[wallState].spriteRotationRadian = 1.5f;
	pStateType[wallState].moveDikIndex = groundState;
	pStateType[wallState].minAngleClamp = -10;
	pStateType[wallState].maxAngleClamp = -170;

	//Sprite & Animation
	playerTexture = NULL;
	playerSprite = NULL;
	characterCurrentFrame = 0;
	characterSize.x = size.x;
	characterSize.y = size.y;
	scaleFactor.x = scale.x;
	scaleFactor.y = scale.y;
	characterCentre = D3DXVECTOR3(size.x / 2, size.y / 4, 0.0f);
	rect2Center = D3DXVECTOR3(characterCentre.x + 3, characterCentre.y + 2.0f, 0.0f);
	playerFaceDirX = 1;
	animationTimer = 0;
	animationDuration = 0.5f / 5;
	rotation = 0.0f;

	//TrajectSprite
	trajectDotTex = NULL;
	trajectSprite = NULL;
	trajDotCenter = D3DXVECTOR3(16.0f, 16.0f, 0.0f);
	trajDotCuttingRect.top = 1;
	trajDotCuttingRect.left = 33;
	trajDotCuttingRect.bottom = 31;
	trajDotCuttingRect.right = 63;

	//Movement
	prev_PlayerVelocity = D3DXVECTOR2(0, 0);
	totalVelocity = D3DXVECTOR2(0, 0);
	playerPosValue = D3DXVECTOR2(pos.x, pos.y);
	this->speed = speed;
	//adjustedSpeed = this->speed / 60.0f;



	//State
	isPlayerMoving = false;
	isReleasedKey = false;
	isPlayerFalling = true;
	isPlayerCollided = false;
	isShowingTrajectDot = false;
	currentPStatus = groundState;

	/*struct PStatus {
		float spriteRotationAngle;
		int moveDikIndex;
		float minAngleClamp, maxAngleClamp;
		RECT colliderRect;
	};*/

	//Collider
	for (int i = 0; i < 5; i++)
	{
		playerPointArray[i] = D3DXVECTOR2(0, 0);
		playerPointArray2[i] = D3DXVECTOR2(0, 0);;
	}
	oriSizeRect.top = pStateType[groundState].colliderRect.top;
	oriSizeRect.left = pStateType[groundState].colliderRect.left;
	oriSizeRect.bottom = pStateType[groundState].colliderRect.bottom;
	oriSizeRect.right = pStateType[groundState].colliderRect.right;
	oriSizeRect2.top = 0, oriSizeRect2.left = 0, oriSizeRect2.bottom = 32, oriSizeRect2.right = 38;

}


PlayerController::~PlayerController()
{

}

PlayerController *PlayerController::instance = NULL;

PlayerController *PlayerController::GetPlayerInstance()
{
	if (!instance)
	{
		instance = new PlayerController(D3DXVECTOR2(500.0f, 400.0f), D3DXVECTOR2(2.0f, 2.0f), D3DXVECTOR2(32.0f, 32.0f), 100.0f);

	}
	return instance;
}

void PlayerController::ReleasePlayerInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

void PlayerController::PlayerStart()
{
	D3DXCreateSprite(myGraphics->d3dDevice, &playerSprite);
	D3DXCreateSprite(myGraphics->d3dDevice, &trajectSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slime.png", &playerTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slimeTraject.png", &trajectDotTex);
	D3DXCreateLine(myGraphics->d3dDevice, &playerLine);
	/*spriteCutRect.left = 0;
	spriteCutRect.top = 32;
	spriteCutRect.right = spriteCutRect.left + characterSize.x;
	spriteCutRect.bottom = spriteCutRect.top + characterSize.y;*/
}

void PlayerController::ReceiveInput()
{
	isPlayerMoving = false;
	inputAxis = D3DXVECTOR2(0, 0);
	//jumpVelocity = D3DXVECTOR2(0, 0);
	if (myInput->AcceptKeyDown(DIK_LEFT))
	{
		//std::cout << "LEFT" << std::endl;
		inputAxis.x = -1;
		playerFaceDirX =-1;
		isPlayerMoving = true;
		myInput->prev_KeyState[DIK_LEFT] = 1;
	}
	else if (myInput->prev_KeyState[DIK_LEFT] == 1)
	{
		myInput->prev_KeyState[DIK_LEFT] = 0;
		//isPlayerMoving = false;

	}
	if (myInput->AcceptKeyDown(DIK_RIGHT))
	{
		//std::cout << "RIGHT" << std::endl;
		inputAxis.x = 1;
		playerFaceDirX = 1;
		isPlayerMoving = true;
		myInput->prev_KeyState[DIK_LEFT] = 1;
	}
	else if (myInput->prev_KeyState[DIK_RIGHT] == 1)
	{
		myInput->prev_KeyState[DIK_RIGHT] = 0;
		//isPlayerMoving = false;

	}
	if (myInput->AcceptKeyDown(DIK_UP))
	{
		myInput->prev_KeyState[DIK_UP] = 1;
	}
	else if (myInput->prev_KeyState[DIK_UP] == 1)
	{
		myInput->prev_KeyState[DIK_UP] = 0;
		rotation += 0.1f;
		std::cout << "Current Rotation : " << rotation << std::endl;

	}
	if (myInput->AcceptKeyDown(DIK_DOWN))
	{
		myInput->prev_KeyState[DIK_DOWN] = 1;
	}
	else if (myInput->prev_KeyState[DIK_DOWN] == 1)
	{
		myInput->prev_KeyState[DIK_DOWN] = 0;
		rotation -= 0.1f;
		std::cout << "Current Rotation : " << rotation << std::endl;

	}
	if (myInput->AcceptKeyDown(DIK_P))
	{
		//std::cout << "Pos : (" << posValue.x << " , " << posValue.y << " ) " << std::endl;
		std::cout << "Scene 1 test value " << sceneInstance->getTestIndex() << std::endl;
	}
	if (myInput->AcceptButtonDown(1))
	{
		calNorDirection(GetPlayerPosistion(), myInput->getMousePosition());
		if (trajectoryAngleClamp()&& totalVelocity.y == 0)
		{
			isShowingTrajectDot = true;
			myInput->prev_MouseState[1] = 1;
			
		}
		
	}
	else if (myInput->prev_MouseState[1] == 1)
	{
		myInput->prev_MouseState[1] = 0;
		playerJumpVer2();
	
	}
	else
	{
		isShowingTrajectDot = false;
	}
	
}

void PlayerController::PlayerMovement()
{
	//std::cout << " Is player move : " << isPlayerMoving << std::endl;
	CollisionManager::setCollisionBox(playerPointArray, setCalculatePlayerCollision());
	CollisionManager::setCollisionBox(playerPointArray2, colliderSizeRect2);
	for (int i = 0; i < sceneInstance->getSizeOfMapTileList(); i++)
	{
		RECT tempMapRect = sceneInstance->getMapTilePointer(i)->getCollisionRect();

		if (CollisionManager::CheckCollision(setCalculatePlayerCollision(), tempMapRect))
		{
			ResolveCollision(sceneInstance->getMapTilePointer(i)->getCollisionRect());
		}
		//Loop until last no collision
		colliderSizeRect2 = CollisionManager::CalculateCollision(playerPosValue, oriSizeRect2, D3DXVECTOR2(rect2Center.x, rect2Center.y));
		if (CollisionManager::CheckCollision(colliderSizeRect2, tempMapRect))
		{
			//std::cout << "Outer collider Collided" << std::endl;
			isPlayerCollided = true;
			break;
		}
		else if (i == sceneInstance->getSizeOfMapTileList() - 1)
		{
			//std::cout << "No collision" << std::endl;
			isPlayerCollided = false;
		}
	}

	if (isPlayerMoving&&totalVelocity.y==0)
	{
		playerMoveVelocity = inputAxis * speed;
	
	}
	else
	{
		playerMoveVelocity = D3DXVECTOR2(0, 0);
	}
	
	//New MEthod
	//std::cout << "JUMP VEL : " << " ( " << totalVelocity.x << " , " << totalVelocity.y << " ) " << std::endl;
	//Speed Clamping
	if (abs(totalVelocity.x) > 100)
	{
		totalVelocity.x = (totalVelocity.x / abs(totalVelocity.x)) * 100;
	}
	
	playerPosValue += (totalVelocity + playerMoveVelocity )/ 60.0f;

	if (playerPosValue.y <= 600)
	{
		totalVelocity.y += falling().y;
	}
	else
	{
		totalVelocity = D3DXVECTOR2(0, 0);
		playerPosValue.y = 600;
	}
	if (playerMoveVelocity != D3DXVECTOR2(0, 0)|| totalVelocity != D3DXVECTOR2(0, 0))
	{
		prev_PlayerVelocity = playerMoveVelocity + totalVelocity;
	}


	scaling = D3DXVECTOR2(scaleFactor.x*playerFaceDirX, scaleFactor.y);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, rotation, &playerPosValue);
}

void PlayerController::PlayerRender() 
{
	playerSprite->Begin(D3DXSPRITE_ALPHABLEND);
	playerSprite->SetTransform(&mat);
	playerSprite->Draw(playerTexture, &spriteCutRect, &characterCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	
	playerSprite->End();
	CollisionManager::drawColliderBox(playerLine, playerPointArray);
	CollisionManager::drawColliderBox(playerLine, playerPointArray2);
	if (isShowingTrajectDot)
	{
		trajectSprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR2 tempVelocity = normDirectV * 500;
		D3DXVECTOR2 tempPosistion = playerPosValue;
		for (int i = 0; i < 60; i++)
		{
			
			tempPosistion += (tempVelocity / 60.0f);
			tempVelocity.y += 10;
			if (abs(tempVelocity.x) > 100)
			{
				tempVelocity.x = (tempVelocity.x / abs(tempVelocity.x)) * 100;
			}
			if (i % 5 == 0)
			{
				D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &tempPosistion);
				trajectSprite->SetTransform(&mat);
				trajectSprite->Draw(trajectDotTex, &trajDotCuttingRect, &trajDotCenter, NULL, D3DCOLOR_XRGB(255, 255, 255));
			}
			
			
		}
		trajectSprite->End();
	}
	


}

void PlayerController::PlayerAnimation()
{
	animationTimer += 1 / 60.0f;
	if (animationTimer >= animationDuration)
	{
		animationTimer -= animationDuration;
		characterCurrentFrame++;
		characterCurrentFrame %= 5;
	}
	
	//Update animation
	spriteCutRect.left = characterSize.x*characterCurrentFrame;
	spriteCutRect.top = 32;
	spriteCutRect.right = spriteCutRect.left + characterSize.x;
	spriteCutRect.bottom = 64;

	//std::cout << "CF : " << characterCurrentFrame << std::endl;
	//std::cout << "RECT X : " << characterRect.left << " , " << characterRect.right << std::endl;
	//std::cout << "RECT Y TOP : " << characterRect.top << " , BOTTOM : " << characterRect.bottom << std::endl;
}

void PlayerController::PlayerRelease()
{
	CollisionManager::releaseColliderBox(playerLine);

	playerTexture->Release();
	playerTexture = NULL;

	trajectDotTex->Release();
	trajectDotTex = NULL;

	trajectSprite->Release();
	trajectSprite = NULL;

	playerSprite->Release();
	playerSprite = NULL;


}

void PlayerController::calNorDirection(D3DXVECTOR2 fromP, D3DXVECTOR2 toP)
{
	D3DXVECTOR2 dir,norDir;
	//long int mag;

	dir = toP - fromP;
	//mag = D3DXVec2LengthSq(&dir);
	D3DXVec2Normalize(&norDir, &dir);
	normDirectV = norDir;
	
}

bool PlayerController::trajectoryAngleClamp()
{
	float angle;
	angle = atan2(normDirectV.y, normDirectV.x) / 3.142 * 180;
	if (angle <= -10 && angle >= -170)
	{
		return true;

	}
	else
	{
		return false;
	}

}

D3DXVECTOR2 PlayerController::GetPlayerPosistion()
{
	return playerPosValue;
}

D3DXVECTOR3 PlayerController::GetPlayerCentre()
{
	return characterCentre;
}

//D3DXVECTOR2 PlayerController::PlayJump()
//{
//	D3DXVECTOR2 nextVelocity = D3DXVECTOR2(0, 0);
//	if (!trajecList.empty())
//	{
//		//std::cout << "Play Jumps !! "<< std::endl;
//		//setIsApplyGravity(true);
//		nextVelocity = trajecList.front();
//		trajecList.pop_front();
//		prev_PlayerVelocity = nextVelocity;
//		if (trajecList.empty())
//		{
//			ResolveCollision();
//		}
//	}
//	return nextVelocity;
//}

D3DXVECTOR2 PlayerController::falling()
{
	D3DXVECTOR2 fallVector = D3DXVECTOR2(0.0f, 0.0f);
	if (!isPlayerCollided)
	{

		//D3DXVECTOR2(prev_PlayerVelocity.x, 0.0f)
		fallVector = (sceneInstance->getGravity());
		return fallVector;
	}
	else
	{
		return fallVector;
	}
}


void PlayerController::playerJumpVer2()
{
	isPlayerMoving = true;
	if (normDirectV.x >= 0)
		playerFaceDirX = 1;
	else
		playerFaceDirX = -1;
	totalVelocity = normDirectV * 500;
	std::cout << "JUMP VEL : " << " ( " << normDirectV.x << " , " << normDirectV.y << " ) " << std::endl;

}


void PlayerController::ResolveCollision(RECT colliderRect)
{
	isPlayerMoving = false;
	
	//Reset velocity , and resolve player pos to the y axis of collider 
	totalVelocity = D3DXVECTOR2(0.0f, 0.0f);
	playerPosValue -= (prev_PlayerVelocity/60);

	std::cout << "Resolving (" << prev_PlayerVelocity.x << " , " << prev_PlayerVelocity.y << " ) " << std::endl;
}

RECT PlayerController::setCalculatePlayerCollision()
{
	colliderSizeRect = CollisionManager::CalculateCollision(playerPosValue,
		oriSizeRect, D3DXVECTOR2(characterCentre.x, characterCentre.y));
	return colliderSizeRect;
}

void PlayerController::setIsApplyGravity(bool boolValue)
{
	if(isPlayerFalling!=boolValue)
		isPlayerFalling = boolValue;
}

void PlayerController::setScenePointer(Scene1 *scenePtr)
{
	sceneInstance = scenePtr;
}
