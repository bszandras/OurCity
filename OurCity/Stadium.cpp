#include "Stadium.h"
#include <iostream>

/// <summary>
/// Stadion konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a stadiont �p�tj�k</param>
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
/// A stadion hat�sugar�t �ll�tja be (ilyen k�rnyezetben boldog�t)
/// </summary>
/// <param name="range">A stadion hat�sugara</param>
void Stadium::setRange(int range)
{
	this->range = range;
}

/// <summary>
/// Friss�ti a stadion hat�sugar�ban l�v� Tile-okat (boldogs�gukat)
/// </summary>
/// <param name="tiles">A friss�tend� Tile-ok</param>
/// <param name="tileCount">A friss�tend� Tile-ok sz�ma</param>
void Stadium::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->happinessModifer += 30;
		updatedTiles.push_back(tiles[i]);
	}
}

/// <summary>
/// Friss�ti a stadion lerombol�sa ut�n a k�rnyez� cell�kat (boldogs�gukat)
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
/// Megadja a stadion hat�sugar�t.
/// </summary>
/// <returns></returns>
int Stadium::getRange() const
{
	return this->range;
}