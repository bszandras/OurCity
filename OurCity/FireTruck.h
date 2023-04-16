#ifndef FIRETRUCK_H
#define FIRETRUCK_H

#include "FireStation.h"
#include "AppTime.h"
#include "Vector.h"
#include "Building.h"
#include "Road.h"
#include <vector>

class FireTruck
{
private:
	FireStation* station;
	Vector2Data* currentPosition;
	Building* destination;

public:
	FireTruck(FireStation* station);
	~FireTruck();

	void goToFire(std::vector<Road*> path, Building* destination);

	void setCurrentPosition(Vector2Data* currentPosition);
	void setDestination(Building* destination);

	FireStation* getStation() const;
	Vector2Data* getCurrentPosition() const;
	Building* getDestination() const;
};

#endif