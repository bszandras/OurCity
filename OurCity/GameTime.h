#ifndef GAMETIME_H
#define GAMETIME_H

#include <iostream>

class GameTime
{
private:
	int year;
	int month;
	int day;
	int hour;
	int speed;
	float seconds;

public:
	GameTime();
	~GameTime();

	int update(float deltaTime);
	void changeSpeed(int i);
	std::string getTimeString();

	int getHour();
	int getSpeed();
};

#endif
