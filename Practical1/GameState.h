#pragma once
class GameState
{
	//Abstract class
public:
	
	virtual void Init()=0;
	virtual void Update()=0;
	virtual void FixedUpdate() = 0;
	virtual void Draw()=0;
	virtual void Release()=0;
	virtual void RenewInput() = 0;
};

