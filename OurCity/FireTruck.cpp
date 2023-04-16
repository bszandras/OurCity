#include "FireTruck.h"

FireTruck::FireTruck(FireStation* station)
{
	this->station = station;
	this->currentPosition = station->getTile();
	this->destination = nullptr;
}

FireTruck::~FireTruck()
{
}

void FireTruck::goToFire(Building* destination)
{
}

void FireTruck::goBackToStation()
{
}

void FireTruck::setCurrentPosition(Tile* currentPosition)
{
}

void FireTruck::setDestination(Building* destination)
{
}

FireStation* FireTruck::getStation() const
{
	return nullptr;
}

Tile* FireTruck::getCurrentPosition() const
{
	return nullptr;
}

Building* FireTruck::getDestination() const
{
	return nullptr;
}
