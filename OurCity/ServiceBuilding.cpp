#include "ServiceBuilding.h"

ServiceBuilding::ServiceBuilding(Tile* tile) : Workplace(tile)
{
	this->buildCost = 0;
	this->maintenanceCost = 0;

	this->tile = tile;
	this->capacity = 12;
	this->tax = 0;
}
