#ifndef SPECIALBUILDING_H
#define SPECIALBUILDING_H

#include "Building.h"

class SpecialBuilding : public Building
{
public:
	SpecialBuilding(Tile* tile);

	void UpdateAreaAfterBuilding(Tile** tiles, int tileCount);
	void UpdateAreaAfterDestruction();
};

#endif
