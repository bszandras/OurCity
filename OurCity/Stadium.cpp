#include "Stadium.h"
#include <iostream>

/// <summary>
/// Stadion konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a stadiont építjük</param>
Stadium::Stadium(Tile* tile) : SpecialBuilding(tile)
{
	this->buildCost = 100;
	this->maintenanceCost = 30;
	tile->fireChance += 1;
	this->tileSize = 4;
	range = 3;
}

Stadium::~Stadium()
{
}

/// <summary>
/// A stadion hatósugarát állítja be (ilyen környezetben boldogít)
/// </summary>
/// <param name="range">A stadion hatósugara</param>
void Stadium::setRange(int range)
{
	this->range = range;
}

/// <summary>
/// Frissíti a stadion hatósugarában lévõ Tile-okat (boldogságukat)
/// </summary>
/// <param name="tiles">A frissítendõ Tile-ok</param>
/// <param name="tileCount">A frissítendõ Tile-ok száma</param>
void Stadium::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->happinessModifer += 30;
		updatedTiles.push_back(tiles[i]);
	}
}

/// <summary>
/// Frissíti a stadion lerombolása után a környezõ cellákat (boldogságukat)
/// </summary>
void Stadium::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->happinessModifer -= 30;
	}
	updatedTiles.clear();
}

/// <summary>
/// Megadja a stadion hatósugarát.
/// </summary>
/// <returns></returns>
int Stadium::getRange() const
{
	return this->range;
}