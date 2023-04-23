#include "ServiceBuilding.h"

ServiceBuilding::ServiceBuilding(Tile* tile) : Workplace(tile)
{
	this->buildCost = 0;
	this->maintenanceCost = 0;
	//this->fireChance = 5;
	tile->fireChance += 5;
	this->tile = tile;
	this->capacity = 6;
	this->tax = 0;
}
