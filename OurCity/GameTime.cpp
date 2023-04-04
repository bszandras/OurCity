#include "GameTime.h"

GameTime::GameTime()
{
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	seconds = 0;
	changeSpeed(1);
}

GameTime::~GameTime()
{
}

void GameTime::update(float deltaTime)
{
	seconds += deltaTime;
	if (seconds < 1)
	{
		return;
	}
	seconds = 0;

	hour += speed;
	int days = 0;
	if (hour >= 24)
	{
		days = hour / 24;
		hour = hour % 24;
	}
	day += days;
	
	int months = 0;
	if (day >= 30)
	{
		months = day / 30;
		day = day % 30;
	}
	month += months;

	int years = 0;
	if (month >= 12)
	{
		years = month / 12;
		month = month % 12;
	}
	year += years;

	std::cout << "Year: " << year << " Month: " << month << " Day: " << day << " Hour: " << hour << std::endl;
}

void GameTime::changeSpeed(int i)
{
	switch (i)
	{
		case 0:
			speed = 0;
			break;

		case 1:
			speed = 2;
			break;

		case 2:
			speed = 24;
			break;

		case 3:
			speed = 24 * 7;
			break;

		default:
			std::cerr << "Invalid speed" << std::endl;
			break;
	}
}
