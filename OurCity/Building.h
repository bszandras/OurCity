#ifndef BUILDING_H
#define BUILDING_H

#include "TileRect.h"

struct Tile;
class Building
{
protected:
	unsigned short buildCost;
	unsigned short maintenanceCost;
	unsigned short fireChance;
	unsigned char tileSize = 1;
	Tile* tile;

public:
	Building(Tile* tile);
	~Building();

	unsigned short getBuildCost();
	unsigned short getMaintenanceCost();
	unsigned short getFireChance();
	unsigned char getTileSize();
	Tile* getTile();

	void catchOnFire();
};

#endif