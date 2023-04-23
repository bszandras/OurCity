#ifndef STADIUM_H
#define STADIUM_H

#include "SpecialBuilding.h"
#include <vector>

class Stadium : public SpecialBuilding
{
private:
	int range;
	std::vector<int> rangeTiles; // TileIDs of tiles in range
	std::vector<Tile*> updatedTiles; // Tiles that have been updated
	int bonusHappiness;
public:
	Stadium(Tile* tile);
	~Stadium();

	void setRange(int r);
	void setRangeTiles(std::vector<int> tiles);
	void UpdateAreaAfterBuilding(Tile** tiles, int tileCount);
	void UpdateAreaAfterDestruction();
	int getRange() const;
	std::vector<int> getRangeTiles() const;
};

#endif
