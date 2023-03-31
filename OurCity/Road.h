#ifndef ROAD_H
#define ROAD_H

#include "SpecialBuilding.h"

class Road : public SpecialBuilding
{
private:
	static int idxCounter;
	int idx;

public:
	Road(Tile* tile);
};

#endif
