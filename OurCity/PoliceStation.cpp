#include "PoliceStation.h"

/// <summary>
/// Rend�rs�g kontruktor
/// </summary>
/// <param name="tile">A Tile, amire a rend�rs�g �p�l</param>
PoliceStation::PoliceStation(Tile* tile) : SpecialBuilding(tile)
{
	this->buildCost = 100;
	this->maintenanceCost = 30;
	tile->fireChance += 3;
	range = 30;
}

PoliceStation::~PoliceStation()
{
}

/// <summary>
/// Be�ll�tja, hogy a rend�rs�g milyen sugar� ter�letet fed le
/// </summary>
/// <param name="range"></param>
void PoliceStation::setRange(int range)
{
	this->range = range;
}

/// <summary>
/// Friss�ti a k�rnyez� cell�kat rend�rs�g �p�t�se ut�n (n�veli a k�zbiztons�got)
/// </summary>
/// <param name="tiles">A friss�tend� Tile-ok</param>
/// <param name="tileCount">A friss�tend� Tile-ok sz�ma</param>
void PoliceStation::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->publicSafety += 1;
		updatedTiles.push_back(tiles[i]);
	}
}

/// <summary>
/// Friss�ti a k�rnyez� cell�kat rend�rs�g lerombol�sa ut�n (vissza�ll�tja a k�zbiztons�got)
/// </summary>
void PoliceStation::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->publicSafety -= 1;
	}
	updatedTiles.clear();
}

/// <summary>
/// Megadja, hogy mekkora a rend�rs�g hat�sugara
/// </summary>
/// <returns>A rend�rs�g hat�sugara</returns>
int PoliceStation::getRange() const
{
	return this->range;
}