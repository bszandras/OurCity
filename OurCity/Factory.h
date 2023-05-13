#ifndef FACTORY_H
#define FACTORY_H

#include "Workplace.h"

class Factory : public Workplace
{
private:
	int range;

	std::vector<Tile*> updatedTiles;

public:
	Factory(Tile* tile);

	int getRange() const;

	void setRange(int range);

	void UpdateAreaAfterBuilding(Tile** tiles, int tileCount);
	void UpdateAreaAfterDestruction();
};

#endif