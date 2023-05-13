#ifndef BUILDING_H
#define BUILDING_H

#include "TileRect.h"

struct Tile;
class Building
{
protected:
	unsigned short buildCost;
	unsigned short maintenanceCost;

	unsigned char tileSize = 1;
	Tile* tile;

public:
	Building(Tile* tile);
	~Building();

	unsigned short getBuildCost();
	unsigned short getMaintenanceCost();
	unsigned char getTileSize();
	Tile* getTile();
	short getFireChance();

	void setBuildCost(unsigned short cost);

	virtual void toString();
};

#endif