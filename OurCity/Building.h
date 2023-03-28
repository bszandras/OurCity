#ifndef BUILDING_H
#define BUILDING_H

#include "Tile.h"

class Building
{
protected:
	int buildCost;
	int maintenanceCost;
	int fireChance;
	Tile* tile;

public:
	Building(Tile* tile);
	~Building();

	int getBuildCost();
	int getMaintanceCost();
	int getFireChance();
	Tile* getTile();

	void catchOnFire();
};

#endif