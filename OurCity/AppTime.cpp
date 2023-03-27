#include "AppTime.h"

Time* Time::instance = nullptr;
Time::Time(float currTime)
{
	if (instance != nullptr)
	{
		return;
	}
	instance = this;
	deltaTime = 0;
	time = currTime;
	// scale-t egyel�re nem haszn�ljuk
	scale = 1;
}

Time::~Time()
{
	instance = nullptr;
}

void Time::UpdateTime(float currTime)
{
	deltaTime = currTime - time;
	// ez nem okvetlen j�, tud nem defini�lt viselked�st gener�lni
	time += deltaTime * scale;
}

void Time::SetScale(float s)
{
	scale = s;
}

float Time::getDelta()
{
	return deltaTime;
}
