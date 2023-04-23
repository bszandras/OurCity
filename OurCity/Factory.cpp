#include "Factory.h"

Factory::Factory(Tile* tile) : Workplace(tile)
{
	this->buildCost = 0;
	this->maintenanceCost = 0;
	//this->fireChance = 9;
	tile->fireChance = 9;
	this->tile = tile;
	this->capacity = 8;
	this->tax = 0;
}