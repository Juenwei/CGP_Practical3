#pragma once
#include"JuenWindow.h"
class JuenTimer
{
private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;
	int Requested_FPS;
	float intervalsPerFrame;
public:
	JuenTimer();
	~JuenTimer();
	void Init(int fps);
	int FramesToUpdate();



};

