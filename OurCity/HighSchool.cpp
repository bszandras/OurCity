#include "HighSchool.h"

/// <summary>
/// Középiskola konstruktor
/// </summary>
/// <param name="tile">A Tile, amire az iskolát építjük</param>
HighSchool::HighSchool(Tile* tile) : School(tile)
{
	this->buildCost = 100;
	this->maintenanceCost = 30;

	tile->fireChance += 6;
	this->tileSize = 2;
	this->capacity = 50; // TODO: Modify capacity if needed!
}

HighSchool::~HighSchool()
{
}
