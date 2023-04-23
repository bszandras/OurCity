#include "HighSchool.h"

HighSchool::HighSchool(Tile* tile) : School(tile)
{
	// Set the members of the base class
	this->buildCost = 100;
	this->maintenanceCost = 30;
	//this->fireChance = 6;
	tile->fireChance += 6;
	this->tileSize = 2;
	this->capacity = 50; // TODO: Modify capacity if needed!
}

HighSchool::~HighSchool()
{
}
