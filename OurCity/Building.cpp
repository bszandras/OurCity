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

Tile* Building::getTile()
{
	return tile;
}
