#include "Factory.h"

/// <summary>
/// Ipari �p�let konstruktor
/// </summary>
/// <param name="tile">A Tile, amin az ipari �p�let van</param>
Factory::Factory(Tile* tile) : Workplace(tile)
{
	this->buildCost = 0;
	this->maintenanceCost = 0;
	tile->fireChance += 9;
	this->tile = tile;
	this->capacity = 8;
	this->range = 2;
}

/// <summary>
/// Az ipari �p�let kedvront� hat�s�nak hat�sugar�nak be�ll�t�sa
/// </summary>
/// <param name="range">Ekkora hat�sug�rban rontja a lakosok kedv�t az ipari �p�let</param>
void Factory::setRange(int range)
{
	this->range = range;
}

/// <summary>
/// Az ipari �p�let �p�l�se ut�n friss�ti a k�rnyez� cell�k szennyezetts�g�t
/// </summary>
/// <param name="tiles">A friss�tend� Tile-ok</param>
/// <param name="tileCount">A friss�tend� Tile-ok sz�ma</param>
void Factory::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->pollution += 1;
		updatedTiles.push_back(tiles[i]);
	}
}

/// <summary>
/// Az ipari �p�let lerombol�sa ut�n friss�ti a k�rnyez� cell�k szennyezetts�g�t
/// </summary>
void Factory::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->pollution -= 1;
	}
	updatedTiles.clear();
}

/// <summary>
/// Megadja az ipari �p�let kedvront� hat�s�nak hat�sugar�t
/// </summary>
/// <returns>A kedvront� hat�s sugara</returns>
int Factory::getRange() const
{
	return this->range;
}