#pragma once
//#include "AppTime.h"
class DayNight
{
private:
	//Time* apptime;
	float time = 0;
	float minTime = 0;
	float maxTime = 1;
	float cycleTime = 1.0f;
	bool play = true;
	// ez az int folyamatot ír le
	// 0 nem csinál semmit
	// -1 deszinkronizál
	// 1 szinkronizál
	int sync = 0;
	bool synced = true;
public:
	DayNight();
	~DayNight();

	void Restart();
	void StopAtDay();
	void Syncronized();
	void StartDesync();
	float progressAndGetTime(float delta);
	float getTime();
};