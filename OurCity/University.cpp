#include "University.h"

University::University(Tile* tile) : School(tile)
{
	// Set the members of the base class
	this->buildCost = 100;
	this->maintenanceCost = 30;
	this->fireChance = 0;

	capacity = 0; // TODO: modify capacity if needed
}

University::~University()
{
}
