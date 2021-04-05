#include "PlayerController.h"
#include "Scene1.h"


PlayerController::PlayerController(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size, float speed)
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();
	playerHealth = 100;
	//Ground State 
	pStateType[groundState].colliderRect[0].top = 0;
	pStateType[groundState].colliderRect[0].left = 0;
	pStateType[groundState].colliderRect[0].bottom = 26;
	pStateType[groundState].colliderRect[0].right = 32;
	pStateType[groundState].colliderRect[1].top = 0;
	pStateType[groundState].colliderRect[1].left = 0;
	pStateType[groundState].colliderRect[1].bottom = 38;
	pStateType[groundState].colliderRect[1].right = 38;
	pStateType[groundState].AngleClameType = 1;

	//Wall State Left
	pStateType[wallState].colliderRect[0].top = 0;
	pStateType[wallState].colliderRect[0].left = 0;
	pStateType[wallState].colliderRect[0].bottom = 32;
	pStateType[wallState].colliderRect[0].right = 26;
	pStateType[wallState].colliderRect[1].top = 0;
	pStateType[wallState].colliderRect[1].left = 0;
	pStateType[wallState].colliderRect[1].bottom = 38;
	pStateType[wallState].colliderRect[1].right = 38;
	pStateType[wallState].AngleClameType = 0;

	//Set Current states
	currentPStatus = groundState;
	//playerHealth = 100;

	//Sprite & Animation
	playerTexture = NULL;
	playerSprite = NULL;
	healthFont = NULL;
	characterCurrentFrame = 0;
	characterSize.x = size.x;
	characterSize.y = size.y;
	scaleFactor.x = scale.x;
	scaleFactor.y = scale.y;

	//UI & TEXT
	healthTextRect.left = 16;
	healthTextRect.top = 8;
	healthTextRect.right = 0;
	healthTextRect.bottom = 0;
	playerHealthUIRect.left = 0;
	playerHealthUIRect.top = 88;
	playerHealthUIRect.right = 128;
	playerHealthUIRect.bottom = 128;

	characterCentre = D3DXVECTOR3(size.x / 2, size.y / 4, 0.0f);//X : 16 , Y : 8
	playerFaceDirX = 1;
	animationTimer = 0;
	animationDuration = 0.5f / 5;
	//rotation = pStateType[currentPStatus].spriteRotationRadian;
	rotation = 0.0f;
	minAngleClamp = 0;
	maxAngleClamp = 0;

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
	initialPos = D3DXVECTOR2(pos.x, pos.y);
	playerPosValue = initialPos;
	this->speed = speed;

	//State
	isMoveKeyPressed = false;
	isReleasedKey = false;
	isPlayerFalling = true;
	isPlayerCollided = false;
	isShowingTrajectDot = false;
	isPlayHitAnimation = false;
	canPlayerShoot = true;

	//Collider
	/*for (int i = 0; i < 5; i++)
	{
		playerPointArray[i] = D3DXVECTOR2(0, 0);
		playerPointArray2[i] = D3DXVECTOR2(0, 0);

	}*/

	for (int i = 0; i < 4; i++)
	{
		pStateType[groundState].colliderSidePoint[i] = D3DXVECTOR2(0, 0);
		pStateType[wallState].colliderSidePoint[i] = D3DXVECTOR2(0, 0);
	}
	oriSizeRect = pStateType[currentPStatus].colliderRect[0];
	oriSizeOuterRect2 = pStateType[currentPStatus].colliderRect[1];
	outerColliderRect2Center = D3DXVECTOR3(characterCentre.x + 3, characterCentre.y + 2.0f, 0.0f);

	//Timer
	shootTimeElasped = 0.0f;
	shootTimeDuration = 0.4f;

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
	//Reset State
	D3DXCreateSprite(myGraphics->d3dDevice, &playerSprite);
	D3DXCreateSprite(myGraphics->d3dDevice, &trajectSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slime.png", &playerTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slimeTraject.png", &trajectDotTex);
	D3DXCreateLine(myGraphics->d3dDevice, &playerLine);
	D3DXCreateFont(myGraphics->d3dDevice, 20, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &healthFont);
	
}

void PlayerController::ReceiveInput()
{
	isMoveKeyPressed = false;
	inputAxis = D3DXVECTOR2(0, 0);
	
	if (currentPStatus == groundState)
	{
		if (myInput->AcceptKeyDown(DIK_LEFT))
		{
			//std::cout << "LEFT" << std::endl;
			inputAxis.x = -1;
			playerFaceDirX = -1;
			isMoveKeyPressed = true;
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
			isMoveKeyPressed = true;
			myInput->prev_KeyState[DIK_LEFT] = 1;
		}
		else if (myInput->prev_KeyState[DIK_RIGHT] == 1)
		{
			myInput->prev_KeyState[DIK_RIGHT] = 0;
			//isPlayerMoving = false;

		}
	}
	else if (currentPStatus == wallState)
	{
		if (myInput->AcceptKeyDown(DIK_UP))
		{
			inputAxis.y = -1;
			playerFaceDirX = -1 * (rotation / abs(rotation));
			isMoveKeyPressed = true;
			myInput->prev_KeyState[DIK_UP] = 1;
		}
		else if (myInput->prev_KeyState[DIK_UP] == 1)
		{
			myInput->prev_KeyState[DIK_UP] = 0;
			//rotation += 0.1f;
			//std::cout << "Current Rotation : " << rotation << std::endl;

		}
		if (myInput->AcceptKeyDown(DIK_DOWN))
		{
			inputAxis.y = 1;
			playerFaceDirX = 1 * (rotation / abs(rotation));
			isMoveKeyPressed = true;
			myInput->prev_KeyState[DIK_DOWN] = 1;
		}
		else if (myInput->prev_KeyState[DIK_DOWN] == 1)
		{
			myInput->prev_KeyState[DIK_DOWN] = 0;
			//rotation -= 0.1f;
			//std::cout << "Current Rotation : " << rotation << std::endl;

		}
	}
	

	if (myInput->AcceptButtonDown(1))
	{
		calNorDirection(GetPlayerPosistion(), myInput->getMousePosition());
		//std::cout << "Angle : " << trajectoryAngleClamp() << std::endl;
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
	//std::cout << " Is player move : " << isMoveKeyPressed << std::endl;
	//std::cout << " Is player Collided : " << isPlayerCollided<< std::endl;
	CollisionManager::setCollisionBox(playerPointArray, getPlayerCollision());
	CollisionManager::setCollisionBox(playerPointArray2, colliderSizeRect2);
	for (int i = 0; i < sceneInstance->getSizeOfMapTileList(); i++)
	{
		RECT tempMapRect = sceneInstance->getMapTilePointer(i)->getCollisionRect();

		if (CollisionManager::CheckCollision(getPlayerCollision(), tempMapRect))
		{
			//Collided
			//Calculate Player
			CollisionManager::calculateSideOfCollision(pStateType[currentPStatus].colliderSidePoint, colliderSizeRect);
			int tempIndex = CollisionManager::checkSideOfCollider(pStateType[currentPStatus].colliderSidePoint, sceneInstance->getMapTilePointer(i)->mapSideCenterPoint, tempMapRect);
			//Check Side
			if (tempIndex == 1)
			{
				std::cout << "Switch to ground state" << std::endl;
				ChangePlayerState(groundState, 0.0f, -10, -170);
			}
			else if(tempIndex ==2)
			{
				std::cout << "Switch to wall state Left" << std::endl;
				pStateType[wallState].AngleClameType = tempIndex;
				ChangePlayerState(wallState, -1.5f, 100,-100);
			}
			else if (tempIndex == 3)
			{
				std::cout << "Switch to wall state Right" << std::endl;
				pStateType[wallState].AngleClameType = tempIndex;
				ChangePlayerState(wallState, 1.5f, 80, -80);
			}
			ResolveCollision(sceneInstance->getMapTilePointer(i)->getCollisionRect());
		}
		//Loop until last no collision
		colliderSizeRect2 = CollisionManager::CalculateCollision(playerPosValue, oriSizeOuterRect2, D3DXVECTOR2(outerColliderRect2Center.x, outerColliderRect2Center.y));
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

	//Plus is Collided while implement
	if (isMoveKeyPressed&&isPlayerCollided)
	{
		playerMoveVelocity = inputAxis * speed;
		if (abs(playerMoveVelocity.x) > 100)
		{
			playerMoveVelocity.x = (playerMoveVelocity.x / abs(playerMoveVelocity.x)) * 100;
		}
	}
	else
	{
		playerMoveVelocity = D3DXVECTOR2(0, 0);
	}
	
	//Speed Clamping
	if (abs(totalVelocity.x) > 300)
	{
		totalVelocity.x = (totalVelocity.x / abs(totalVelocity.x)) * 300;
	}
	
	playerPosValue += (totalVelocity + playerMoveVelocity )/ 60.0f;

	//Clamp for map boundary
	if (playerPosValue.y <= 900)
	{
		totalVelocity.y += ApplyGravity().y;
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


	//scaling = D3DXVECTOR2(scaleFactor.x*playerFaceDirX, scaleFactor.y);

	//D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, rotation, &playerPosValue);
}

void PlayerController::PlayerRender() 
{
	playerSprite->Begin(D3DXSPRITE_ALPHABLEND);
	scaling = D3DXVECTOR2(scaleFactor.x*playerFaceDirX, scaleFactor.y);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, rotation, &playerPosValue);
	playerSprite->SetTransform(&mat);
	playerSprite->Draw(playerTexture, &spriteCutRect, &characterCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &D3DXVECTOR2(2.0f, 2.0f), NULL, NULL, &D3DXVECTOR2(0.0f, 0.0f));
	playerSprite->SetTransform(&mat);
	playerSprite->Draw(healthUITex, &playerHealthUIRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	std::string healthString = "Health : " + std::to_string(playerHealth);
	healthFont->DrawText(playerSprite, healthString.c_str() ,-1, &healthTextRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	playerSprite->End();

	CollisionManager::drawColliderBox(playerLine, playerPointArray,5);
	CollisionManager::drawColliderBox(playerLine, playerPointArray2,5);
	if (isShowingTrajectDot)
	{
		trajectSprite->Begin(D3DXSPRITE_ALPHABLEND);
		calNorDirection(GetPlayerPosistion(), myInput->getMousePosition());
		D3DXVECTOR2 tempVelocity = normDirectV * 500;
		D3DXVECTOR2 tempPosistion = playerPosValue;
		for (int i = 0; i < 120; i++)
		{
			
			tempPosistion += (tempVelocity / 60.0f);
			tempVelocity.y += 10;
			//Speed Clamping
			if (abs(tempVelocity.x) > 300)
			{
				//MIN(MAX)
				tempVelocity.x = (tempVelocity.x / abs(tempVelocity.x)) * 300;
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

	if (myInput->AcceptKeyDown(DIK_RIGHT) || myInput->AcceptKeyDown(DIK_LEFT)|| myInput->AcceptKeyDown(DIK_UP) || myInput->AcceptKeyDown(DIK_DOWN))
	{
		//Walk
		if (animationTimer >= animationDuration)
		{
			animationTimer -= animationDuration;
			characterCurrentFrame++;
			characterCurrentFrame %= 5;
		}
		spriteCutRect.left = characterSize.x * characterCurrentFrame;
		spriteCutRect.top = 32;
		spriteCutRect.right = spriteCutRect.left + characterSize.x;
		spriteCutRect.bottom = 64;
	}
	else if (!isPlayerCollided)
	{
		//JUMP
		if (animationTimer >= animationDuration)
		{
			animationTimer -= animationDuration;
		}
		spriteCutRect.left = 96;
		spriteCutRect.top = 64;
		spriteCutRect.right = spriteCutRect.left + characterSize.x;
		spriteCutRect.bottom = 96;
	}
	else if (myInput->AcceptKeyDown(DIK_D))
	{
		//Dead //Play one time only
		if (animationTimer >= animationDuration)
		{
			animationTimer -= animationDuration;
			characterCurrentFrame++;
			characterCurrentFrame %= 6;
		}
		spriteCutRect.left = characterSize.x * characterCurrentFrame;
		spriteCutRect.top = 128;
		spriteCutRect.right = spriteCutRect.left + characterSize.x;
		spriteCutRect.bottom = 160;
	}
	else if (myInput->AcceptKeyDown(DIK_H))
	{
		//hit , Play one time only
		if (animationTimer >= animationDuration)
		{
			animationTimer -= animationDuration;
			characterCurrentFrame++;
			characterCurrentFrame %= 2;
		}
		spriteCutRect.left = characterSize.x * characterCurrentFrame;
		spriteCutRect.top = 160;
		spriteCutRect.right = spriteCutRect.left + characterSize.x;
		spriteCutRect.bottom = 192;
	}
	else
	{
		//Idle
		if (animationTimer >= animationDuration)
		{
			animationTimer -= animationDuration;
			characterCurrentFrame++;
			characterCurrentFrame %= 4;
		}
		spriteCutRect.left = characterSize.x * characterCurrentFrame;
		spriteCutRect.top = 96;
		spriteCutRect.right = spriteCutRect.left + characterSize.x;
		spriteCutRect.bottom = 128;
	}
}

void PlayerController::PlayerRelease()
{
	CollisionManager::releaseColliderBox(playerLine);

	healthFont->Release();
	healthFont = NULL;

	playerTexture->Release();
	playerTexture = NULL;

	trajectDotTex->Release();
	trajectDotTex = NULL;

	trajectSprite->Release();
	trajectSprite = NULL;

	playerSprite->Release();
	playerSprite = NULL;
}

void PlayerController::PlayerTimer()
{
	shootTimeElasped += (1 / 60.0f);
	
	if (shootTimeElasped >= shootTimeDuration)
	{
		canPlayerShoot = true;
	}
}

void PlayerController::ResetShootTimer()
{
	canPlayerShoot = false;
	shootTimeElasped = 0.0f;
}

void PlayerController::ResetPlayerValue()
{
	isMoveKeyPressed = false;
	isReleasedKey = false;
	isPlayerFalling = true;
	isPlayerCollided = false;
	isShowingTrajectDot = false;
	isPlayHitAnimation = false;
	canPlayerShoot = true;
	currentPStatus = groundState;
	playerHealth = 100;
	playerPosValue = initialPos;
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
	//std::cout << "Angle : " << angle << std::endl;
	if (currentPStatus == groundState)
	{
		if (angle <= minAngleClamp && angle >= maxAngleClamp)
		{
			return true;

		}
		else
		{
			//std::cout << "Angle : " << angle << "  Not Within the range from : " << minAngleClamp << "  to : " << maxAngleClamp << std::endl;
			return false;
		}
	}
	else
	{
		if (pStateType[wallState].AngleClameType == 2)
		{
			if (abs(angle) > minAngleClamp)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (abs(angle) < minAngleClamp)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

}

D3DXVECTOR2 PlayerController::ApplyGravity()
{
	D3DXVECTOR2 fallVector = D3DXVECTOR2(0.0f, 0.0f);
	if (!isPlayerCollided)
	{
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
	isMoveKeyPressed = true;
	if (normDirectV.x >= 0)
		playerFaceDirX = 1;
	else
		playerFaceDirX = -1;
	rotation = 0.0f;
	totalVelocity = normDirectV * 500;
}


void PlayerController::ResolveCollision(RECT colliderRect)
{
	isMoveKeyPressed = false;
	totalVelocity = D3DXVECTOR2(0.0f, 0.0f);
	playerPosValue -= (prev_PlayerVelocity/100);
}

void PlayerController::ChangePlayerState(PlayerStatus targetState, float rotationRad, int minAngle, int maxAngle)
{
	currentPStatus = targetState;
	oriSizeRect = pStateType[currentPStatus].colliderRect[0];
	oriSizeOuterRect2 = pStateType[currentPStatus].colliderRect[1];
	rotation = rotationRad;
	minAngleClamp = minAngle;
	maxAngleClamp = maxAngle;
}

void PlayerController::SetPlayerUI(LPDIRECT3DTEXTURE9 UITexture)
{
	healthUITex = UITexture;
}

D3DXVECTOR2 PlayerController::GetPlayerPosistion()
{
	return playerPosValue;
}

D3DXVECTOR3 PlayerController::GetPlayerCentre()
{
	return characterCentre;
}

void PlayerController::gettingDamage(int damage)
{
	playerHealth -= damage;
}

RECT PlayerController::getPlayerCollision()
{
	colliderSizeRect = CollisionManager::CalculateCollision(playerPosValue,
		oriSizeRect, D3DXVECTOR2(characterCentre.x, characterCentre.y));
	return colliderSizeRect;
}

bool PlayerController::getPlayerShooting()
{
	return canPlayerShoot;
}

int PlayerController::getPlayerHealth()
{
	return playerHealth;
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
