#ifndef FACTORY_H
#define FACTORY_H

#include "Workplace.h"

class Factory : public Workplace
{
private:
	int range;
	std::vector<int> rangeTiles;
	std::vector<Tile*> updatedTiles;
	int minusHappiness;
public:
	Factory(Tile* tile);

	void setRange(int r);
	void setRangeTiles(std::vector<int> tiles);
	void UpdateAreaAfterBuilding(Tile** tiles, int tileCount);
	void UpdateAreaAfterDestruction();
	int getRange() const;
	std::vector<int> getRangeTiles() const;
};

#endif