#define _USE_MATH_DEFINES

#include "DayNight.h"
#include <cmath>
#include <iostream>

DayNight::DayNight()
{
}

DayNight::~DayNight()
{
}

void DayNight::Restart()
{
	play = true;
}

void DayNight::StopAtDay()
{
	play = false;
}

void DayNight::Syncronized()
{
	synced = true;
}

void DayNight::StartDesync()
{
	sync = -1;
}

float DayNight::progressAndGetTime(float delta)
{
	if (synced)
	{
		cycleTime += delta;
	}

	time = cycleTime;

	time /= 6;

	time = sin(time * M_PI + M_PI);
	time = time * 2 + 1;
	time /= 2;
	if (time < minTime)
	{
		time = minTime;
	}
	else if (time > maxTime)
	{
		time = maxTime;
	}
	//std::cout << cycleTime << " - " <<time<<std::endl;


	// check if needs to desnyc
	// if desyncing and time = 1
	// desync complete
	if (sync == -1 && time == 1)
	{
		sync = 0;
		synced = false;
	}

	return time;
}

float DayNight::getTime()
{
	time = cycleTime;

	time /= 6;

	time = sin(time * M_PI + M_PI);
	time = time * 2 + 1;
	time /= 2;
	if (time < minTime)
	{
		time = minTime;
	}
	else if (time > maxTime)
	{
		time = maxTime;
	}
	return time;
}
