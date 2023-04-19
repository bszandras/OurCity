#include "Building.h"

Building::Building(Tile* tile)
{
	this->tile = tile;

	buildCost = 0;
	maintenanceCost = 0;
	fireChance = 0;
}

Building::~Building()
{
}

unsigned short Building::getBuildCost()
{
	return buildCost;
}

void Building::setBuildCost(unsigned short c)
{
	buildCost = c;
}

unsigned short Building::getMaintenanceCost()
{
	return maintenanceCost;
}

unsigned short Building::getFireChance()
{
	return fireChance;
}

unsigned char Building::getTileSize()
{
	return tileSize;
}

void Building::catchOnFire()
{
	// TODO: implement this
}

void Building::toString()
{
}

Tile* Building::getTile()
{
	return tile;
}
