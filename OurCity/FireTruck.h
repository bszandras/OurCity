#ifndef FIRETRUCK_H
#define FIRETRUCK_H

#include "FireStation.h"
#include "AppTime.h"
#include "Vector.h"
#include "Building.h"
#include "Road.h"
#include <vector>
#include "World.h"

class FireStation;
class FireTruck
{
private:
	FireStation* station;
	Tile* currentPosition;
	Building* destination;
	World* world;

public:
	FireTruck(FireStation* station);
	~FireTruck();

	void goToFire(Building* destination);
	void goBackToStation();

	void setCurrentPosition(Tile* currentPosition);
	void setDestination(Building* destination);

	FireStation* getStation() const;
	Tile* getCurrentPosition() const;
	Building* getDestination() const;
};

#endif