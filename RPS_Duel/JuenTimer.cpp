#include "JuenTimer.h"

JuenTimer::JuenTimer()
{

}

JuenTimer::~JuenTimer()
{
}

void JuenTimer::Init(int fps)
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);

	//init fps time info
	Requested_FPS = fps;
	//The number of intervals in the given

	//timer, per frame at the requested rate.
	intervalsPerFrame =((float)timerFreq.QuadPart / Requested_FPS);
}

int JuenTimer::FramesToUpdate()
{
	int framesToUpdate = 0;
	QueryPerformanceCounter(&timeNow);

	//getting the delta time
	float intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrevious.QuadPart;
	framesToUpdate = (int)(intervalsSinceLastUpdate / intervalsPerFrame);
	//If we are not updating any frames,

	//keep the old previous timer count
	if (framesToUpdate != 0) {
		QueryPerformanceCounter(&timePrevious);
	}
	return framesToUpdate;
}
