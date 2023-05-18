#pragma once
#include "AppTime.h"
class DayNight
{
private:
	Time* apptime;
	float time;
	float minTime = 0;
	float maxTime = 1;
public:
	DayNight(Time* time);
	~DayNight();

	void ProgressTowardsDay(float deltaTime);
	void ProgressTowardsNight(float deltaTime);
	float getTime();
};