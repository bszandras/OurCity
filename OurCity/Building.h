#ifndef BUILDING_H
#define BUILDING_H

#include "Tile.h"

class Building
{
protected:
	unsigned short buildCost;
	unsigned short maintenanceCost;
	unsigned short fireChance;
	Tile* tile;

public:
	Building(Tile* tile);
	~Building();

	unsigned short getBuildCost();
	unsigned short getMaintanceCost();
	unsigned short getFireChance();
	Tile* getTile();

	void catchOnFire();
};

#endif