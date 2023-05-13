#include "University.h"

/// <summary>
/// Egyetem konstruktor
/// </summary>
/// <param name="tile">A Tile, amire az egyetemet építeni akarjuk</param>
University::University(Tile* tile) : School(tile)
{
	this->buildCost = 100;
	this->maintenanceCost = 30;
	tile->fireChance += 9;
	this->tileSize = 4;

	capacity = 30; // TODO: modify capacity if needed
}

University::~University()
{
}
