#include "Factory.h"

Factory::Factory(Tile* tile) : Workplace(tile)
{
	this->buildCost = 0;
	this->maintenanceCost = 0;

	this->tile = tile;
	this->capacity = 16;
	this->tax = 0;
}