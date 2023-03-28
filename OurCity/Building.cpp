#include "Building.h"

Building::Building(Tile* tile)
{
	this->tile = tile;
}

Building::~Building()
{
}

int Building::getBuildCost()
{
	return buildCost;
}

int Building::getMaintanceCost()
{
	return maintenanceCost;
}

int Building::getFireChance()
{
	return fireChance;
}

void Building::catchOnFire()
{
	// TODO: implement this
}

Tile* Building::getTile()
{
	return tile;
}
