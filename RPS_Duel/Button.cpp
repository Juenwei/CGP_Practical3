#include "Button.h"

Button::Button(D3DXVECTOR2 pos, D3DXVECTOR2 buttonSize)
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();
	buttonTexture = NULL;
	buttonSprite = NULL;
	textRect.left = -90;
	textRect.top =-18;
	textRect.right = 0;
	textRect.bottom = 0;
	buttonCuttingRect.left = 0.0f, buttonCuttingRect.top = 18.0f, buttonCuttingRect.right = 256.0f, buttonCuttingRect.bottom = 109.0f;
	buttonScale = D3DXVECTOR2(1.0f, 1.0f);
	oriColliderRect.top = 0, oriColliderRect.left = 0, oriColliderRect.bottom = buttonSize.y*buttonScale.y, oriColliderRect.right = buttonSize.x *buttonScale.x;
	buttonPos = D3DXVECTOR2(pos.x, pos.y);
	buttonCentre = D3DXVECTOR3(oriColliderRect.right / 2 * buttonScale.x, oriColliderRect.bottom / 2 * buttonScale.y, 0.0f);
	isOnClick = false;
	isPressed = false;
}

Button::~Button()
{

}

void Button::buttonStart(std::string buttonMsg)
{
	D3DXCreateSprite(myGraphics->d3dDevice, &buttonSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/buttonUI.png", &buttonTexture);
	D3DXCreateFont(myGraphics->d3dDevice, 40, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Courier New", &font);
	buttonColliderRect = CollisionManager::CalculateCollision(buttonPos, oriColliderRect, D3DXVECTOR2(buttonCentre.x, buttonCentre.y));
	this->buttonMsg = buttonMsg;
}

void Button::buttonCollision(RECT mouseRect)
{

	isPressed = false;
	if (CollisionManager::CheckCollision(buttonColliderRect, mouseRect))
	{
		if (myInput->AcceptButtonDown(0))
		{
			myInput->prev_MouseState[0] = 1;
			isPressed = true;
		}
		else if (myInput->prev_MouseState[0] == 1)
		{
			myInput->prev_MouseState[0] = 0;
			isOnClick = true;
			std::cout << "Click event" << std::endl;
		}
	
		
	}
	if (isPressed)
	{
		rValue = 100;
		gValue = 100;
		bValue = 100;
	}
	else
	{
		rValue = 255;
		gValue = 255;
		bValue = 255;
	}
}

void Button::buttonRender()
{
	buttonSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTransformation2D(&buttonMat, NULL, 0.0, &buttonScale, NULL, 0.0f, &buttonPos);
	buttonSprite->SetTransform(&buttonMat);
	buttonSprite->Draw(buttonTexture, &buttonCuttingRect, &buttonCentre, NULL, D3DCOLOR_XRGB(rValue, gValue, bValue));
	font->DrawText(buttonSprite, buttonMsg.c_str(), -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	buttonSprite->End();

}

void Button::buttonRelease()
{
	buttonTexture->Release();
	buttonTexture = NULL;

	font->Release();
	font = NULL;

	buttonSprite->Release();
	buttonSprite = NULL;

}

void Button::resetButton()
{
	isOnClick = false;
}
