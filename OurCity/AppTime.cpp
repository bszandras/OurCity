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
	// scale-t egyelőre nem használjuk
	scale = 1;
}

Time::~Time()
{
	instance = nullptr;
}

void Time::UpdateTime(float currTime)
{
	deltaTime = currTime - time;
	// ez nem okvetlen jó, tud nem definiált viselkedést generálni
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

float Time::getFullTime()
{
	return time;
}
