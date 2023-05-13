#ifndef STADIUM_H
#define STADIUM_H

#include "SpecialBuilding.h"
#include <vector>

class Stadium : public SpecialBuilding
{
private:
	int range;

	std::vector<Tile*> updatedTiles; // Tiles that have been updated

public:
	Stadium(Tile* tile);
	~Stadium();

	int getRange() const;

	void setRange(int range);

	void UpdateAreaAfterBuilding(Tile** tiles, int tileCount);
	void UpdateAreaAfterDestruction();

};

#endif
